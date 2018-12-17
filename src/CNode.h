#ifndef VENECJIR_CNODE_H
#define VENECJIR_CNODE_H

#include <memory>

class CSheet;

using namespace std;

/**
 * Class that represents a single node in binary expression tree.
 */
class CNode {
public:

    virtual ~CNode() = default;

    /**
     * Calculates node value.
     *
     * @return Node value
     */
    virtual double Calculate() const = 0;
};

/**
 * Class that represents binary predicates.
 */
class CBinaryPredicate : public CNode {
public:

    /**
     * Constructor takes left and right side node pointers.
     *
     * @param[in] m_Left Left side of the expression
     * @param[in] m_Right Right side of the expression
     */
    CBinaryPredicate(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right);

    double Calculate() const override = 0;

protected:

    /** Left side of the predicate */
    unique_ptr<CNode> m_Left;

    /** Right side of the predicate */
    unique_ptr<CNode> m_Right;
};

/**
 * Class that represents unary predicates.
 */
class CUnaryPredicate : public CNode {
public:

    /**
     * Constructor takes pointer to a child node.
     *
     * @param[in] m_Child Child node.
     */
    explicit CUnaryPredicate(unique_ptr<CNode> m_Child);

    double Calculate() const override = 0;

protected:

    /** Child of the predicate */
    unique_ptr<CNode> m_Child;
};

/**
 * Class that represents binary functions.
 */
class CBinaryFunction : public CBinaryPredicate {
public:

    CBinaryFunction(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right);

    double Calculate() const override = 0;

};

/**
 * Class that represents unary functions.
 */
class CUnaryFunction : public CUnaryPredicate {
public:

    explicit CUnaryFunction(unique_ptr<CNode> m_Child);

    double Calculate() const override = 0;
};

/**
 * Node that represents absolute value function.
 */
class CAbs : public CUnaryFunction {
public:

    explicit CAbs(unique_ptr<CNode> m_Child);

    double Calculate() const override;
};

/**
 * Node that represents sine function.
 */
class CSin : public CUnaryFunction {
public:

    explicit CSin(unique_ptr<CNode> m_Child);

    double Calculate() const override;
};

/**
 * Node that represents cosine function.
 */
class CCos : public CUnaryFunction {
public:

    explicit CCos(unique_ptr<CNode> m_Child);

    double Calculate() const override;
};

/**
 * Node that represents max function.
 * Greater of two values is returned when evaluated.
 */
class CMax : public CBinaryFunction {
public:

    CMax(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right);

    double Calculate() const override;
};

/**
 * Node that represents min function.
 * Lesser of two values is returned when evaluated.
 */
class CMin : public CBinaryFunction {
public:

    CMin(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right);

    double Calculate() const override;
};

/**
 * Node that represents power function.
 * Left side is raised to the power of the right side when evaluated.
 */
class CPow : public CBinaryFunction {
public:

    CPow(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right);

    double Calculate() const override;
};

/**
 * Node that represents brackets.
 */
class CBrackets : public CUnaryPredicate {
public:

    explicit CBrackets(unique_ptr<CNode> m_Child);

    double Calculate() const override;
};

/**
 * Node that represents unary minus sign.
 */
class CNegation : public CUnaryPredicate {
public:

    explicit CNegation(unique_ptr<CNode> m_Child);

    double Calculate() const override;
};

/**
 * Node that represents addition.
 */
class CPlus : public CBinaryPredicate {
public:

    CPlus(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right);

    double Calculate() const override;
};

/**
 * Node that represents subtraction.
 */
class CMinus : public CBinaryPredicate {
public:

    explicit CMinus(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right);

    double Calculate() const override;
};

/**
 * Node that represents multiplication.
 */
class CMultiply : public CBinaryPredicate {
public:

    CMultiply(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right);

    double Calculate() const override;
};

/**
 * Node that represents division.
 */
class CDivide : public CBinaryPredicate {
public:

    CDivide(unique_ptr<CNode> m_Left, unique_ptr<CNode> m_Right);

    double Calculate() const override;
};

/**
 * Node that represents numeric value.
 */
class CValue : public CNode {
public:

    /**
     * Constructor that sets node to value.
     *
     * @param[in] m_Value Value to be set
     */
    explicit CValue(double m_Value);

    double Calculate() const override;

protected:

    /** Node value */
    double m_Value;
};

/**
 * Node represents link to other cells.
 */
class CLink : public CNode {
public:

    /**
     * Constructor that takes reference to a sheet and coordinates of a cell to be linked.
     *
     * @param m_Sheet Sheet reference
     * @param m_Coordinates Coordinates of cell that is to be linked
     */
    CLink(const CSheet &m_Sheet, const string &m_Coordinates);

    double Calculate() const override;

protected:

    /** Reference to sheet cell coordinates belong to */
    const CSheet &m_Sheet;

    /** Coordinates of cell that is to be linked */
    string m_Coordinates;
};

#endif //VENECJIR_CNODE_H
