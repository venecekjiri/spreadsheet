#include "CApplication.h"

#include <iostream>
#include <exception>

using namespace std;

int main() {

    CApplication app;

    try {

        app.Run();
    } catch (const exception &e) {

        cerr << e.what() << endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
