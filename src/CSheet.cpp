#include "CSheet.h"
#include "CInputParser.h"
#include "CInvalidFormat.h"
#include "CInvalidCoordinates.h"

#include <string>
#include <algorithm>
#include <fstream>

bool CSheet::SetCell(const string &coordinates, const string &value, bool fromFile) {

    CInputParser inputParser;

    unique_ptr<CCell> cell;
    set<string> links;

    if (! inputParser.Parse(value))
        return false;

    switch (inputParser.Type()) {

        case CellTypes::integer : {

            cell = make_unique<CInteger>(CInteger(stoi(inputParser.Result())));

            m_Links.Set(coordinates, links);

            break;
        }

        case CellTypes::decimal : {

            cell = make_unique<CDecimal>(CDecimal(stod(inputParser.Result())));

            m_Links.Set(coordinates, links);

            break;
        }

        case CellTypes::formula : {

            try {

                cell = make_unique<CFormula>(CFormula(inputParser.Result(), *this));
            }
            catch (const CInvalidFormat &e) {

                return false;
            }

            links = m_Links.ParseLinks(value);

            if (!fromFile) { // Not setting from file - check immediately

                if (m_Links.ValidateLinks(links) && m_Links.SafeSet(coordinates, links)) {

                    break;
                } else {

                    return false;
                }
            } else {

                m_Links.Set(coordinates, links);

                break;
            }
        }

        case CellTypes::label : {

            // Avoid link to label
            if (m_Links.FindLink(coordinates)) {

                return false;
            }

            cell = make_unique<CLabel>(CLabel(inputParser.Result()));

            break;
        }

        default:
            return false;
    }

    m_Data[coordinates] = move(cell);

    return true;
}

bool CSheet::DeleteCell(const string &coordinates) {

    if (m_Data.find(coordinates) != m_Data.end()
        && !m_Links.FindLink(coordinates)) {

        m_Data.erase(coordinates);
        m_Links.Delete(coordinates);

        return true;
    }

    return false;
}

string CSheet::GetValue(const string &coordinates) const {

    if (m_Data.find(coordinates) != m_Data.end()) {

        return m_Data.at(coordinates)->GetValue();
    }

    throw CInvalidCoordinates();
}

string CSheet::Print(const string &coordinates) const {

    if (m_Data.find(coordinates) != m_Data.end()) {

        return m_Data.at(coordinates)->Print();
    }

    throw CInvalidCoordinates();
}

bool CSheet::Find(const string &coordinates) const {

    return m_Data.find(coordinates) != m_Data.end();
}

bool CSheet::SaveToFile(const string &fileName) const {

    ofstream output;
    output.open(fileName);

    if (output.is_open()) {

        for (const auto &cell : m_Data) {

            output << cell.first << ';';
            output << cell.second->Print() << "\n";
        }

        return true;
    }

    return false;
}

bool CSheet::LoadFromFile(const string &fileName) {

    ifstream input;
    input.open(fileName);

    if (input.is_open()) {

        m_Data.clear();
        m_Links.Clear();

        while (input) {

            string cell;
            string value;

            getline(input, cell, ';');
            getline(input, value, '\n');

            input >> ws;

            if (!input) {

                break;
            }

            if (!SetCell(cell, value, true)) {

                return false;
            }
        }

        if (m_Links.ValidateLinks() && ! m_Links.IsCyclic()) {

            return true;
        } else {

            m_Data.clear();
            m_Links.Clear();
        }
    }

    return false;
}

