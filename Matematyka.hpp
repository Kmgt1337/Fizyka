#ifndef MATEMATYKA_HPP
#define MATEMATYKA_HPP

#include <vector>
#include "Punkt.hpp"

class Matematyka
{
public:
    static Wektor oblicz_wektor_natezenia_pola(const std::vector<Ladunek>& ladunki, const Ladunek& docel);
    static double oblicz_potencjal_pola(const std::vector<Ladunek>& ladunki, const Ladunek& docel);
    static Wektor oblicz_wektor_przyspieszenia(const Wektor& wektor_natezenia, const double& q, const double& m);

    static Punkt oblicz_wspolrzedne_maksymalne(const std::vector<Ladunek>& ladunki);
    static Punkt oblicz_wspolrzedne_minimalne(const std::vector<Ladunek>& ladunki);
    static bool ladunek_w_granicach(const Punkt& min, const Punkt& max, const Ladunek& ladunek);

private:
    constexpr static double jeden_przez_4pi_razy_przenikalnosc{8987551790};
};


#endif