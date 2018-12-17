#ifndef VENECJIR_CINVALIDCOORDINATES_H
#define VENECJIR_CINVALIDCOORDINATES_H

#include <exception>

/**
 * Exception indicating invalid coordinates were detected.
 */
class CInvalidCoordinates : public exception{

    /**
     * Shows error message.
     *
     * @return Error message
     */
    const char* what() const throw() override{

        return "Invalid cell coordinates.";
    }
};

#endif //VENECJIR_CINVALIDCOORDINATES_H
