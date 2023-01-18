#include "Matematyka.hpp"
#include <iostream>
#include <algorithm>

Wektor Matematyka::oblicz_wektor_natezenia_pola(const std::vector<Ladunek>& ladunki, const Ladunek& docel)
{
    double x{}, y{}, z{};
    std::vector<Wektor> wektory;

    for(std::size_t i = 0; i < ladunki.size(); i++)
    {
        wektory.push_back(Wektor{docel._x - ladunki.at(i)._x, docel._y - ladunki.at(i)._y, docel._z - ladunki.at(i)._z});

        if(wektory.at(i)._dlugosc != 0)
        {
            double czynnik = ladunki.at(i)._q / std::pow(wektory.at(i)._dlugosc, 3);
            x += wektory.at(i)._x * czynnik;
            y += wektory.at(i)._y * czynnik;
            z += wektory.at(i)._z * czynnik;
        }
    }

    x *= jeden_przez_4pi_razy_przenikalnosc;
    y *= jeden_przez_4pi_razy_przenikalnosc;
    z *= jeden_przez_4pi_razy_przenikalnosc;

    return Wektor{x, y, z};
}

double Matematyka::oblicz_potencjal_pola(const std::vector<Ladunek>& ladunki, const Ladunek& docel)
{
    double potencjal{};
    std::vector<Wektor> wektory;

    for(std::size_t i = 0; i < ladunki.size(); i++)
    {
        wektory.push_back(Wektor{docel._x - ladunki.at(i)._x, docel._y - ladunki.at(i)._y, docel._z - ladunki.at(i)._z});

        if(wektory.at(i)._dlugosc != 0)
        {
            potencjal += ladunki.at(i)._q / wektory.at(i)._dlugosc;
        }
    }

    return potencjal;
}

Wektor Matematyka::oblicz_wektor_przyspieszenia(const Wektor& wektor_natezenia, const double& q, const double& m)
{
    return Wektor((q * wektor_natezenia._x) / m, (q * wektor_natezenia._y) / m, (q * wektor_natezenia._z) / m);
}

Punkt Matematyka::oblicz_wspolrzedne_minimalne(const std::vector<Ladunek>& ladunki)
{
    auto min_x = std::min_element(ladunki.begin(), ladunki.end(),
    [](const Punkt& l1, const Punkt& l2)
    {
        return l1._x > l2._x ? false : true;
    });

    auto min_y = std::min_element(ladunki.begin(), ladunki.end(), 
    [](const Punkt& l1, const Punkt& l2)
    {
        return l1._y > l2._y ? false : true;
    });

    auto min_z = std::min_element(ladunki.begin(), ladunki.end(), 
    [](const Punkt& l1, const Punkt& l2)
    {
        return l1._z > l2._z ? false : true;
    });

    return Punkt((*min_x)._x, (*min_y)._y, (*min_z)._z);
}

Punkt Matematyka::oblicz_wspolrzedne_maksymalne(const std::vector<Ladunek>& ladunki)
{
    auto max_x = std::max_element(ladunki.begin(), ladunki.end(),
    [](const Punkt& l1, const Punkt& l2)
    {
        return l1._x > l2._x ? false : true;
    });

    auto max_y = std::max_element(ladunki.begin(), ladunki.end(), 
    [](const Punkt& l1, const Punkt& l2)
    {
        return l1._y > l2._y ? false : true;
    });

    auto max_z = std::max_element(ladunki.begin(), ladunki.end(), 
    [](const Punkt& l1, const Punkt& l2)
    {
        return l1._z > l2._z ? false : true;
    });

    return Punkt((*max_x)._x, (*max_y)._y, (*max_z)._z);
}

bool Matematyka::ladunek_w_granicach(const Punkt& min, const Punkt& max, const Ladunek& ladunek)
{
    if((ladunek._x < min._x || ladunek._y < min._y || ladunek._z < min._z) ||
       (ladunek._x > max._x || ladunek._y > max._y || ladunek._z > max._z))
    {
        return false;
    }
    return true;
}