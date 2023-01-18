#include "Wizualizacja.hpp"
#include "Plik.hpp"

std::string Gnuplot::_skrypt;
std::string Gnuplot::_sciezka_programu;

void Gnuplot::ustaw_sciezke_programu(char* sciezka)
{
    std::string pom = sciezka;
    size_t indeks = pom.find("fizyka.exe");
    _sciezka_programu = pom.substr(0, indeks);
}

bool Gnuplot::uruchom_skrypt_wektory()
{
    std::string tytul = "\"Wektory natezenia pola elektrycznego w kazdym ladunku w przestrzeni\"";

    _skrypt.clear();
    _skrypt += "cd '" + _sciezka_programu + "'\n";
    _skrypt += "set title " + tytul + "\n";
    _skrypt += "splot \"" + Plik::_sciezka_wynikow_gnuplot 
    + "\"" + " using 1:2:3 title 'Ladunki' pt 7 ps 1, " + "\"" + Plik::_sciezka_wynikow_gnuplot_wektor 
    + "\"" + " using 1:2:3:($4/sqrt($4*$4+$5*$5+$6*$6)):($5/sqrt($4*$4+$5*$5+$6*$6)):($6/sqrt($4*$4+$5*$5+$6*$6)) title 'Wektory natezenia pola elektrycznego' with vectors filled head lw 1\n";
    _skrypt += "pause -1";

    std::ofstream strumien("Wyniki\\Gnuplot\\skrypt_wektory.txt");
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_zapisem("Problem z zapisem do pliku - " + _sciezka_programu);
    }

    strumien << _skrypt;

    strumien.close();

    system("gnuplot Wyniki\\Gnuplot\\skrypt_wektory.txt");
    return true;
}

bool Gnuplot::uruchom_skrypt_punktu()
{
    std::string tytul = "\"Tor ruchu czastki w polu elektrycznym\"";

    _skrypt.clear();
    _skrypt += "cd '" + _sciezka_programu + "'\n";
    _skrypt += "set title " + tytul + "\n";
    _skrypt += "splot \"" + Plik::_sciezka_wynikow_gnuplot + 
    "\"" + " using 1:2:3 title 'Ladunki' pt 7 ps 1, " + "\"" + Plik::_sciezka_punktu_wyniki_gnuplot 
    + "\"" + " using 1:2:3 title 'Tor ruchu' pt 7 ps 1\n";
    _skrypt += "pause -1";

    std::ofstream strumien("Wyniki\\Gnuplot\\skrypt_punkt.txt");
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_zapisem("Problem z zapisem do pliku - " + _sciezka_programu);
    }

    strumien << _skrypt;

    strumien.close();

    system("gnuplot Wyniki\\Gnuplot\\skrypt_punkt.txt");
    return true;
}