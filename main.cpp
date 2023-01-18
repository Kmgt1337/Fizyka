#include "Program.hpp"
#include "Plik.hpp"

int main(int argc, char** argv)
{
    if(argc > 0)
    {
        try
        {
            Program p(argv[0]);
            return p.uruchom(); 
        }
        catch(const Problem_z_odczytem& e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch(const Problem_z_zapisem& e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch(...)
        {
            std::cerr << "Nieznany blad" << std::endl;
        }
    }
    return 1;
}