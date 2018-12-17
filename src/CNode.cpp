#include <cmath>
#include "CNode.h"
#include "CSheet.h"

CBinaryPredicate::CBinaryPredicate(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right)
        : m_Left(move(m_Left)), m_Right(move(m_Right)) {}

CUnaryPredicate::CUnaryPredicate(unique_ptr<CNode> m_Child)
        : m_Child(move(m_Child)) {}

CBinaryFunction::CBinaryFunction(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right)
        : CBinaryPredicate(move(m_Left), move(m_Right)) {}

CUnaryFunction::CUnaryFunction(unique_ptr<CNode> m_Child)
        : CUnaryPredicate(move(m_Child)) {}

CBrackets::CBrackets(unique_ptr<CNode> m_Child)
        : CUnaryPredicate(move(m_Child)) {}

double CBrackets::Calculate() const {

    return m_Child->Calculate();
}

CPlus::CPlus(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right)
        : CBinaryPredicate(move(m_Left), move(m_Right)) {}

double CPlus::Calculate() const {

    return m_Left->Calculate() + m_Right->Calculate();
}

CMinus::CMinus(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right)
        : CBinaryPredicate(move(m_Left), move(m_Right)) {}

double CMinus::Calculate() const {

    return m_Left->Calculate() - m_Right->Calculate();
}

CMultiply::CMultiply(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right)
        : CBinaryPredicate(move(m_Left), move(m_Right)) {}

double CMultiply::Calculate() const {

    return m_Left->Calculate() * m_Right->Calculate();
}

CDivide::CDivide(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right)
        : CBinaryPredicate(move(m_Left), move(m_Right)) {}

double CDivide::Calculate() const {

    return m_Left->Calculate() / m_Right->Calculate();
}

CAbs::CAbs(unique_ptr<CNode> m_Child)
        : CUnaryFunction(move(m_Child)) {}

double CAbs::Calculate() const {

    return fabs(m_Child->Calculate());
}

CSin::CSin(unique_ptr<CNode> m_Child)
        : CUnaryFunction(move(m_Child)) {}

double CSin::Calculate() const {

    return sin(m_Child->Calculate());
}

CCos::CCos(unique_ptr<CNode> m_Child)
        : CUnaryFunction(move(m_Child)) {}

double CCos::Calculate() const {

    return cos(m_Child->Calculate());
}

CMax::CMax(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right)
        : CBinaryFunction(move(m_Left), move(m_Right)) {}

double CMax::Calculate() const {

    return max(m_Left->Calculate(), m_Right->Calculate());
}

CMin::CMin(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right)
        : CBinaryFunction(move(m_Left), move(m_Right)) {}

double CMin::Calculate() const {

    return min(m_Left->Calculate(), m_Right->Calculate());
}

CPow::CPow(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right)
        : CBinaryFunction(move(m_Left), move(m_Right)) {}

double CPow::Calculate() const {

    return pow(m_Left->Calculate(), m_Right->Calculate());
}

CValue::CValue(double m_Value) : m_Value(m_Value) {}

double CValue::Calculate() const {

    return m_Value;
}

CLink::CLink(const CSheet &m_Sheet, const string &m_Coordinates)
        : m_Sheet(m_Sheet), m_Coordinates(m_Coordinates) {}

double CLink::Calculate() const {

    string result = m_Sheet.GetValue(m_Coordinates);

    return stod(result);
}

double CNegation::Calculate() const {

    return -(m_Child->Calculate());
}

CNegation::CNegation(unique_ptr<CNode> m_Child)
        : CUnaryPredicate(move(m_Child)) {}
