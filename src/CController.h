#ifndef VENECJIR_CCONTROLLER_H
#define VENECJIR_CCONTROLLER_H

#include "CInputReader.h"

class CSheet;
class CTable;

using namespace std;

/**
 * Class that allows user to control the program.
 */
class CController : public CInputReader{
public:

    /**
     * Constructor takes reference to sheet.
     *
     * @param m_Sheet Reference to programs current sheet
     */
    explicit CController(CSheet& m_Sheet);

    /**
     * Runs controller
     */
    void Run();

private:

    CSheet& m_Sheet;

    /**
    * Clears screen.
    */
    void ClearScreen() const;

    /**
     * Displays main options.
     */
    void DisplayMainOptions() const;

    /**
     * Alowes user to save the sheet to file.
     */
    void RunSaveSheet() const;

    /**
     * Alowes user to load the sheet from file.
     */
    void RunLoadSheet() const;

    /**
     * Alowes user to edit cell.
     */
    void RunEditCell() const;

    /**
     * Alowes user to delete cell.
     */
    void RunDeleteCell() const;

    /**
     * Alowes user to display cell.
     */
    void RunDisplayCell() const;

    /**
     * Alowes user to change the table settings
     *
     * @param table Reference to the table
     */
    void RunTableSettings(CTable& table) const;

    /**
     * Displays short information about the program.
     */
    void DisplayHelp() const;

    /**
     * Prompts user with a message.
     *
     * @param message Message to be output
     */
    void Prompt(const string &message = "") const;

    /** String used as left indent */
    const string LEFT_INDENT = "  ";
};

#endif //VENECJIR_CCONTROLLER_H
