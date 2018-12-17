#include <cassert>

#include "../src/CSheet.h"
#include "../src/CExpression.h"

void TestBrackets(){

    CSheet s0;
    CExpression e0(s0);

    assert("Unexpected result" && e0.Parse("((((((-1)*-1)*-1)*-1)*-1)*-1)*-1") && e0.Evaluate() == -1);
    assert("Unexpected result" && e0.Parse("((2)*(3))*((15)/(3))") && e0.Evaluate() == 30);
    assert("Unexpected result" && e0.Parse("3*(5)+5*(5)") && e0.Evaluate() == 40);
    assert("Unexpected result" && e0.Parse("-(-5)") && e0.Evaluate() == 5);
    assert("Unexpected result" && e0.Parse("-(-(-(-5)))") && e0.Evaluate() == 5);
    assert("Unexpected result" && e0.Parse("(0)-(-1)") && e0.Evaluate() == 1);
    assert("Unexpected result" && e0.Parse("(0*0)*5") && e0.Evaluate() == 0);
    assert("Unexpected result" && e0.Parse("(15+5+9)*(15-15)") && e0.Evaluate() == 0);
    assert("Unexpected result" && e0.Parse("3*5+5") && e0.Evaluate() == 20);
    assert("Unexpected result" && e0.Parse("3*(5+5)") && e0.Evaluate() == 30);
    assert("Unexpected result" && e0.Parse("15/(3+2)") && e0.Evaluate() == 3);
    assert("Unexpected result" && e0.Parse("15/((5)*3)") && e0.Evaluate() == 1);
    assert("Unexpected result" && e0.Parse("25*(-1)*(-1)") && e0.Evaluate() == 25);
}

void TestFunctions(){

    CSheet s0;
    CExpression e0(s0);

    assert("Unexpected result" && e0.Parse("abs(max(-5,-25))") && e0.Evaluate() == 5);
    assert("Unexpected result" && e0.Parse("abs(min(-5,-25))") && e0.Evaluate() == 25);
    assert("Unexpected result" && e0.Parse("abs(-max(3,5))") && e0.Evaluate() == 5);
    assert("Unexpected result" && e0.Parse("abs(-(min(3,5)))") && e0.Evaluate() == 3);

    assert("Unexpected result" && e0.Parse("-(cos(0))") && e0.Evaluate() == -1);
    assert("Unexpected result" && e0.Parse("-(sin(0))") && e0.Evaluate() == 0);
    assert("Unexpected result" && e0.Parse("pow(2,2)") && e0.Evaluate() == 4);
    assert("Unexpected result" && e0.Parse("pow(16,1/2)") && e0.Evaluate() == 4);
    assert("Unexpected result" && e0.Parse("pow(64,1/2)") && e0.Evaluate() == 8);

    assert("Unexpected result" && e0.Parse("abs(-pow(2,(2)*2+6)*-1)") && e0.Evaluate() == 1024);
    assert("Unexpected result" && e0.Parse("-pow((pow(64,1/2))*(pow(64,1/2)),1/2)") && e0.Evaluate() == -8);
    assert("Unexpected result" && e0.Parse("pow(pow(2,2),pow(2,0))") && e0.Evaluate() == 4);
    assert("Unexpected result" && e0.Parse("-(-5)*-1") && e0.Evaluate() == -5);

    assert("Unexpected result" && e0.Parse("abs(-50)") && e0.Evaluate() == 50);
    assert("Unexpected result" && e0.Parse("cos(0)") && e0.Evaluate() == 1);
    assert("Unexpected result" && e0.Parse("sin(0)") && e0.Evaluate() == 0);
    assert("Unexpected result" && e0.Parse("pow(2,2)") && e0.Evaluate() == 4);
    assert("Unexpected result" && e0.Parse("pow(16,1/2)") && e0.Evaluate() == 4);
    assert("Unexpected result" && e0.Parse("pow(16,0)") && e0.Evaluate() == 1);
    assert("Unexpected result" && e0.Parse("max(5,35)") && e0.Evaluate() == 35);
    assert("Unexpected result" && e0.Parse("max(-5,-25)") && e0.Evaluate() == -5);
    assert("Unexpected result" && e0.Parse("min(5,35)") && e0.Evaluate() == 5);
    assert("Unexpected result" && e0.Parse("min(-5,-25)") && e0.Evaluate() == -25);

    assert("Unexpected result" && e0.Parse("abs((-50+5)-(25-10)-(15/5))") && e0.Evaluate() == 63);
    assert("Unexpected result" && e0.Parse("pow(abs((-50+5)-(25-10)-(15/5)),0)") && e0.Evaluate() == 1);

    assert("Unexpected result" && e0.Parse("abs(-2)*3+5") && e0.Evaluate() == 11);
    assert("Unexpected result" && e0.Parse("abs(-2)*(3+5)") && e0.Evaluate() == 16);
}

