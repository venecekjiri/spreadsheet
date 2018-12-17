#ifndef VENECJIR_CINVALIDFORMAT_H
#define VENECJIR_CINVALIDFORMAT_H

#include <exception>

/**
 * Exception indicating invalid expression format was detected.
 */
class CInvalidFormat : public exception{

    /**
     * Shows error message.
     *
     * @return Error message
     */
    const char* what() const throw() override{

        return "Invalid expression format.";
    }
};

#endif //VENECJIR_CINVALIDFORMAT_H
