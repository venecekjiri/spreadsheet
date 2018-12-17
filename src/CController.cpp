#include <iostream>
#include <climits>

#include "CController.h"
#include "CSheet.h"
#include "CTable.h"
#include "CColorStream.h"

CController::CController(CSheet &m_Sheet) : m_Sheet(m_Sheet) {}

void CController::Run() {

    CTable table(m_Sheet);
    int option(0);
    bool isRunning(true);

    while (isRunning) {

        ClearScreen();
        table.Display();
        DisplayMainOptions();

        if (!ReadOption(option)) {

            Prompt("Invalid option.");
            continue;
        }

        switch (option) {

            case 1: {

                RunDisplayCell();
                continue;
            }

            case 2 : {

                RunEditCell();
                continue;
            }

            case 3 : {

                RunDeleteCell();
                continue;
            }

            case 4 : {

                DisplayHelp();
                continue;
            }

            case 5 : {

                RunSaveSheet();
                continue;
            }

            case 6 : {

                RunLoadSheet();
                break;
            }

            case 7 : {

                RunTableSettings(table);
                break;
            }

            case 8 : {

                isRunning = false;
                break;
            }

            default: {

                Prompt("Invalid option.");
                continue;
            }
        }
    }
}

void CController::ClearScreen() const {

    cout << "\033[2J\033[1;1H";
}

void CController::DisplayMainOptions() const {

    CColorStream boldYellow(Color::FGYellow, Attribute::bold);
    CColorStream boldWhite(Color::FGWhite, Attribute::bold);
    CColorStream def;

    cout << left << boldWhite << LEFT_INDENT
         << "[" << boldYellow << "1" << boldWhite << "] " << setw(12) << "Display"
         << "[" << boldYellow << "2" << boldWhite << "] " << setw(12) << "Edit"
         << "[" << boldYellow << "3" << boldWhite << "] " << setw(12) << "Delete"
         << "[" << boldYellow << "4" << boldWhite << "] " << setw(12) << "Help"
         << "\n" << LEFT_INDENT
         << "[" << boldYellow << "5" << boldWhite << "] " << setw(12) << "Save"
         << "[" << boldYellow << "6" << boldWhite << "] " << setw(12) << "Load"
         << "[" << boldYellow << "7" << boldWhite << "] " << setw(12) << "Settings"
         << "[" << boldYellow << "8" << boldWhite << "] " << setw(12) << "Quit"
         << "\n" << LEFT_INDENT << ": " << def;
}

void CController::RunSaveSheet() const {

    string fileName;
    CColorStream boldBlue(Color::FGBlue, Attribute::bold);
    CColorStream def;

    cout << "\n" << LEFT_INDENT << boldBlue << "Filename" << def << LEFT_INDENT << ": ";

    if (ReadString(fileName) && fileName.find_first_of(' ') == string::npos) {

        if (m_Sheet.SaveToFile(fileName)) {

            Prompt("Sheet saved successfully.");
        } else {

            Prompt("Sheet can't be saved.");
        }
    } else {

        Prompt("Invalid input.");
    }
}

void CController::RunLoadSheet() const {

    string fileName;
    CColorStream boldBlue(Color::FGBlue, Attribute::bold);
    CColorStream def;

    cout << "\n" << LEFT_INDENT << boldBlue << "Filename" << def << LEFT_INDENT << ": ";

    if (ReadString(fileName) && fileName.find_first_of(" \t\n") == string::npos) {

        if (!m_Sheet.LoadFromFile(fileName)) {

            Prompt("File doesn't exist or is corrupted.");
        }
    } else {

        Prompt("Invalid input.");
    }
}

void CController::RunEditCell() const {

    string coordinates;
    CColorStream boldBlue(Color::FGBlue, Attribute::bold);
    CColorStream def;

    cout << "\n" << LEFT_INDENT << boldBlue << "Cell coordinates" << def << LEFT_INDENT << ": ";

    if (ReadCoordinates(coordinates)) {

        string value;

        cout << "\n" << LEFT_INDENT << ": ";

        if (ReadString(value)) {

            if (!m_Sheet.SetCell(coordinates, value)) {

                Prompt("Invalid value or cell can't be set.");
            }
        } else {

            Prompt("Invalid input.");
        }
    } else {

        Prompt("Invalid coordinates.");
    }
}

void CController::RunDisplayCell() const {

    string coordinates;

    CColorStream boldWhite(Color::FGWhite, Attribute::bold);
    CColorStream boldBlue(Color::FGBlue, Attribute::bold);
    CColorStream def;

    cout << "\n" << LEFT_INDENT << boldBlue << "Cell coordinates" << def << LEFT_INDENT << ": ";

    if (!ReadCoordinates(coordinates)) {

        Prompt("Invalid coordinates.");
    } else {

        if (m_Sheet.Find(coordinates)) {

            CColorStream boldYellow(Color::FGYellow, Attribute::bold);

            // Additional output for expressions
            if (m_Sheet.Print(coordinates).at(0) == '=') {

                cout << "\n" << boldYellow << LEFT_INDENT << m_Sheet.GetValue(coordinates) << def;
            }

            Prompt(m_Sheet.Print(coordinates));
        } else {

            Prompt("Cell is empty.");
        }
    }
}

