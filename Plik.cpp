#include "Plik.hpp"

std::string Plik::_sciezka_danych;
std::string Plik::_sciezka_wynikow;
std::string Plik::_sciezka_wynikow_gnuplot;
std::string Plik::_sciezka_wynikow_gnuplot_wektor;
std::string Plik::_sciezka_wyniki_wiele;
std::string Plik::_sciezka_punktu;
std::string Plik::_sciezka_punktu_wyniki;
std::string Plik::_sciezka_punktu_wyniki_gnuplot;

bool Plik::ustaw_sciezke(std::string sciezka_danych, std::string sciezka_punktu)
{
    _sciezka_danych = sciezka_danych;
    _sciezka_punktu = sciezka_punktu;
    
    try
    {
        size_t indeks_kropka = sciezka_danych.find_first_of('.');
        size_t indeks_ukosnik = sciezka_danych.find_first_of('/');
        if(indeks_ukosnik == std::string::npos)
        {
            indeks_ukosnik = sciezka_danych.find_first_of('\\');
        }
        _sciezka_wynikow = "Wyniki\\" + sciezka_danych.substr(indeks_ukosnik, indeks_kropka - indeks_ukosnik);
        _sciezka_wynikow += "_wyniki.dat";

        _sciezka_wynikow_gnuplot = "Wyniki/Gnuplot" + sciezka_danych.substr(indeks_ukosnik, indeks_kropka - indeks_ukosnik);
        _sciezka_wynikow_gnuplot += "_wyniki_gnuplot.dat";

        _sciezka_wynikow_gnuplot_wektor = "Wyniki/Gnuplot" + sciezka_danych.substr(indeks_ukosnik, indeks_kropka - indeks_ukosnik);
        _sciezka_wynikow_gnuplot_wektor += "_wyniki_gnuplot_wektor.dat";

        indeks_kropka = sciezka_punktu.find_first_of('.');
        indeks_ukosnik = sciezka_danych.find_first_of('/');
        if(indeks_ukosnik == std::string::npos)
        {
            indeks_ukosnik = sciezka_danych.find_first_of('\\');
        }
        _sciezka_punktu_wyniki_gnuplot = "Wyniki/Gnuplot" + sciezka_punktu.substr(indeks_ukosnik, indeks_kropka - indeks_ukosnik);
        _sciezka_punktu_wyniki_gnuplot += "_wyniki_gnuplot.dat";

        _sciezka_punktu_wyniki = "Wyniki\\" + sciezka_punktu.substr(indeks_ukosnik, indeks_kropka - indeks_ukosnik);
        _sciezka_punktu_wyniki += "_wyniki.dat";

        _sciezka_wyniki_wiele = "Wyniki\\" + sciezka_punktu.substr(indeks_ukosnik, indeks_kropka - indeks_ukosnik) + "_glowny.dat";
    }
    catch(...)
    {
        throw Problem_z_odczytem("Nastapil problem z plikiem\n");
    }
    
    std::ofstream s1(_sciezka_punktu_wyniki, std::ios::out | std::ios::trunc);
    std::ofstream s2(_sciezka_punktu_wyniki_gnuplot, std::ios::out | std::ios::trunc);
    std::ofstream s3(_sciezka_wyniki_wiele, std::ios::out | std::ios::trunc);

    if(!s1 || !s2 || !s2)
    {
        s1.close(); s2.close(); s3.close();
        throw Problem_z_zapisem("Problem z plikiem");
    }

    s1.close(); s2.close(); s3.close();
}

bool Plik::odczytaj_z_pliku_dane(std::vector<Ladunek>& ladunki)
{
    std::ifstream strumien(_sciezka_danych.c_str());
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_odczytem("Problem z odczytem pliku: " + _sciezka_danych);
    }

    double x{};
    double y{};
    double z{};
    double q{};

    while(strumien >> x >> y >> z >> q)
    {
        ladunki.push_back(Ladunek{x, y, z, q});
    }

    strumien.close();
    return true;
}

bool Plik::odczytaj_z_pliku_punkt_poruszajacy_sie(Ladunek& ladunek, Wektor& wektor_predkosci, double& q, double& m)
{
    std::ifstream strumien(_sciezka_punktu.c_str());
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_odczytem("Problem z odczytem pliku: " + _sciezka_punktu);
    }

    double x0{}, y0{}, z0{}, vx0{}, vy0{}, vz0{};
    strumien >> x0 >> y0 >> z0 >> vx0 >> vy0 >> vz0 >> q >> m;

    ladunek._x = x0;
    ladunek._y = y0;
    ladunek._z = z0;

    wektor_predkosci._x = vx0;
    wektor_predkosci._y = vy0;
    wektor_predkosci._z = vz0;

    strumien.close();
    return true;
}

