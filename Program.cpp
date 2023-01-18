#include "Program.hpp"
#include "Test.hpp"
#include "Wizualizacja.hpp"
#include "Plik.hpp"

Program::Program(char* argv)
{
    Gnuplot::ustaw_sciezke_programu(argv);
}

int Program::uruchom()
{
    try
    {
        stworz_plik_z_losowymi_danymi();
    }
    catch(const Problem_z_zapisem& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    
    std::cout << "Podaj nazwe pliku z punktami: ";
    std::getline(std::cin, _sciezka_pliku_z_punktami);
    std::cout << "Podaj nazwe pliku z ladunkiem poruszajacym sie: ";
    std::getline(std::cin, _sciezka_pliku_z_punktem_poruszajacym_sie);
    Plik::ustaw_sciezke(_sciezka_pliku_z_punktami, _sciezka_pliku_z_punktem_poruszajacym_sie);

    try
    {
        Plik::odczytaj_z_pliku_dane(_ladunki);
        Plik::odczytaj_z_pliku_punkt_poruszajacy_sie(_ladunek, _wektor_predkosci, _q, _m);
    }
    catch(const Problem_z_odczytem& e)
    {
        std::cerr << e.what() << '\n';
        std::cin.get();
        return 1;
    }
    catch(const Problem_z_zapisem& e)
    {
        std::cerr << e.what() << '\n';
        std::cin.get();
        return 1;
    }

    // std::cout << "Podaj punkt [x, y, z] wzgledem ktorego obliczamy: ";
    // std::cin >> _ladunek_docel._x >> _ladunek_docel._y >> _ladunek_docel._z;

    std::cout << "Obliczam...\n";
    stoper.rozpocznij_obliczanie();

    for(std::size_t i = 0; i < _ladunki.size(); i++)
    {
        _ladunek_docel = _ladunki.at(i);
        //_wektory = Matematyka::oblicz_wektory(_ladunki, _ladunek_docel);
        _wektor_natezenia_pola = Matematyka::oblicz_wektor_natezenia_pola(_ladunki, _ladunek_docel);
        _potencjal = Matematyka::oblicz_potencjal_pola(_ladunki, _ladunek_docel);

        _wektory_natezenia_pola.push_back(Matematyka::oblicz_wektor_natezenia_pola(_ladunki, _ladunek_docel));
        _potencjaly.push_back(Matematyka::oblicz_potencjal_pola(_ladunki, _ladunek_docel));
    }

    try
    {
        Plik::zapis_do_pliku_glowny(_ladunki, _wektory_natezenia_pola, _potencjaly);
        Plik::zapis_do_pliku(_ladunki, _wektor_natezenia_pola, _ladunek_docel, _potencjal);
        Plik::zapis_do_pliku_gnuplot(_ladunki);
        Plik::zapis_do_pliku_gnuplot_wektor(_wektory_natezenia_pola, _ladunki);
    }
    catch(const Problem_z_zapisem& e)
    {
        std::cerr << e.what() << std::endl;
        std::cin.get();
        return 1;
    }

    rozwiaz_rownania_ruchu();
    stoper.zakoncz_obliczanie();

    std::cout << "Czas wykonania obliczen wyniosl " << stoper.czas_w_milisekundach() << " milisekund" << std::endl;
    std::cout << "Czy chcesz wizualizacje? (t/n): ";
    char wybor;
    std::cin >> wybor;

    if(wybor == 't' || wybor == 'T')
    {
        Gnuplot::uruchom_skrypt_wektory();
        Gnuplot::uruchom_skrypt_punktu();
    }

    return 0;
}

int Program::rozwiaz_rownania_ruchu()
{
    double czas = 0.0;

   // _wektory = Matematyka::oblicz_wektory(_ladunki, _ladunek);
    _wektor_natezenia_punktu = Matematyka::oblicz_wektor_natezenia_pola(_ladunki, _ladunek);
    _wektor_przyspieszenia = Matematyka::oblicz_wektor_przyspieszenia(_wektor_natezenia_punktu, _q, _m);

    
    std::vector<Pomocnicza_zapis_ladunku> pom_ladunek;
    std::vector<Pomocnicza_zapis_toru> pom_tor;

    pom_ladunek.push_back(Pomocnicza_zapis_ladunku(czas, _ladunek, _wektor_predkosci, _wektor_przyspieszenia));
    pom_tor.push_back(Pomocnicza_zapis_toru(_ladunek));

    // try
    // {
    //     Plik::zapis_do_pliku_tor_ruchu(pom_ladunek);
    //     Plik::zapis_do_pliku_tor_ruchu_gnuplot(pom_tor);
    // }
    // catch(const Problem_z_zapisem& e)
    // {
    //     std::cerr << e.what() << '\n';
    //     return 1;
    // }

    Punkt min = Matematyka::oblicz_wspolrzedne_minimalne(_ladunki);
    Punkt max = Matematyka::oblicz_wspolrzedne_maksymalne(_ladunki);
    
    for(std::size_t i = 0; i < MAX_ITERACJI; i++)
    {
        czas += _deltat;

        _ladunek._x = _ladunek._x + _wektor_predkosci._x * _deltat + 0.5 * _wektor_przyspieszenia._x * std::pow(_deltat, 2);
        _ladunek._y = _ladunek._y + _wektor_predkosci._y * _deltat + 0.5 * _wektor_przyspieszenia._y * std::pow(_deltat, 2);
        _ladunek._z = _ladunek._z + _wektor_predkosci._z * _deltat + 0.5 * _wektor_przyspieszenia._z * std::pow(_deltat, 2);

        if(!Matematyka::ladunek_w_granicach(min, max, _ladunek))
        {
            break;
        }

        _wektor_predkosci._x = _wektor_predkosci._x + _wektor_przyspieszenia._x * _deltat;
        _wektor_predkosci._y = _wektor_predkosci._y + _wektor_przyspieszenia._y * _deltat;
        _wektor_predkosci._z = _wektor_predkosci._z + _wektor_przyspieszenia._z * _deltat;

        //_wektory = Matematyka::oblicz_wektory(_ladunki, _ladunek);
        _wektor_natezenia_punktu = Matematyka::oblicz_wektor_natezenia_pola(_ladunki, _ladunek);
        _wektor_przyspieszenia = Matematyka::oblicz_wektor_przyspieszenia(_wektor_natezenia_punktu, _q, _m);
        
        pom_ladunek.push_back(Pomocnicza_zapis_ladunku(czas, _ladunek, _wektor_predkosci, _wektor_przyspieszenia));
        pom_tor.push_back(Pomocnicza_zapis_toru(_ladunek));
    }

    try
    {
        Plik::zapis_do_pliku_tor_ruchu(pom_ladunek);
        Plik::zapis_do_pliku_tor_ruchu_gnuplot(pom_tor);
    }
    catch(const Problem_z_zapisem& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}