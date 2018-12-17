#ifndef VENECJIR_CINPUTREADER_H
#define VENECJIR_CINPUTREADER_H

#include <string>

using namespace std;

/**
 * Class that has useful methods to get user input.
 */
class CInputReader{
public:

    /**
     * Reads an integer.
     *
     * @param[in,out] integer Reference to an integer variable the input is stored to
     * @return TRUE if read is successfull, FALSE otherwise
     */
    bool ReadInteger(int &integer) const;

    /**
     * Reads string. String can't be empty and has to have at least one non
     * white space character.
     *
     * @param[in,out] str Reference to a string variable the input is stored to
     * @return TRUE if read is successfull, FALSE otherwise
     */
    bool ReadString(string &str) const;

    /**
     * Reads a menu option. Option si a single digit number.
     *
     * @param[in,out] option Reference to a variable the input is stored to
     * @return TRUE if read is successfull, FALSE otherwise
     */
    bool ReadOption(int &option) const;

    /**
     * Reads cell coordinates. Coordinate starts with a single letter followed
     * by at most two digit number.
     *
     * @param[in,out] coordinates Reference to a variable the input is stored to
     * @return TRUE if read is successfull, FALSE otherwise
     */
    bool ReadCoordinates(string &coordinates) const;
};

#endif //VENECJIR_CINPUTREADER_H
