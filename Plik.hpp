#ifndef ZAPIS_DO_PLIKU_HPP
#define ZAPIS_DO_PLIKU_HPP

#include "Program.hpp"
#include "Punkt.hpp"
#include <stdexcept>

class Pomocnicza_zapis_ladunku
{
public:
    Pomocnicza_zapis_ladunku(double deltat, Punkt ladunek, Wektor v, Wektor a)
        : _delta_t{deltat}, _ladunek{ladunek}, _wektor_predkosci{v}, _wektor_przyspieszenia{a}
    {}

    double _delta_t;
    Punkt _ladunek;
    Wektor _wektor_predkosci;
    Wektor _wektor_przyspieszenia;
};

class Pomocnicza_zapis_toru
{
public:
    Pomocnicza_zapis_toru(Punkt ladunek) : _ladunek{ladunek}
    {}

    Punkt _ladunek;
};

class Plik
{
public:
    static bool odczytaj_z_pliku_dane(std::vector<Ladunek>& ladunki);
    static bool odczytaj_z_pliku_punkt_poruszajacy_sie(Ladunek& ladunek, Wektor& wektor_predkosci, double& q, double& m);

    static bool zapis_do_pliku(const std::vector<Ladunek>& ladunki, const Wektor& wektor, const Ladunek& ladunek_docel, double potencjal);
    static bool zapis_do_pliku_gnuplot(const std::vector<Ladunek>& ladunki);
    static bool zapis_do_pliku_gnuplot_wektor(const std::vector<Wektor>& wektory, const std::vector<Ladunek>& ladunki);

    static bool zapis_do_pliku_glowny(const std::vector<Ladunek>& ladunki, const std::vector<Wektor>& wektory, const std::vector<double>& potencjaly);

    static bool zapis_do_pliku_tor_ruchu(const std::vector<Pomocnicza_zapis_ladunku>& pom);
    static bool zapis_do_pliku_tor_ruchu_gnuplot(const std::vector<Pomocnicza_zapis_toru>& pom);

    static bool ustaw_sciezke(std::string sciezka_danych, std::string sciezka_punktu);

    static std::string _sciezka_punktu;
    static std::string _sciezka_punktu_wyniki;
    static std::string _sciezka_punktu_wyniki_gnuplot;
    
    static std::string _sciezka_wyniki_wiele;
    static std::string _sciezka_danych;
    static std::string _sciezka_wynikow;
    static std::string _sciezka_wynikow_gnuplot;
    static std::string _sciezka_wynikow_gnuplot_wektor;
};

class Problem_z_odczytem : public std::exception
{
public:
    Problem_z_odczytem(std::string wiad) : _wiadomosc(wiad)
    {}

    const char* what() const noexcept override
    {
        return _wiadomosc.c_str();
    }

private:
    std::string _wiadomosc;
};

class Problem_z_zapisem : public std::exception
{
public:
    Problem_z_zapisem(std::string wiad) : _wiadomosc(wiad)
    {}

    const char* what() const noexcept override
    {
        return _wiadomosc.c_str();
    }

private:
    std::string _wiadomosc;
};

#endif