#ifndef VENECJIR_CCELL_H
#define VENECJIR_CCELL_H

#include <string>

#include "CExpression.h"

using namespace std;

/**
 * Class that represents single cell.
 */
class CCell {
public:

    virtual ~CCell() = default;

    /**
     * Gets cell value.
     *
     * @return Cell value
     */
    virtual string GetValue() const = 0;

    /**
     * Gets cell value in printable format.
     *
     * @return Cell value in printable format
     */
    virtual string Print() const = 0;

    /**
     * Sets cell value.
     *
     * @param value Cell value
     */
    virtual void SetValue(const string &value) = 0;

    /**
     * Checks if cell can be linked to by other cells.
     *
     * @return TRUE if cell is linkable, FALSE otherwise
     */
    virtual bool IsLinkable() const = 0;
};

/**
 * Class that represents numeric value cell.
 */
class CNumber : public CCell {
public:

    string GetValue() const override = 0;

    string Print() const override = 0;

    void SetValue(const string &) override = 0;

    bool IsLinkable() const override;
};

/**
 * Class that represents integer value cell.
 */
class CInteger : public CNumber {
public:

    explicit CInteger(int value);

    string GetValue() const override;

    string Print() const override;

    void SetValue(const string &) override;

private:

    int m_Value;
};

/**
 * Class that represents decimal value cell.
 */
class CDecimal : public CNumber {
public:

    explicit CDecimal(double value);

    string GetValue() const override;

    string Print() const override;

    void SetValue(const string &) override;

private:

    double m_Value;
};

/**
 * Class that represents mathematical formula cell.
 */
class CFormula : public CCell {
public:

    CFormula(const string &, const CSheet &);

    string GetValue() const override;

    string Print() const override;

    void SetValue(const string &) override;

    bool IsLinkable() const override;

protected:

    /** Mathematical formula, @see class CExpression */
    CExpression m_Formula;
};

/**
 * Class that represents label cell.
 */
class CLabel : public CCell {
public:

    explicit CLabel(const string &);

    string GetValue() const override;

    string Print() const override;

    void SetValue(const string &) override;

    bool IsLinkable() const override;

private:

    string m_Label;
};

#endif //VENECJIR_CCELL_H
