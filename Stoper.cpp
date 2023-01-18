#include "Stoper.hpp"

Stoper::Stoper()
{

}

void Stoper::rozpocznij_obliczanie()
{
    czas_startu = std::chrono::high_resolution_clock::now();
}

void Stoper::zakoncz_obliczanie()
{
    czas_konca = std::chrono::high_resolution_clock::now();
}

long long Stoper::czas_w_milisekundach()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(czas_konca - czas_startu).count();
}

long long Stoper::czas_w_sekundach()
{
    return std::chrono::duration_cast<std::chrono::seconds>(czas_konca - czas_startu).count();
}