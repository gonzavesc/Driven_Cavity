#include <iostream>
#include <fstream>
#include <vector>
#include "import.hpp"
#include "positions.hpp"

positions::positions(const double& a, const double& b)
{   
    double j;
    dx = a;
    dy = b;

    n = 1 / dx;
    m = 1/ dy;
    Xu.push_back(0);
    Yv.push_back(0);
    for (j = 0; j < n; j++)
    {
        Xp.push_back(j * dx);
        Xu.push_back((j + 0.5) * dx);
        
    }
    Xp.push_back(n * dx); Xu.push_back(n * dx);
    for (j = 0; j < m; j++)
    {
        Yp.push_back(j * dy);
        Yv.push_back((j + 0.5) * dy);
    }
    Yp.push_back(m * dy); Yv.push_back(m * dy);


    for (j = 0; j < n; j++)
    {

        Dxpr.push_back((Xp[j+1] - Xp[j])/2);
    }
    Dxpr.push_back(0);
    Dxpl.push_back(0);
    for (j = 1; j <= n; j++)
    {
        Dxpl.push_back((Xp[j] - Xp[j-1]) / 2);
    }
    
    for (j = 0; j < m; j++)
    {
        Dypu.push_back((Yp[j+1] - Yp[j])/2);
    }
    Dypu.push_back(0);
    
    Dypd.push_back(0);
    for (j = 1; j <= m; j++)
    {
        Dypd.push_back((Yp[j] - Yp[j-1])/2);
    }
    
    Dxur.push_back(0);
    for (j = 1; j < n; j++ )
    {
        Dxur.push_back((Xu[j+1] - Xu[j]) / 2);
    }
    Dxur.push_back(Xu[n+1] - Xu[n]); Dxur.push_back(0);
    
    Dxul.push_back(0); Dxul.push_back(Xu[1]);
    for (j = 2; j <= n; j++)
    {
        Dxul.push_back((Xu[j] - Xu[j - 1]) / 2);
    }
    Dxul.push_back(0);
    
    Dyvu.push_back(0);
    for (j = 1; j < m; j++)
    {
        Dyvu.push_back((Yv[j+1] - Yv[j]) / 2);
    }
    Dyvu.push_back(Yv[m+1] - Yv[m]); Dyvu.push_back(0);

    Dyvd.push_back(0); Dyvd.push_back(Yv[1]);
    for (j = 2; j <= m; j++)
    {
        Dyvd.push_back((Yv[j] - Yv[j-1]) / 2);
    }
    Dyvd.push_back(0);
}
std::vector <double> positions::get_Xu()
{
    return Xu;
}

std::vector <double> positions::get_Yv()
{
    return Yv;
}
std::vector <double> positions::get_Yp()
{
    return Yp;
}
std::vector <double> positions::get_Xp()
{
    return Xp;
}
int positions::get_m()
{
    return m;
}
int positions::get_n()
{
    return n;
}