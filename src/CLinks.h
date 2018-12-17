#ifndef VENECJIR_CLINKS_H
#define VENECJIR_CLINKS_H

#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

/**
 * Class that keeps track of cell links in the sheet. Detects cycles and validates its links.
 */
class CLinks {
public:

    /**
     * Sets cell links without any checks. Useful when setting from a file where
     * content is in random order.
     *
     * @param[in] coordinates Cell coordinates
     * @param[in] links Set of links belonging to the cell in the first parameter
     */
    void Set(const string &coordinates, const set<string> &links);

    /**
     * Sets cell links and checks if cycle wasn't created.
     *
     * @param[in] coordinates Cell coordinates
     * @param[in] links Set of links belonging to the cell in the first parameter
     * @return TRUE if links are set and cycle isn't created, FALSE otherwise
     */
    bool SafeSet(const string &coordinates, const set<string> &links);

    /**
     * Deletes cell and its links.
     *
     * @param[in] coordinates Cell coordinates
     * @return TRUE if cell is deleted, FALSE otherwise
     */
    bool Delete(const string &coordinates);

    /**
     * Checks if all given links have a valid targets.
     *
     * @param[in] connections Links to be validated
     * @return TRUE if cycle isn't detected, FALSE otherwise
     */
    bool ValidateLinks(const set<string> &connections) const;

    /**
     * Checks if all current links have a valid target.
     *
     * @return TRUE if member links don't create a cycle, FALSE otherwise
     */
    bool ValidateLinks() const;

    /**
    * Finds all links in input expression string.
     *
    * @param[in] expression Given cell expression as string
    * @return Set of links
    */
    set<string> ParseLinks(const string& expression) const;

    /**
     * Checks if given cell exists in other cells links.
     *
     * @param[in] coordinates Cell coordinates
     * @return TRUE if cell is found in others links, FALSE otherwise
     */
    bool FindLink(const string &coordinates) const;

    /**
     * Detects cycle in cell links.
     *
     * @return TRUE if links create a cycle, FALSE otherwise
     */
    bool IsCyclic() const;

    /**
     * Removes all links.
     */
    void Clear();

private:

    /**
     * Performs recursive search to detect cell cycles. Uses modified
     * version of the DFS algorithm.
     *
     * @param[in] coordinates Cell coordinates
     * @param[in] visited Set of already visited cells
     * @param[in] stack Recursion stack
     * @return TRUE if cycle is detected, FALSE otherwise
     */
    bool DetectCycle(const string &coordinates, map<string, bool> &visited, map<string, bool> &stack) const;

    /** Map of cell coordinates and corresponding links */
    map<string, set<string> > m_Links;
};

#endif //VENECJIR_CLINKS_H
