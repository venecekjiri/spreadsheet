#ifndef VENECJIR_CTABLE_H
#define VENECJIR_CTABLE_H

#include <iomanip>

class CSheet;

using namespace std;

/**
 * Class that prints sheet in table format.
 */
class CTable {
public:

    /**
     * Constructor that takes reference to a sheet to be displayed.
     *
     * @param[in] m_Sheet Given sheet
     */
    explicit CTable(const CSheet &m_Sheet);

    /**
     * Sets table width.
     *
     * @return TRUE if table width is set, FALSE otherwise
     */
    bool SetWidth(unsigned int);

    /**
     * Displays table.
     */
    void Display() const;

    /**
     * Sets table height.
     *
     * @return TRUE if table height is set, FALSE otherwise
     */
    bool SetHeight(unsigned int);

    /**
     * Sets cell thickness.
     *
     * @return TRUE if cell thickness is set, FALSE otherwise
     */
    bool SetThickness(unsigned int);

private:

    /**
     * Displays cell content.
     *
     * @param[in] coordinates Coordinates of the cell to be displayed.
     * @return Cell content in printable format
     */
    string DisplayCell(const pair<int, int> &coordinates) const;

    /**
     * Displays top row coordinates.
     *
     * @param[in] character Top row coordinate
     * @return Centered top row coordinate in printable format
     */
    string DisplayTopCoordinate(char character) const;

    /**
     * Displays top row.
     *
     * @return Top row in printable format
     */
    string DisplayTopRow() const;

    /**
     * Displays horizontal line separating cells in the table.
     *
     * @return Horizontal line in printable format
     */
    string DisplayLine() const;

    /**
     * Displays vertical cell separator.
     *
     * @return Vertical separator in printable format
     */
    string DisplayVertical() const;

    /**
     * Repeats character number of times.
     *
     * @param numberOfTimes How many times is the character set to be repeated
     * @param character Character to be repeated
     * @return Result as string
     */
    string Repeat(int numberOfTimes, char character) const;

    /** Reference to the sheet to be displayed */
    const CSheet &m_Sheet;

    /** Cell width */
    unsigned m_CellWidth = 10;

    /** Table width */
    unsigned m_Width = 7;

    /** Table height */
    unsigned m_Height = 10;

    /** Left side indent */
    static const int m_LeftIndent = 2;

    /** Maximal displayable table width */
    static const int MAX_WIDTH = 26;

    /** Maximal displayable table height */
    static const int MAX_HEIGHT = 30;

    /** Maximal displayable cell width */
    static const int MAX_THICKNESS = 15;

    /** Minimal displayable cell width */
    static const int MIN_THICKNESS = 3;

    /** Horizontal cell separator */
    char m_Horizontal = '-';

    /** Vertical cell separator */
    char m_Vertical = '|';

    /** Cell corner */
    char m_Corner = '+';
};

#endif //VENECJIR_CTABLE_H
