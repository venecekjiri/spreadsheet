#include <iostream>
#include <sstream>

#include "CCell.h"
#include "CInvalidFormat.h"

CFormula::CFormula(const string &formula, const CSheet &sheet) : m_Formula(sheet) {

    if (!m_Formula.Parse(formula)) {

        throw CInvalidFormat();
    }
}

string CFormula::GetValue() const {

    ostringstream oss;
    oss << m_Formula.Evaluate();

    return oss.str();
}

void CFormula::SetValue(const string &value) {

    m_Formula = value;
}

bool CFormula::IsLinkable() const {

    return true;
}

string CFormula::Print() const {

    return ("=" + m_Formula.Print());
}

bool CNumber::IsLinkable() const {

    return true;
}

CLabel::CLabel(const std::string &text)
        : m_Label(text) {}

string CLabel::GetValue() const {

    return m_Label;
}

void CLabel::SetValue(const string &value) {

    m_Label = value;
}

bool CLabel::IsLinkable() const {

    return false;
}

string CLabel::Print() const {

    return m_Label;
}

CInteger::CInteger(int value) : m_Value(value) {}

string CInteger::GetValue() const {

    return to_string(m_Value);
}

void CInteger::SetValue(const string &value) {

    m_Value = stoi(value);
}

string CInteger::Print() const {

    return GetValue();
}

CDecimal::CDecimal(double value) : m_Value(value) {}

string CDecimal::GetValue() const {

    ostringstream oss;
    oss << m_Value;

    return oss.str();
}

void CDecimal::SetValue(const string &value) {

    m_Value = stod(value);
}

string CDecimal::Print() const {

    return GetValue();
}
