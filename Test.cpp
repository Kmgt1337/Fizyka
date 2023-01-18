#include "Test.hpp"
#include "Plik.hpp"

bool stworz_plik_z_losowymi_danymi()
{
    std::ofstream strumien("dane\\dane.dat");
    if(!strumien)
    {
        strumien.close();
        throw Problem_z_zapisem("Problem z zapisem w pliku dane.dat");
    }

    std::random_device d;
    std::mt19937 e(d());
    std::gamma_distribution<> losuj_punkty_gamma(1, 5);
    std::uniform_real_distribution<double> losuj_punkty_real(-10, 10);
    std::normal_distribution<double> losuj_punkty_normal(-10, 10);
    //std::extreme_value_distribution<double> losuj_punkty(1, 25);
    std::uniform_real_distribution<double> losuj_ladunki(-0.00005, 0.00001);

    for(int i = 0; i < 100; i++)
    {   
        strumien << losuj_punkty_real(e) << " " << losuj_punkty_real(e) << " " << losuj_punkty_real(e) << " " << losuj_ladunki(e) << "\n";
    }

    strumien.close();
    return true;
}