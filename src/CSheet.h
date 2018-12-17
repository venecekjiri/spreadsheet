#ifndef VENECJIR_CSHEET_H
#define VENECJIR_CSHEET_H

#include "CCell.h"
#include "CLinks.h"

using namespace std;

/**
 * Class that stores cells and their corresponding links.
 */
class CSheet {
public:

    /**
     * Finds given cell in the sheet.
     *
     * @param[in] coordinates Coordinates of the cell to be found
     * @return TRUE if cell is found, FALSE otherwise
     */
    bool Find(const string &coordinates) const;

    /**
     * Gets cell value.
     *
     * @param[in] coordinates Coordinates of the cell to be found
     * @return Cell value
     */
    string GetValue(const string &coordinates) const;

    /**
     * Gets cell value in printable format.
     *
     * @param[in] coordinates Coordinates of the cell to be found
     * @return Cell value in printable format
     */
    string Print(const string &coordinates) const;

    /**
     * Sets cell to given value.
     *
     * @param[in] coordinates Coordinates of the cell to be found
     * @param[in] value Given cell value
     * @param[in] fromFile TRUE if cell is being set from file, FALSE otherwise
     * @return TRUE if cell is set, FALSE otherwise
     */
    bool SetCell(const string &coordinates, const string &value, bool fromFile = false);

    /**
     * Deletes given cell.
     *
     * @return TRUE if cell is deleted, FALSE otherwise
     */
    bool DeleteCell(const string &);

    /**
     * Saves sheet contents to a file.
     *
     * @param[in] fileName Destination file name
     * @return TRUE if save is successfull, FALSE otherwise
     */
    bool SaveToFile(const string &fileName) const;

    /**
     * Loads sheet contents from a file.
     *
     * @param[in] fileName Source file name
     * @return TRUE if file is loaded successfully
     */
    bool LoadFromFile(const string &fileName);

private:

    /** Map that holds cell coordinates and pointer to the actual cell object */
    map<string, unique_ptr<CCell> > m_Data;

    /** Class that holds information about cell links, @see class CLinks */
    CLinks m_Links;
};

#endif //VENECJIR_CSHEET_H
