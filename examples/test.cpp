#include <iostream>

#include "../examples/TestCExpression.cpp"
#include "../examples/TestCSheet.cpp"
#include "../examples/TestCInputParser.cpp"

using namespace std;

int main(){

    TestCExpression();
    cout << "Expression test success." << endl;

    TestCInputParser();
    cout << "Input parser test success." << endl;

    TestCSheet();
    cout << "Sheet test success." << endl;

    return 0;
}