#ifndef STOPER_HPP
#define STOPER_HPP

#include <chrono>

class Stoper
{
public:
    Stoper();
    void rozpocznij_obliczanie();
    void zakoncz_obliczanie();

    long long czas_w_milisekundach(); 
    long long czas_w_sekundach();

private:
    std::chrono::high_resolution_clock::time_point czas_startu;
    std::chrono::high_resolution_clock::time_point czas_konca;
};


#endif