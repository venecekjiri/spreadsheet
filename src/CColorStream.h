#ifndef VENECJIR_CCOLORSTREAM_H
#define VENECJIR_CCOLORSTREAM_H

/**
 * Enumeration of all available colors.
 */
enum Color {

    FGBlack = 30,
    FGRed = 31,
    FGGreen = 32,
    FGYellow = 33,
    FGBlue = 34,
    FGMagneta = 35,
    FGCyan = 36,
    FGWhite = 37,
    FGDefault = 39
};
/**
 * Enumeration of all output attributes.
 */
enum Attribute {

    reset = 0,
    bold = 1,
    inverse = 7,
    bold_off = 21
};

/**
 * Class modifying output stream by adding color and attributes.
 */
class CColorStream {
public:

    /**
     * Constructor that sets color to default and resets attributes.
     */
    CColorStream() : m_Color(Color::FGDefault), m_Attribute(Attribute::reset) {}

    /**
     * Constructor takes color code together with attribute and saves them for use.
     *
     * @param[in] m_Color Color code, @see enum Color
     * @param[in] m_Attribute Output attribute, @see enum Attribute
     */
    CColorStream(Color m_Color, Attribute m_Attribute) : m_Color(m_Color), m_Attribute(m_Attribute) {}

    /**
     * Stream output modified.
     *
     * @param[in] os Stream reference
     * @param[in] colorStream An instance of CColorStream class
     * @return Reference to the modified stream
     */
    friend ostream &operator<<(ostream &os, const CColorStream &colorStream) {

        return os << "\033[" << colorStream.m_Attribute << ";" << colorStream.m_Color << "m";
    }

private:

    /** Color code */
    Color m_Color;

    /** Output attribute */
    Attribute m_Attribute;
};

#endif //VENECJIR_CCOLORSTREAM_H
