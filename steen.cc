#include "standaard.h"
#include "steen.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Steen::Steen ()
{
    noord = -1;
    oost = -1;
    zuid = -1;
    west = -1;
    steenNummer = -1;
}  // dedault constructor 

//*************************************************************************

Steen::Steen (int n, int o, int z, int w, int num)
{
    noord = n;
    oost = o;
    zuid = z;
    west = w;
    steenNummer = num;
}  // non-default constructor 

//*************************************************************************

int Steen::getSteenNummer ()
{
    return steenNummer;
}  // getSteenNummer

int Steen::getNoord ()
{
    return noord;
}  // getNoord

//*************************************************************************

int Steen::getOost ()
{
    return oost;
}  // getOost

//*************************************************************************

int Steen::getZuid ()
{
    return zuid;
}  // getZuid

//*************************************************************************

int Steen::getWest ()
{
    return west;
}  // getWest


void Steen::print () 
{
    cout << steenNummer << ": " << noord << ", " << oost << ", " 
         << zuid << ", " << west << endl;  
}  // print

//*************************************************************************

void Steen::roteer (int hoek) 
{
    while (hoek > 0)
    {
        int temp = noord;
        noord = oost;
        oost = zuid;
        zuid = west;
        west = temp;
        hoek--;
    }
}  // roteer