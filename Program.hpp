#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "Punkt.hpp"
#include "Matematyka.hpp"
#include "Stoper.hpp"

class Program
{
public:
    Program(char*);
    int uruchom();
    int rozwiaz_rownania_ruchu();

private:
    Ladunek _ladunek_docel{};

    Wektor _wektor_natezenia_pola{};
    double _potencjal{};

    std::vector<Ladunek> _ladunki{};

    std::vector<Wektor> _wektory{};
    std::vector<Wektor> _wektory_natezenia_pola{};

    std::vector<double> _potencjaly{};

    std::string _sciezka_pliku_z_punktami{};
    std::string _sciezka_pliku_z_punktem_poruszajacym_sie{};

    double _q{}, _m{};
    Wektor _wektor_natezenia_punktu{};
    Wektor _wektor_przyspieszenia{};
    Wektor _wektor_predkosci{};
    Ladunek _ladunek{};

    const size_t MAX_ITERACJI{10000};
    const double _deltat{0.1};

    Stoper stoper;
};

#endif