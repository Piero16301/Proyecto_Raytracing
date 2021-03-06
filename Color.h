#ifndef ADVANCED_RAYTRACER_COLOR_H
#define ADVANCED_RAYTRACER_COLOR_H

class Color {
public:
    double red;
    double green;
    double blue;
    double special; // Nivel de reflexion expecular [0-1]

public:
    Color();
    Color(double r, double g, double b, double s);

    double getColorRed() const;
    double getColorGreen() const;
    double getColorBlue() const;
    double getColorSpecial() const;

    void setColorRed(double redValue);
    void setColorGreen(double greenValue);
    void setColorBlue(double blueValue);
    void setColorSpecial(double specialValue);

    double brightness() const;

    Color colorScalar(double scalar) const;
    Color colorAdd(Color color) const;
    Color colorMultiply(Color color) const;
    Color colorAverage(Color color) const;

    Color clip();
};

#endif //ADVANCED_RAYTRACER_COLOR_H
