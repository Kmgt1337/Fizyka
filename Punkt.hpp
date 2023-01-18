#ifndef PUNKT_HPP
#define PUNKT_HPP

#include <cmath>

class Punkt
{
public:
    Punkt(double x = 0, double y = 0, double z = 0)
        : _x(x), _y(y), _z(z)
    {}

    double _x;
    double _y;
    double _z;
};

class Ladunek : public Punkt
{
public:
    Ladunek(double x = 0, double y = 0, double z = 0, double q = 0)
        : Punkt(x, y, z), _q(q)
    {}

    double _q;
};

class Wektor : public Punkt
{
public:
    Wektor(double x = 0, double y = 0, double z = 0) 
        : Punkt(x, y, z), _dlugosc(std::sqrt(_x * _x + _y * _y + _z * _z))
    {}

    double _dlugosc;
};

#endif // PUNKT_HPP