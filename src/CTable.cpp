#include <iostream>

#include "CTable.h"
#include "CSheet.h"
#include "CColorStream.h"

CTable::CTable(const CSheet &m_Sheet) : m_Sheet(m_Sheet) {}

string CTable::DisplayCell(const pair<int, int> &numberCoordinates) const {

    string coordinates;
    CColorStream red(Color::FGRed, Attribute::bold_off);
    CColorStream def;

    coordinates = static_cast<char>(numberCoordinates.first + 'A'); // Assign x coordinate corresponding letter
    coordinates += to_string(numberCoordinates.second);

    if (m_Sheet.Find(coordinates)) {

        string result = m_Sheet.GetValue(coordinates);

        if (result.length() <= m_CellWidth) {

            return result;
        } else {

            ostringstream oss;
            oss << result.substr(0, m_CellWidth - 3)
                << red << "..." << def;

            return oss.str();
        }
    }

    return Repeat(m_CellWidth, ' ');
}

string CTable::DisplayTopRow() const {

    string result;

    result = Repeat(m_LeftIndent + 1, ' ');

    for (unsigned i = 0; i < m_Width; ++i) {

        result += DisplayTopCoordinate((char) i + 'A');
    }

    return result;
}

string CTable::DisplayLine() const {

    ostringstream result;
    CColorStream blue(Color::FGBlue, Attribute::bold_off);
    CColorStream def;

    // First corner
    result << Repeat(m_LeftIndent, ' ') << blue << m_Corner << def;

    // Rest of the line
    for (unsigned i = 0; i < m_Width; ++i) {

        result << blue << Repeat(m_CellWidth, m_Horizontal) << m_Corner << def;
    }

    return result.str();
}

void CTable::Display() const{

    CColorStream boldYellow(Color::FGYellow, Attribute::bold);
    CColorStream boldWhite(Color::FGWhite, Attribute::bold);
    CColorStream def;

    cout << "\n";

    cout << DisplayTopRow() << "\n";
    cout << DisplayLine() << "\n";

    for (unsigned i = 1; i < m_Height + 1; ++i) {

        // Display line numbers
        cout << boldYellow << right << setw(2) << i << def;

        cout << DisplayVertical();

        for (unsigned j = 0; j < m_Width; ++j) {

            // Display cell
            cout << boldWhite << setw(m_CellWidth)
                 << right
                 << DisplayCell(make_pair(j, i)) << def;

            cout << DisplayVertical();
        }

        cout << "\n" << DisplayLine() << "\n";
    }

    cout << "\n";
}

string CTable::Repeat(int numberOfTimes, char character) const {

    string result;

    for (int i = 0; i < numberOfTimes; ++i) {
        result.push_back(character);
    }

    return result;
}

string CTable::DisplayTopCoordinate(char coordinate) const {

    ostringstream oss;
    CColorStream boldYellow(Color::FGYellow, Attribute::bold);
    CColorStream def;

    int leftPadding = m_CellWidth / 2;
    int rightPadding = m_CellWidth - leftPadding;

    oss << Repeat(leftPadding, ' ');
    oss << boldYellow << coordinate << def;
    oss << Repeat(rightPadding, ' ');

    return oss.str();
}

bool CTable::SetThickness(unsigned int thickness) {

    if (thickness > MAX_THICKNESS
        || thickness < MIN_THICKNESS
            )
        return false;

    m_CellWidth = thickness;

    return true;
}

bool CTable::SetHeight(unsigned int height) {

    if (height < 1 || height > MAX_HEIGHT)
        return false;

    m_Height = height;

    return true;
}

bool CTable::SetWidth(unsigned int width) {

    if (width < 1 || width > MAX_WIDTH)
        return false;

    m_Width = width;

    return true;
}

string CTable::DisplayVertical() const {

    ostringstream oss;
    CColorStream blue(Color::FGBlue, Attribute::bold_off);
    CColorStream def;

    oss << blue << m_Vertical << def;

    return oss.str();
}
