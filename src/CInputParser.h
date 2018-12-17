#ifndef VENECJIR_CINPUTPARSER_H
#define VENECJIR_CINPUTPARSER_H

#include <algorithm>

using namespace std;

/**
 * Enumeration of all the cell types.
 */
enum CellTypes {

    integer = 0,
    decimal,
    formula,
    label
};

/**
 * Class that parses user input.
 */
class CInputParser {
public:

    /**
     * Parses given input string.
     *
     * @param[in] input Input string
     * @return TRUE if string is parsed successfully, FALSE otherwise
     */
    bool Parse(const string &input);

    /**
     * Returns result of parsing the input.
     *
     * @return Input data
     */
    string Result() const;

    /**
     * Returns input type.
     *
     * @return Input type, @see enum CellTypes
     */
    int Type() const;

    /**
     * Checks if given string is an integer.
     *
     * @param[in] str String to be examined
     * @return TRUE if string is an integer, FALSE otherwise
     */
    bool IsInteger(const string &str) const;

    /**
     * Checks if given string is a double.
     *
     * @param[in] str String to be examined
     * @return TRUE if string is a double, FALSE otherwise
     */
    bool IsDouble(const string &str) const;

    /**
     * Checks if given string is a formula.
     *
     * @param[in] str String to be examined
     * @return TRUE if string is a formula, FALSE otherwise
     */
    bool IsFormula(const string &str) const;

    /**
     * Checks if given string is a label.
     *
     * @param[in] str String to be examined
     * @return TRUE if string is a label, FALSE otherwise
     */
    bool IsLabel(const string &str) const;

    /**
     * Removes leading and trailing spaces from a string and strips consecutive spaces into one.
     *
     * @param[in] str Input to be modified
     * @return Modified input
     */
    string StripSpaces(const string &str) const;

private:

    /** Parsed input data */
    string m_Result;

    /** Input type */
    int m_Type;
};

#endif //VENECJIR_CINPUTPARSER_H
