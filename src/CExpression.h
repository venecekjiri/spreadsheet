#ifndef VENECJIR_CEXPRESSION_H
#define VENECJIR_CEXPRESSION_H

#include <string>
#include <sstream>
#include <map>

#include "CNode.h"

using namespace std;

/**
 * Class that represents mathematical expression. Parses string input into binary expression tree.
 */
class CExpression {
public:

    /**
     * Constructor takes reference to a sheet. Allows for links to be evaluated.
     *
     * @param[in] m_Sheet Sheet reference
     */
    explicit CExpression(const CSheet &m_Sheet);

    /**
     * Parses string expression into binary expression tree.
     *
     * @param[in] expression Given expression as string
     * @return TRUE if input is parsed successfully, FALSE otherwise
     */
    bool Parse(const string &expression);

    /**
     * Assignment operator allows expression to changed.
     *
     * @param[in] expression Given expression as string
     * @return TRUE if input is parsed successfully, FALSE otherwise
     */
    CExpression &operator=(const string &expression);

    /**
     * Evaluates expression.
     *
     * @return Expression value
     */
    double Evaluate() const;

    /**
     * Returns expression in string format.
     *
     * @return Expression as string
     */
    string Print() const;

private:

    /** Head of binary expression tree. */
    shared_ptr<CNode> m_Head;

    /**
     * Parses cell links.
     *
     * @param[in] iterator Current string position in the process
     * @return Pointer to the new link node
     */
    unique_ptr<CNode> ParseLink(string::const_iterator &iterator);

    /**
     * Parses brackets.
     *
     * @param[in] iterator Current string position in the process
     * @return Pointer to the new brackets node
     */
    unique_ptr<CNode> ParseBracket(string::const_iterator &iterator);

    /**
     * Parses functions.
     *
     * @param[in] iterator Current string position in the process
     * @return Pointer to the new function node
     */
    unique_ptr<CNode> ParseFunction(string::const_iterator &iterator);

    /**
     * Parses numbers.
     *
     * @param[in] iterator Current string position in the process
     * @return Pointer to the new number node
     */
    unique_ptr<CNode> ParseNumber(string::const_iterator &iterator);

    /**
     * Parses addition and subtraction.
     *
     * @param iterator Current string position in the process
     * @return Pointer to the new summand node
     */
    unique_ptr<CNode> ParseSummand(string::const_iterator &iterator);

    /**
     * Parses multiplication and division.
     *
     * @param iterator Current string position in the process
     * @return Pointer to the new factor node
     */
    unique_ptr<CNode> ParseFactor(string::const_iterator &iterator);

    /** Expression in string format */
    string m_ExpressionAsString;

    /** Reference to the corresponding sheet */
    const CSheet &m_Sheet;
};

#endif //VENECJIR_CEXPRESSION_H
