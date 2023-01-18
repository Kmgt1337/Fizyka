#ifndef GNUPLOT_HPP
#define GNUPLOT_HPP

#include "Program.hpp"
#include "Plik.hpp"

class Gnuplot
{
public:
    static void ustaw_sciezke_programu(char*);
    static bool uruchom_skrypt_wektory();
    static bool uruchom_skrypt_punktu();

private:
    static std::string _skrypt;
    static std::string _sciezka_programu;
};

#endif