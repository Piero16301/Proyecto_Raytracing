#include "Color.h"

Color::Color() {
    red = 0.5;
    green = 0.5;
    blue = 0.5;
    special = 0;
    refraction = 0;
}

Color::Color(double r, double g, double b, double s, double rf) {
    red = r;
    green = g;
    blue = b;
    special = s;
    refraction = rf;
}

double Color::getColorRed() const {
    return red;
}

double Color::getColorGreen() const {
    return green;
}

double Color::getColorBlue() const {
    return blue;
}

double Color::getColorSpecial() const {
    return special;
}

double Color::getColorRefraction() const {
    return refraction;
}

void Color::setColorRed(double redValue) {
    red = redValue;
}

void Color::setColorGreen(double greenValue) {
    green = greenValue;
}

void Color::setColorBlue(double blueValue) {
    blue = blueValue;
}

void Color::setColorSpecial(double specialValue) {
    special = specialValue;
}

double Color::brightness() const {
    return (red + green + blue) / 3;
}

Color Color::colorScalar(double scalar) const {
    return Color(red*scalar, green*scalar, blue*scalar, special, refraction);
}

Color Color::colorAdd(Color color) const {
    return Color(red + color.getColorRed(), green + color.getColorGreen(), blue + color.getColorBlue(), special, refraction);
}

Color Color::colorMultiply(Color color) const {
    return Color(red * color.getColorRed(), green * color.getColorGreen(), blue * color.getColorBlue(), special, refraction);
}

Color Color::colorAverage(Color color) const {
    return Color((red + color.getColorRed())/2, (green + color.getColorGreen())/2, (blue + color.getColorBlue())/2, special, refraction);
}

Color Color::clip() {
    double allLight = red + green + blue;
    double excessLight = allLight - 3;
    if (excessLight > 0) {
        red = red + excessLight * (red / allLight);
        green = green + excessLight * (green / allLight);
        blue = blue + excessLight * (blue / allLight);
    }
    if (red > 1) {red = 1;}
    if (green > 1) {green = 1;}
    if (blue > 1) {blue = 1;}

    if (red < 0) {red = 0;}
    if (green < 0) {green = 0;}
    if (blue < 0) {blue = 0;}

    return Color(red, green, blue, special, refraction);
}
