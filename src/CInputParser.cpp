#include "CInputParser.h"

bool CInputParser::Parse(const string &input) {

    m_Result.clear();

    if(!input.length() || input.find_first_not_of(" \n\t") == string::npos){

        return false;
    }

    string formattedInput = StripSpaces(input);

    if (IsInteger(formattedInput)) {

        m_Result = formattedInput;

        m_Type = CellTypes::integer;
    } else if (IsDouble(formattedInput)) {

        m_Result = formattedInput;

        m_Type = CellTypes::decimal;
    } else if (IsFormula(formattedInput)) {

        // Removes all spaces
        copy_if(formattedInput.begin() + 1, formattedInput.end(), back_inserter(m_Result),
                [](char c) { return !isspace(c); });

        m_Type = CellTypes::formula;
    } else if (IsLabel(formattedInput)) {

        m_Result = formattedInput;

        m_Type = CellTypes::label;
    } else {

        return false;
    }

    return true;
}

bool CInputParser::IsInteger(const string &str) const {

    if(str.length() > 0 && (str.at(0) == '+' || str.at(0) == '-' || isdigit(str.at(0)))){

        try {

            stoi(str);
        }
        catch (...) {

            return false;
        }

        if(str.length() == 1){

            return true;
        }

        // Additional check if string isn't cut short by stoi and doesn't contain invalid data
        return str.length() > 1 && str.find_first_not_of("0123456789", 1) == string::npos;
    }

    return false;
}

bool CInputParser::IsDouble(const string &str) const {

    if(str.length() > 0 && (str.at(0) == '+' || str.at(0) == '-' || isdigit(str.at(0)))){

        try {

            stod(str);
        }
        catch (...) {

            return false;
        }

        if(str.length() == 1){

            return true;
        }

        // Additional check if string isn't cut short by stod and doesn't contain invalid data
        return str.find_first_not_of("0123456789.", 1) == string::npos && count(str.begin(), str.end(), '.') == 1;
    }

    return false;
}

bool CInputParser::IsFormula(const string &str) const {

    return str.length() > 1 && str.at(0) == '=' && str.find_first_of('=', 1) == string::npos;
}

bool CInputParser::IsLabel(const string &str) const {

    // Allowed symbols
    size_t i = str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:- ");

    return i == string::npos;
}

int CInputParser::Type() const {

    return m_Type;
}

string CInputParser::Result() const {

    return m_Result;
}

string CInputParser::StripSpaces(const string &str) const {

    bool inSpaces(true);
    string result;

    string::const_iterator it = str.begin();

    while (it != str.end()) {

        if (isspace(*it) && inSpaces) {

            it++;
            continue;
        } else {

            result.push_back(*it);
            inSpaces = isspace(*it) && !inSpaces;
        }

        it++;
    }

    // Get rid of trailing space
    if (result.length() > 1 && isspace(result.at(result.length() - 1))) {

        result.pop_back();
    }

    return result;
}