bool Plik::zapis_do_pliku(const std::vector<Ladunek>& ladunki, const Wektor& wektor, const Ladunek& ladunek_docel, double potencjal)
{
    std::ofstream strumien(_sciezka_wynikow.c_str());
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_zapisem("Problem z zapisem pliku: " + _sciezka_wynikow);
    }

    strumien << std::fixed << std::setprecision(8) << ladunek_docel._x << " " << ladunek_docel._y << " " << ladunek_docel._z 
    << " " << wektor._x << " " << wektor._y 
    << " " << wektor._z << " " << potencjal << "\n";

    strumien.close();
    return true;
}

bool Plik::zapis_do_pliku_gnuplot(const std::vector<Ladunek>& ladunki)
{
    std::ofstream strumien(_sciezka_wynikow_gnuplot.c_str());
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_zapisem("Problem z zapisem do pliku: " + _sciezka_wynikow_gnuplot);
    }

    for(const auto& e : ladunki)
    {
        strumien << std::fixed << std::setprecision(8) << e._x << " " << e._y << " " << e._z << "\n";
    }

    strumien.close();
    return true;
}

bool Plik::zapis_do_pliku_gnuplot_wektor(const std::vector<Wektor>& wektory, const std::vector<Ladunek>& ladunki)
{
    std::ofstream strumien(_sciezka_wynikow_gnuplot_wektor.c_str());
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_zapisem("Problem z zapisem do pliku: " + _sciezka_wynikow_gnuplot_wektor);
    }

    for(std::size_t i = 0; i < ladunki.size(); i++)
    {
        strumien << std::fixed << std::setprecision(8) << ladunki.at(i)._x << " " << ladunki.at(i)._y << " " << ladunki.at(i)._z 
        << " " << wektory.at(i)._x << " " << wektory.at(i)._y  << " " << wektory.at(i)._z << "\n";
    }

    strumien.close();
    return true;
}

bool Plik::zapis_do_pliku_glowny(const std::vector<Ladunek>& ladunki, const std::vector<Wektor>& wektory, const std::vector<double>& potencjaly)
{
    std::ofstream strumien(_sciezka_wyniki_wiele);
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_zapisem("Problem z zapisem do pliku: " + _sciezka_wyniki_wiele);
    }

    for(std::size_t i = 0; i < ladunki.size(); i++)
    {
        strumien << ladunki.at(i)._x << " " << ladunki.at(i)._y << " " << ladunki.at(i)._z << " " << ladunki.at(i)._q << " "
        << wektory.at(i)._x << " " << wektory.at(i)._y << " " << wektory.at(i)._z << " " << wektory.at(i)._dlugosc << " " 
        << potencjaly.at(i) << std::endl;
    }

    strumien.close();
    return true;
}

bool Plik::zapis_do_pliku_tor_ruchu(const std::vector<Pomocnicza_zapis_ladunku>& pom)
{
    std::ofstream strumien(_sciezka_punktu_wyniki, std::ios::app);
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_zapisem("Problem z zapisem do pliku: " + _sciezka_punktu);
    }

    for(const auto& e : pom)
    {
        strumien << e._delta_t << " " << e._ladunek._x << " " << e._ladunek._y << " " << e._ladunek._z << " "
        << e._wektor_predkosci._x << " " << e._wektor_predkosci._y << " " << e._wektor_predkosci._z << " " 
        << e._wektor_przyspieszenia._x << " " << e._wektor_przyspieszenia._y << " " << e._wektor_przyspieszenia._z << std::endl; 
    }
    strumien.close();
    return true;
}

bool Plik::zapis_do_pliku_tor_ruchu_gnuplot(const std::vector<Pomocnicza_zapis_toru>& pom)
{
    std::ofstream strumien(_sciezka_punktu_wyniki_gnuplot, std::ios::app);
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_zapisem("Problem z zapisem do pliku: " + _sciezka_punktu_wyniki_gnuplot);
    }

    for(const auto& e : pom)
    {
        strumien << e._ladunek._x << " " << e._ladunek._y << " " << e._ladunek._z << std::endl;
    }
    strumien.close();
    return true;
}