void CController::RunDeleteCell() const {

    string coordinates;
    CColorStream boldBlue(Color::FGBlue, Attribute::bold);
    CColorStream def;

    cout << "\n" << LEFT_INDENT << boldBlue << "Cell coordinates" << def << LEFT_INDENT << ": ";

    if (!ReadCoordinates(coordinates)) {

        Prompt("Invalid coordinates.");
    } else {

        if (!m_Sheet.DeleteCell(coordinates)) {

            Prompt("Cell can't be deleted.");
        }
    }
}

void CController::RunTableSettings(CTable &table) const {

    int option(0);
    CColorStream boldYellow(Color::FGYellow, Attribute::bold);
    CColorStream boldWhite(Color::FGWhite, Attribute::bold);
    CColorStream def;

    cout << "\n" << boldWhite
         << LEFT_INDENT << "[" << boldYellow << "1" << boldWhite << "]" << setw(12) << "Table width" << "\n"
         << LEFT_INDENT << "[" << boldYellow << "2" << boldWhite << "]" << setw(12) << "Table height" << "\n"
         << LEFT_INDENT << "[" << boldYellow << "3" << boldWhite << "]" << setw(12) << "Cell width" << "\n"
         << def << LEFT_INDENT << ": ";

    if (ReadOption(option) && (option == 1 || option == 2 || option == 3)) {

        cout << LEFT_INDENT << "= ";
        int value;

        if (!ReadInteger(value)) {

            Prompt("Invalid input.");
            return;
        }

        switch (option) {

            case 1: {

                if (!table.SetWidth(static_cast<unsigned>(value))) {

                    Prompt("Value not within range.");
                }
                break;
            }

            case 2 : {

                if (!table.SetHeight(static_cast<unsigned>(value))) {

                    Prompt("Value not within range.");
                }
                break;
            }

            case 3: {

                if (!table.SetThickness(static_cast<unsigned>(value))) {

                    Prompt("Value not within range.");
                }
                break;
            }

            default: {

                Prompt("Invalid option.");
            }
        }
    } else {

        Prompt("Invalid option.");
    }
}

void CController::DisplayHelp() const {

    CColorStream boldWhite(Color::FGWhite, Attribute::bold);
    CColorStream boldYellow(Color::FGYellow, Attribute::bold);
    CColorStream def;

    ClearScreen();

    cout << "\n" << boldWhite
         << LEFT_INDENT << boldYellow << "Operands:" << boldWhite << "\n\n"

         << LEFT_INDENT << "+ Addition.\n"
         << LEFT_INDENT << "- Subtraction.\n"
         << LEFT_INDENT << "* Multiplication.\n"
         << LEFT_INDENT << "/ Division.\n\n"

         << LEFT_INDENT << boldYellow << "Functions:" << boldWhite << "\n\n"

         << LEFT_INDENT << "abs Compute absolute value.\n"
         << LEFT_INDENT << "cos Compute cosine.\n"
         << LEFT_INDENT << "sin Compute sine.\n"
         << LEFT_INDENT << "pow Raise to power.\n"
         << LEFT_INDENT << "max Maximum value.\n"
         << LEFT_INDENT << "min Minimum value.\n\n"

         << LEFT_INDENT << boldYellow << "Instructions:" << boldWhite << "\n\n"
         << LEFT_INDENT << "Any mathematical formula, function or link to other cell\n"
         << LEFT_INDENT << "must start with an equal sign (=).\n\n"

         << LEFT_INDENT << "Labels must only contain alphabetical letters, numbers and\n"
         << LEFT_INDENT << "characters \'-\' or \':\'\n\n"

         << LEFT_INDENT << "Any constants can be entered directly.\n\n"

         << LEFT_INDENT << "Sheet supports columns A-Z and rows 1-30.\n\n"

         << LEFT_INDENT << boldYellow << "Description:\n\n" << boldWhite
         << LEFT_INDENT << "Simple spreadsheet editor. By Jiri Venecek." << def;

    Prompt();
}

void CController::Prompt(const string &message) const {

    CColorStream boldYellow(Color::FGYellow, Attribute::bold);
    CColorStream boldWhite(Color::FGWhite, Attribute::bold);
    CColorStream def;

    cout << "\n" << boldYellow
         << LEFT_INDENT << message << def << "\n\n" << boldWhite
         << LEFT_INDENT << "Type anything to continue.." << def << "\n"
         << LEFT_INDENT << ": ";

    char c;
    cin >> c;

    cin.clear();
    cin.ignore(INT_MAX, '\n');
}






