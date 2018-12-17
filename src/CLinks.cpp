#include "CLinks.h"

void CLinks::Set(const string &coordinates, const set<string> &connections) {

    m_Links[coordinates] = connections;
}

bool CLinks::SafeSet(const string &coordinates, const set<string> &connections) {

    pair<string, set<string> > save;

    bool useSaved(false); // Use newly overwritten data

    const auto &it = m_Links.find(coordinates);

    // There is data to be overwritten - save it
    if (it != m_Links.end()) {

        save = make_pair(it->first, it->second);
        useSaved = true;
    }

    m_Links[coordinates] = connections;

    if (IsCyclic()) { // Cycle found - go back to the old data

        if (useSaved) {

            m_Links[save.first] = save.second;
        } else {

            m_Links[coordinates].clear();
        }

        return false;
    }

    return true;
}

bool CLinks::Delete(const string &coordinates) {

    if (m_Links.find(coordinates) != m_Links.end()) {

        m_Links.erase(coordinates);

        return true;
    }

    return false;
}

bool CLinks::IsCyclic() const {

    map<string, bool> visited;
    map<string, bool> stack;

    for (auto &it : m_Links) {

        visited.insert(make_pair(it.first, false));
        stack.insert(make_pair(it.first, false));
    }

    for (const auto &it : m_Links) {

        if (DetectCycle(it.first, visited, stack)) {

            return true;
        }
    }

    return false;
}

bool CLinks::DetectCycle(const string &coordinates, map<string, bool> &visited, map<string, bool> &stack) const {

    if (!visited.at(coordinates)) {

        visited[coordinates] = true;
        stack[coordinates] = true;

        for (const string &link : m_Links.at(coordinates)) {

            if (!visited.at(link) && DetectCycle(link, visited, stack)) {

                return true;
            } else if (stack.at(link)) {

                return true;
            }
        }
    }

    stack[coordinates] = false;
    return false;
}

void CLinks::Clear() {

    m_Links.clear();
}

bool CLinks::ValidateLinks(const set<string> &links) const {

    for (const string &it : links) {

        if (m_Links.find(it) == m_Links.end()) {

            return false;
        }
    }

    return true;
}

bool CLinks::ValidateLinks() const {

    for (const auto &data : m_Links) {

        for (const string &link : data.second) {

            if (m_Links.find(link) == m_Links.end()) {

                return false;
            }
        }
    }

    return true;
}

bool CLinks::FindLink(const string &coordinates) const {

    for (const auto &data : m_Links) {

        if (data.second.find(coordinates) != data.second.end()) {

            return true;
        }
    }

    return false;
}

set<string> CLinks::ParseLinks(const string &expression) const {

    set<string> res;

    string::const_iterator it = expression.begin();

    while (it != expression.end()) {

        // Coordinate starts with capital letter followed by an integer
        if (isupper(*it) && it + 1 != expression.end() && isdigit(*(it + 1))) {

            string s;
            s.push_back(*it++);

            while (it != expression.end() && isdigit(*it)) {
                s.push_back(*it++);
            }

            res.insert(s);
            continue;
        }

        it++;
    }

    return move(res);
}

