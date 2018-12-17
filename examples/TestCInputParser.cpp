#include <cassert>

#include "../src/CInputParser.h"

void TestCellTypeSort(){

    CInputParser p0;

    assert(p0.Parse("=15*8") && p0.Type() == CellTypes::formula && p0.Result() == "15*8");
    assert(p0.Parse("=abs(-1*8)") && p0.Type() == CellTypes::formula && p0.Result() == "abs(-1*8)");
    assert(p0.Parse("=2-(-2)") && p0.Type() == CellTypes::formula && p0.Result() == "2-(-2)");
    assert(p0.Parse("=-(-1)") && p0.Type() == CellTypes::formula && p0.Result() == "-(-1)");

    assert(p0.Parse("Hello world") && p0.Type() == CellTypes::label && p0.Result() == "Hello world");
    assert(p0.Parse("total") && p0.Type() == CellTypes::label && p0.Result() == "total");
    assert(p0.Parse("sum") && p0.Type() == CellTypes::label && p0.Result() == "sum");

    assert(p0.Parse("12.2") && p0.Type() == CellTypes::decimal && p0.Result() == "12.2");
    assert(p0.Parse("3.141592867254") && p0.Type() == CellTypes::decimal && p0.Result() == "3.141592867254");
    assert(p0.Parse("0.125") && p0.Type() == CellTypes::decimal && p0.Result() == "0.125");

    assert(p0.Parse("125") && p0.Type() == CellTypes::integer && p0.Result() == "125");
    assert(p0.Parse("-125") && p0.Type() == CellTypes::integer && p0.Result() == "-125");
    assert(p0.Parse("123456789") && p0.Type() == CellTypes::integer && p0.Result() == "123456789");
}

void TestTrimmingSpaces(){

    CInputParser p0;

    assert(p0.Parse("   =    15    *    8  ") && p0.Type() == CellTypes::formula && p0.Result() == "15*8");
    assert(p0.Parse("  Hello        world  ") && p0.Type() == CellTypes::label && p0.Result() == "Hello world");
    assert(p0.Parse("    1542134           ") && p0.Type() == CellTypes::integer && p0.Result() == "1542134");
    assert(p0.Parse("      -1542134        ") && p0.Type() == CellTypes::integer && p0.Result() == "-1542134");
    assert(p0.Parse("    -15.3256          ") && p0.Type() == CellTypes::decimal && p0.Result() == "-15.3256");
    assert(p0.Parse(" 15.3256              ") && p0.Type() == CellTypes::decimal && p0.Result() == "15.3256");
    assert(p0.Parse("=12  *  8") && p0.Type() == CellTypes::formula && p0.Result() == "12*8");
    assert(p0.Parse(" h  e  l  o ") && p0.Type() == CellTypes::label && p0.Result() == "h e l o");
}

void TestInvalidInput(){

    CInputParser p0;

    assert(! p0.Parse("A3;A2"));
    assert(! p0.Parse("\"Hello\""));
    assert(! p0.Parse("\'Hello\'"));
    assert(! p0.Parse("85/85"));
    assert(! p0.Parse("85.85.85.85"));
    assert(! p0.Parse("==A1"));
    assert(! p0.Parse("89*9"));
    assert(! p0.Parse("abs(-252)"));
    assert(! p0.Parse("abs(-252)"));
    assert(! p0.Parse(" "));
    assert(! p0.Parse("="));
    assert(! p0.Parse(""));
    assert(! p0.Parse("/"));
    assert(! p0.Parse("[()]"));
    assert(! p0.Parse("\n"));
    assert(! p0.Parse("\t"));
    assert(! p0.Parse("\t\n\n"));
    assert(! p0.Parse("   "));
}

void TestCInputParser(){

    TestCellTypeSort();
    TestTrimmingSpaces();
    TestInvalidInput();
}
