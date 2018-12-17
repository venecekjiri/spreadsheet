#include "CExpression.h"
#include "CInvalidFormat.h"

CExpression::CExpression(const CSheet &m_Sheet)
        : m_Sheet(m_Sheet) {}

string CExpression::Print() const {

    return m_ExpressionAsString;
}

double CExpression::Evaluate() const {

    return m_Head->Calculate();
}

CExpression &CExpression::operator=(const string &str) {

    if (m_ExpressionAsString != str) {

        if (!Parse(str)) {

            throw CInvalidFormat();
        }
    }

    return *this;
}

bool CExpression::Parse(const string &str) {

    m_ExpressionAsString = str;

    string::const_iterator it = m_ExpressionAsString.begin();

    try {

        m_Head = move(ParseSummand(it));
    }
    catch (...) {

        return false;
    }

    return true;
}

unique_ptr<CNode> CExpression::ParseSummand(string::const_iterator &it) {

    if (it == m_ExpressionAsString.end()) {

        throw CInvalidFormat();
    }

    unique_ptr<CNode> leftSide = ParseFactor(it);

    while (it != m_ExpressionAsString.end()) {

        if (*it == '+') {

            it++;

            unique_ptr<CNode> rightSide = ParseFactor(it);

            leftSide = make_unique<CPlus>(CPlus(move(leftSide), move(rightSide)));

            continue;
        } else if (*it == '-') {

            it++;

            unique_ptr<CNode> rightSide = ParseFactor(it);

            leftSide = make_unique<CMinus>(CMinus(move(leftSide), move(rightSide)));

            continue;
        } else {

            return move(leftSide);
        }
    }

    return move(leftSide);
}

unique_ptr<CNode> CExpression::ParseFactor(string::const_iterator &it) {

    if (it == m_ExpressionAsString.end()) {

        throw CInvalidFormat();
    }

    unique_ptr<CNode> leftSide = ParseBracket(it);

    while (it != m_ExpressionAsString.end()) {

        if (*it == '*') {

            it++;

            unique_ptr<CNode> rightSide = ParseBracket(it);

            leftSide = make_unique<CMultiply>(CMultiply(move(leftSide), move(rightSide)));

            continue;
        } else if (*it == '/') {

            it++;

            unique_ptr<CNode> rightSide = ParseBracket(it);

            leftSide = make_unique<CDivide>(CDivide(move(leftSide), move(rightSide)));

            continue;
        }

        return move(leftSide);
    }

    return move(leftSide);
}

unique_ptr<CNode> CExpression::ParseNumber(string::const_iterator &it) {

    if (it == m_ExpressionAsString.end()) {

        throw CInvalidFormat();
    }

    if (isdigit(*it)) {

        double result(0);
        int decPointCnt(0);

        string tmp;

        while (it != m_ExpressionAsString.end() && (isdigit(*it) || *it == '.') && decPointCnt < 2) {

            if(*it == '.'){

                decPointCnt++;
            }

            tmp.push_back(*it++);
        }

        if(it != m_ExpressionAsString.end() && (isdigit(*it) || *it == '.')){

            throw CInvalidFormat();
        }

        try {

            result = stod(tmp);
        }catch (...){

            throw CInvalidFormat();
        }

        unique_ptr<CValue> token = make_unique<CValue>(CValue(result));
        return move(token);
    }

    throw CInvalidFormat();

}

unique_ptr<CNode> CExpression::ParseBracket(string::const_iterator &it) {

    if (it == m_ExpressionAsString.end()) {

        throw CInvalidFormat();
    }

    unique_ptr<CNode> token;

    // Handle signs
    if (*it == '-') {

        it++;

        token = make_unique<CNegation>(CNegation(ParseBracket(it)));
        return token;
    } else if (*it == '+') {

        it++;
    }

    // Parse brackets
    if (*it == '(') {

        it++;

        token = ParseSummand(it);

        if (*it == ')') {

            it++;
            return move(token);
        }

        throw CInvalidFormat();
    } else if (isdigit(*it) || isalpha(*it)) {

        token = ParseLink(it);
        return move(token);
    }

    throw CInvalidFormat();
}

unique_ptr<CNode> CExpression::ParseLink(string::const_iterator &it) {

    if (it == m_ExpressionAsString.end()) {

        throw CInvalidFormat();
    }

    // Parse links
    if (isupper(*it)) {

        string coordinates;

        coordinates.push_back(*it++);

        while (isdigit(*it)) {

            coordinates.push_back(*it++);
        }

        if (coordinates.length() < 2) {

            throw CInvalidFormat();
        }

        unique_ptr<CLink> newToken = make_unique<CLink>(CLink(m_Sheet, coordinates));
        return move(newToken);
    }

    return ParseFunction(it);
}

unique_ptr<CNode> CExpression::ParseFunction(string::const_iterator &it) {

    if (it == m_ExpressionAsString.end()) {

        throw CInvalidFormat();
    }

    unique_ptr<CNode> token;

    // Parse functions
    if (islower(*it)) {

        string functionName;

        while (it != m_ExpressionAsString.end() && *it != '(') {

            functionName.push_back(*it++);
        }

        if (it != m_ExpressionAsString.end()){

            it++;
        }
        else{

            throw CInvalidFormat();
        }

        if (functionName == "abs") {

            token = make_unique<CAbs>(CAbs(ParseSummand(it)));
        } else if (functionName == "cos") {

            token = make_unique<CCos>(CCos(ParseSummand(it)));
        } else if (functionName == "sin") {

            token = make_unique<CSin>(CSin(ParseSummand(it)));
        } else if (functionName == "max") {

            unique_ptr<CNode> leftSide = ParseSummand(it);

            if (*it == ',') {

                it++;
            } else {

                throw CInvalidFormat();
            }

            unique_ptr<CNode> rightSide = ParseSummand(it);

            token = make_unique<CMax>(CMax(move(leftSide), move(rightSide)));
        } else if (functionName == "pow") {

            unique_ptr<CNode> leftSide = ParseSummand(it);

            if (*it == ',') {

                it++;
            } else {

                throw CInvalidFormat();
            }

            unique_ptr<CNode> rightSide = ParseSummand(it);

            token = make_unique<CPow>(CPow(move(leftSide), move(rightSide)));
        } else if (functionName == "min") {

            unique_ptr<CNode> leftSide = ParseSummand(it);

            if (*it == ',') {

                it++;
            } else {

                throw CInvalidFormat();
            }

            unique_ptr<CNode> rightSide = ParseSummand(it);

            token = make_unique<CMin>(CMin(move(leftSide), move(rightSide)));
        } else {

            throw CInvalidFormat();
        }

        if (*it == ')') {

            it++;
            return move(token);
        } else {

            throw CInvalidFormat();
        }
    }

    return ParseNumber(it);
}
