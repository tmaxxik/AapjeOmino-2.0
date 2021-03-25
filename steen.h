// Definitie van klasse Steen

#ifndef SteenHVar  // voorkom dat dit bestand meerdere keren
#define SteenHVar  // ge-include wordt

#include <vector>
using namespace std;

class Steen
{ 
  public:
    //Default constructor 
    Steen ();
    //Non-default constructor met 5 parameters
    Steen (int n, int o, int z, int w, int num);
    //Getters
    int getSteenNummer ();
    int getNoord ();
    int getOost ();
    int getZuid ();
    int getWest ();
    int getRotatie ();
    //Roteer functie
    void roteer (int hoek);
    //Print een steen
    void print ();

  private:
    int noord, oost, zuid, west;
    int steenNummer;
};

#endif

