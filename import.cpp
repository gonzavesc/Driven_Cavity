#include <iostream>
#include <fstream>
#include <vector>
#include "import.hpp"
std::vector<double> readfiledat()
{
    std::ifstream file;
    std::vector<double> v;

    file.open("config.dat");    
    std::string name;
    while (file >> name) 
    {
        double a;

        file >> a;
        v.push_back(a);
    }
    return v;
}