void TestOperands(){

    CSheet s0;
    CExpression e0(s0);

    assert(e0.Parse("3*5+5") && e0.Evaluate() == 20);
    assert(e0.Parse("3*(5+5)") && e0.Evaluate() == 30);
    assert(e0.Parse("30/5+5") && e0.Evaluate() == 11);
    assert(e0.Parse("30/(5+5)") && e0.Evaluate() == 3);
    assert(e0.Parse("30.256-0.256") && e0.Evaluate() == 30);
    assert(e0.Parse("1/4") && e0.Evaluate() == 0.25);
    assert(e0.Parse("1/4/2") && e0.Evaluate() == 0.125);
    assert(e0.Parse("1/4/2/2") && e0.Evaluate() == 0.0625);
    assert(e0.Parse("1/4*1/2") && e0.Evaluate() == 0.125);
    assert(e0.Parse("-(-25)") && e0.Evaluate() == 25);

    assert(e0.Parse("-(-5-(-25))") && e0.Evaluate() == -20);
    assert(e0.Parse("-((-1)*-1)*-1") && e0.Evaluate() == 1);
    assert(e0.Parse("25/5/5") && e0.Evaluate() == 1);
    assert(e0.Parse("5*5*5") && e0.Evaluate() == 125);
    assert(e0.Parse("5*5+5*5") && e0.Evaluate() == 50);
    assert(e0.Parse("5*(5+5)*5") && e0.Evaluate() == 250);
    assert(e0.Parse("18/9*3") && e0.Evaluate() == 6);
    assert(e0.Parse("(5*(15/3)*7)") && e0.Evaluate() == 175);
    assert(e0.Parse("(26+4)+(15-7)-(25+5)") && e0.Evaluate() == 8);
    assert(e0.Parse("(-50+5)-(25-10)-(15/5)") && e0.Evaluate() == -63);
}

void TestLinks(){

    CSheet s0;
    CExpression e0(s0);

    assert("Cell not set" && s0.SetCell("A1", "15"));
    assert("Cell not set" && s0.SetCell("B1", "=A1*2"));

    assert("Unexpected result" && e0.Parse("A1") && e0.Evaluate() == 15);
    assert("Unexpected result" && e0.Parse("-A1") && e0.Evaluate() == -15);
    assert("Unexpected result" && e0.Parse("A1*-1") && e0.Evaluate() == -15);
    assert("Unexpected result" && e0.Parse("B1*-1") && e0.Evaluate() == -30);

    assert("Cell not set" && s0.SetCell("B1", "=A1*-2"));

    assert("Unexpected result" && e0.Parse("B1*-1") && e0.Evaluate() == 30);
    assert("Unexpected result" && e0.Parse("B1+(-1)") && e0.Evaluate() == -31);

    assert("Unexpected result" && e0.Parse("B1") && e0.Evaluate() == -30);

    assert("Cell not set" && s0.SetCell("A1", "1"));

    assert("Unexpected result" && e0.Parse("B1") && e0.Evaluate() == -2);
}

void TestCExpression(){

    TestBrackets();
    TestFunctions();
    TestOperands();
    TestLinks();
}
