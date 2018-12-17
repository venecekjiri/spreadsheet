#include "CInputReader.h"

#include <iostream>

bool CInputReader::ReadInteger(int &integer) const {

    string line;

    cin >> ws;
    getline(cin, line);

    if (line.find_first_not_of("0123456789") == string::npos) {

        try {

            integer = stoi(line);
        }
        catch (...) {

            return false;
        }

        return true;
    }

    return false;
}

bool CInputReader::ReadString(string &str) const {

    string line;

    cin >> ws;
    getline(cin, line);

    if (line.length() && line.find_first_not_of(" \n\t") != string::npos) {

        str = line;

        return true;
    }

    return false;
}

bool CInputReader::ReadOption(int &option) const {

    string line;

    cin >> ws;
    getline(cin, line);

    if (line.length() == 1 && isdigit(line.at(0))) {

        option = stoi(line);
        return true;
    }

    return false;
}

bool CInputReader::ReadCoordinates(string &coordinates) const {

    string line;

    cin >> ws;
    getline(cin, line);

    // Check if coordinate starts with a letter followed by at most two digit number
    if (line.length() >= 2
        && line.length() <= 3
        && isalpha(line[0])
        && line.find_first_not_of("0123456789", 1) == string::npos
       ){

        line[0] = static_cast<char>(toupper(line.at(0)));
        coordinates = line;

        return true;
    }

    return false;
}
