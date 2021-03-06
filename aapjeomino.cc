// Implementatie van klasse AapjeOmino

#include <iostream>
#include <cstdlib>
#include <vector>
#include "limits.h"
#include "standaard.h"
#include "aapjeomino.h"

using namespace std;

//*************************************************************************

AapjeOmino::AapjeOmino ()
{
  aanBeurt = 1;
  steenGepakt = false;
  maxScore = INT_MIN;
  for (int i = 0; i < MaxDimensie; i++)
  {
    for (int j = 0; j < MaxDimensie; j++)
    {
      bord[i][j].first = -1;
      bord[i][j].second = 0;
    }
  }
}  // default constructor

//*************************************************************************

bool AapjeOmino::checkHoogte (int num)
{
  const char * bericht = "Hoogte";
  if (!integerInBereik (bericht, num, 1, MaxDimensie))
    return false;
  return true; 
}  // checkHoogte

//*************************************************************************

bool AapjeOmino::checkBreedte (int num)
{
  const char * bericht = "Breedte";
  if (!integerInBereik (bericht, num, 1, MaxDimensie))
    return false;
  breedte = num;
  return true;
}  // checkBreedte

//*************************************************************************

bool AapjeOmino::checkNrStenen (int num)
{
  if (num < 3)
  {
    cout << "Het aantal stenen klopt niet!" << endl;
    return false;
  }
  nrStenen = num;
  return true;
}  // checkNrStenen

//*************************************************************************

bool AapjeOmino::checkBeginAantalStenen (int num)
{
  if (num < 1 || ((nrStenen - 1) < 2 * num))
  {
    cout << "Het beginaantal stenen klopt niet!" << endl;
    return false;
  }
  return true;
}  // checkBeginAantalStenen

//*************************************************************************

bool AapjeOmino::checkPositieNULLSteen (int pos_i, int pos_j)
{
  if (pos_i >= hoogte || pos_j >= breedte || pos_i < 0 || pos_j < 0)
  {
    cout << "De positie van de 0-steen klopt niet!" << endl;
    return false;
  }
  return true;
}  // checkPositieNULLSteen

//*************************************************************************

bool AapjeOmino::checkWaardes (int i, int n, int o, int z, int w)
{
  if (n < 1 || n > 9 || o < 1 || o > 9  || z < 1 || z > 9 || w < 1 || w > 9)
  {
    cout << i << "-de stenen klopt niet!" << endl;
    return false;
  }
  return true;
}  // checkWaardes

//*************************************************************************

void AapjeOmino::verdeelStenen (int pos_i, int pos_j, int beginAantalStenen)
{
  stenenOpHetBord.push_back(pot.front());
  bord[pos_i][pos_j].first = 0;
  bord[pos_i][pos_j].second = 0;
  pot.erase(pot.begin());
  for (int i = 0; i < 2 * beginAantalStenen; i++)
  {
    if (i % 2 == 0)
    {
      Femke.push_back(pot.front());
      pot.erase(pot.begin());
    }
    else
    {
      Lieke.push_back(pot.front());
      pot.erase(pot.begin());
    }
  }
}

//*************************************************************************

bool AapjeOmino::leesIn (const char * invoernaam)
{
  ifstream input;
  int number;
  //Positie van de 0-steen
  int pos_i, pos_j;
  int beginAantalStenen;
  int n, o, z, w;

  //File openen
  input.open(invoernaam);
  if (input.fail())
  {
    cout << "Deze file kan niet geopend worden!" << endl;
    return false;
  }
  //Hoogte checken 
  input >> number;
  if (!checkHoogte(number))
    return false;
  hoogte = number; 
  //Breedte checken
  input >> number;
  if (!checkBreedte(number))
    return false;
  breedte = number;
  //Aantal stenen checken (nrStenen >= 3!)
  input >> number;
  if (!checkNrStenen(number))
    return false;
  nrStenen = number;
  //Beginaantal stenen van spelers checken
  input >> number;
  if (!checkBeginAantalStenen(number))
    return false;
  beginAantalStenen = number;
  //De positie van de 0-steen checken
  input >> pos_i >> pos_j;
  if (!checkPositieNULLSteen(pos_i, pos_j))
    return false;
  //De waardes van de stenen checken
  for (int i = 0; i < nrStenen; i++)
  {
    input >> n >> o >> z >> w;
    if (!checkWaardes(i, n, o, z, w))
      return false;
    Steen newSteen(n, o, z, w, i);
    pot.push_back(newSteen);
  }

  //Stenen verdelen
  verdeelStenen(pos_i, pos_j, beginAantalStenen);
  
  input.close();
  return true;
}  // leesIn

//*************************************************************************

bool AapjeOmino::eindstand ()
{
  if (Femke.empty() || Lieke.empty() || 
     (bepaalMogelijkeZetten().empty() && pot.empty()))
    return true;
  return false;
}  // eindstand

//*************************************************************************

void AapjeOmino::printStenen (vector<Steen> stenen, string role) 
{
  //Lopen de elke rij af en printen de bijbehorende waardes
  for (int rij = 0; rij < 4; rij++)
  {
    if (rij == 2)
    {
      cout << role << "  ";
      for (int i = 0; i < stenen.size(); i++)
        cout << stenen[i].getOost() << "   " << stenen[i].getWest() << "  ";    
    }
    else
    {
      for (int i = 0; i < role.length(); i++)
        cout << " ";
      cout << "  ";
    }  
    if (rij == 0)
      for (int i = 0; i < stenen.size(); i++)
        cout << " (" << stenen[i].getSteenNummer() << ")   ";
    if (rij == 1)
      for (int i = 0; i < stenen.size(); i++)
        cout << "  " << stenen[i].getNoord() << "    ";
    if (rij == 3)
      for (int i = 0; i < stenen.size(); i++)
        cout << "  " << stenen[i].getZuid() << "    ";     
    cout << endl;
  } 
  cout << endl;   
}  // printStenen

//*************************************************************************

void AapjeOmino::drukAf()
{
  cout << endl;
  //Om het hele bord af te kunnen drukken, maken we een char array met alle symbolen erin
  int h = 3 * hoogte + 1;
  int b = 3 * breedte + 1;
  char printBord[h][b];
  for (int i = 0; i <  h; i++)
    for (int j = 0; j < b; j++)
      printBord[i][j] = ' ';
  
  for (int i = 0; i < hoogte; i++)
  {
    for (int j = 0; j < breedte; j++)
    {
      //Nummers van de rijen en kolommen
      if (i == 0)
          printBord[0][3 * j + 2] = j + '0';
      if (j == 0 )
          printBord[3 * i + 2][0] = i + '0';
      if (bord[i][j].first == -1)
      {
        //.
        printBord[3 * i + 1][3 * j + 2] = '.';
        printBord[3 * i + 2][3 * j + 3] = '.';
        printBord[3 * i + 3][3 * j + 2] = '.';
        printBord[3 * i + 2][3 * j + 1] = '.';
      }
      //Stenen zichzelf
      else
      {
        vector <Steen>::iterator it;
        for (it = stenenOpHetBord.begin(); it != stenenOpHetBord.end(); it++) 
          if (it->getSteenNummer() == bord[i][j].first)
            break;
        Steen currentSteen = *it;
        currentSteen.roteer(bord[i][j].second);
        
        printBord[3 * i + 1][3 * j + 2] = currentSteen.getNoord() + '0';
        printBord[3 * i + 2][3 * j + 3] = currentSteen.getOost() + '0';
        printBord[3 * i + 3][3 * j + 2] = currentSteen.getZuid() + '0';
        printBord[3 * i + 2][3 * j + 1] = currentSteen.getWest() + '0';
      }
    }
  }
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < b; j++)
      cout << printBord[i][j] << " ";
    cout << endl;
  }
  cout << endl;
  //Handen
  string role;
  role = "Femke:";
  printStenen(Femke, role);
  role = "Lieke:";
  printStenen(Lieke, role);
  role = "Pot:  ";
  printStenen(pot, role);
  cout << "Aan de beurt is: ";
  if (aanBeurt == 1)
    cout << "Femke";
  else
    cout << "Lieke";
  cout << endl; 
}  // drukAf

//*************************************************************************

bool AapjeOmino::heeftEenBuur (int i, int j) 
{
  //Heeft een buur ten noorden
  if (i > 0 && bord[i - 1][j].first != -1)
    return true;
  //Heeft een buur ten oosten
  if (j < breedte - 1 && bord[i][j + 1].first != -1)
    return true;
  //Heeft een buur ten zuiden
  if (i < hoogte - 1 && bord[i + 1][j].first != -1)
    return true;
  //Heeft een buur ten westen
  if (j > 0 && bord[i][j - 1].first != -1)
    return true;
  return false;
}  // heeftEenBuur

//*************************************************************************

bool * AapjeOmino::waarIsBuur( int i, int j) 
{
  //Array met (mogelijke) buren
  static bool buren[4];
  for (int it = 0; it < 4; it++)
    buren[it] = false; 
  //Er is een buur ten noorden
  if (i > 0 && bord[i - 1][j].first != -1) 
    buren[0] = true;
  //Er is  een buur ten oosten
  if (j < breedte - 1 && bord[i][j + 1].first != -1)
    buren[1] = true;
  //Er is een buur ten zuiden
  if (i < hoogte - 1 && bord[i + 1][j].first != -1) 
    buren[2] = true;
  //Er is een buur ten westen
  if (j > 0 && bord[i][j - 1].first != -1)
    buren[3] = true;
  return buren;
}  // waarIsBuur

//*************************************************************************

bool AapjeOmino::match (Steen steen, int i, int j)
{
  //Om te checken of de steen bij alle buren past
  bool noordKlopt = true;
  bool oostKlopt = true;
  bool zuidKlopt = true;
  bool westKlopt = true;
  //Het array met mogelijke buren
  bool * buren = waarIsBuur(i, j);
  //Als er wel een buur is, kijken of de steen er niet bij past.

  //Noord buur
  if (buren[0])
  {
    //Iterator naar steen op het bord
    vector <Steen>::iterator it;
    for (it = stenenOpHetBord.begin(); it != stenenOpHetBord.end(); it++) 
      if (it->getSteenNummer() == bord[i - 1][j].first)
        break;
    Steen S = *it;
    //Roteren
    S.roteer(bord[i - 1][j].second);
    //Als er geen match is...
    if (steen.getNoord() != S.getZuid())
      noordKlopt = false;
  }
  //Oost buur
  if (buren[1]) 
  {
    vector <Steen>::iterator it;
    for (it = stenenOpHetBord.begin(); it != stenenOpHetBord.end(); it++) 
      if (it->getSteenNummer() == bord[i][j + 1].first)
        break;
    Steen S = *it;
    S.roteer(bord[i][j + 1].second);
    if (steen.getOost() != S.getWest())
      oostKlopt = false;
  }
  //Zuid buur
  if (buren[2])
  {
    vector <Steen>::iterator it;
    for (it = stenenOpHetBord.begin(); it != stenenOpHetBord.end(); it++) 
      if (it->getSteenNummer() == bord[i + 1][j].first)
        break;
    Steen S = *it;
    S.roteer(bord[i + 1][j].second);
    if (steen.getZuid() != S.getNoord()) 
      zuidKlopt = false;
  }
  //West buur
  if (buren[3])
  {
    vector <Steen>::iterator it;
    for (it = stenenOpHetBord.begin(); it != stenenOpHetBord.end(); it++) 
      if (it->getSteenNummer() == bord[i][j - 1].first)
        break;
    Steen S = *it;
    S.roteer(bord[i][j - 1].second);
    if (steen.getWest() != S.getOost()) 
      westKlopt = false;
  }
  if (noordKlopt && oostKlopt && zuidKlopt && westKlopt) 
    return true;
  return false;
}  // match

//*************************************************************************

vector <Zet> AapjeOmino::bepaalMogelijkeZetten ()
{ 
  vector <Zet> zetten;
  //Speler aan de beurt
  vector <Steen> speler;
  speler = (aanBeurt == 1) ? Femke : Lieke;
  
  //Het hele bord af lopen
  for (int i = 0; i < hoogte; i++) 
  {
    for (int j = 0; j < breedte; j++) 
    {
      //Checken of er een steen geplaats mag worden
      if (bord[i][j].first == -1 && heeftEenBuur(i, j)) 
      {
        //Alle stenen van de speler aflopen
        for (vector <Steen>::iterator it = speler.begin(); it != speler.end(); it++) 
        {
          Steen currentSteen;
          //Kijken naar alle rotaties
          for (int k = 0; k < 4; k++) 
          {
            currentSteen = *it;
            currentSteen.roteer(k);
            //Als er een match is, een nieuwe zet toevoegen
            if (match(currentSteen, i, j)) 
            {
              Zet newZet(currentSteen.getSteenNummer(), k, i, j);
              zetten.push_back(newZet);
            }
          }
        }
      }
    }
  }
  return zetten;
}  // bepaalMogelijkeZetten

//*************************************************************************

int AapjeOmino::haalSteenUitPot ()
{
  //Als het mogelijk is om een steen uit de pot te pakken
  if (!pot.empty() && steenGepakt == false && bepaalMogelijkeZetten().empty()) 
  {
    //Pak dan een steen
    if (aanBeurt == 1)
    {
      Femke.push_back(pot[0]); 
      pot.erase(pot.begin());                
      steenGepakt = true;         
      return Femke.back().getSteenNummer();
    }
    if (aanBeurt == 2) 
    { 
      Lieke.push_back(pot[0]);
      pot.erase(pot.begin());
      steenGepakt = true;
      return Lieke.back().getSteenNummer();
    }
  }
  return -1;
}  // haalSteenUitPot

//*************************************************************************

void AapjeOmino::wisselSpeler ()
{ 
  aanBeurt = (aanBeurt == 1) ? 2 : 1;
  steenGepakt = false;
}  // wisselSpeler

//*************************************************************************

bool AapjeOmino::doeZet (Zet zet)
{
  //Speler aan de beurt
  vector <Steen> speler;
  speler = (aanBeurt == 1) ? Femke : Lieke;
  vector <Steen>::iterator it;
  int index, k = 0;
  
  //Een index van de steen in zet zoeken
  for (it = speler.begin(); it != speler.end(); ++it) 
  {
    if (it->getSteenNummer() == zet.getI())
    {
      index = k;
      break;
    }
    k++;
  }
  //Geen zulke steen
  if (it == speler.end())
    return false;
    
  Steen steen = *it;
  steen.roteer(zet.getR());
  //Benodigde checks
  if (zet.getI() > 0 && zet.getI() < nrStenen &&
      zet.getR() >= 0 && zet.getR() <= 3 &&
      bord[zet.getRij()][zet.getKolom()].first == -1 &&
      heeftEenBuur(zet.getRij(), zet.getKolom()) &&
      match(steen, zet.getRij(), zet.getKolom())) 
  {
    //de zet doen
    bord[zet.getRij()][zet.getKolom()].first = zet.getI();
    bord[zet.getRij()][zet.getKolom()].second = zet.getR(); 
    stenenOpHetBord.push_back(*it);
    
    if (aanBeurt == 1)
      Femke.erase(Femke.begin() + index);
    else
      Lieke.erase(Lieke.begin() + index);
    wisselSpeler();
    return true;
   }//if
  return false;
}  // doeZet

//*************************************************************************

vector<Zet> AapjeOmino::bepaalGoedeZetten ()
{ 
  vector<Zet> zetten;
  vector<Zet> mogelijkeZetten = bepaalMogelijkeZetten();
  //Huidige aantal buren
  int aantalBuren;
  //Max aantal buren
  int maxAantal = 0;
  //We lopen de alle mogelijke zetten af en zoeken een zet waar de steen het hoogste aantal buren heeft
  for (vector <Zet>::iterator it = mogelijkeZetten.begin(); it != mogelijkeZetten.end(); ++it) 
  {
    bool * buur = waarIsBuur(it->getRij(), it->getKolom());
    aantalBuren = 0;
    if (buur[0]) 
      aantalBuren++;
    if (buur[1]) 
      aantalBuren++;
    if (buur[2]) 
      aantalBuren++;
    if (buur[3])
      aantalBuren++;
    //Een betere zet
    if (aantalBuren > maxAantal) 
    {
      maxAantal = aantalBuren;
      zetten.clear();
    }
    //Even goede zet (en ook een betere zet) worden opgeslaagd 
    if (aantalBuren >= maxAantal) 
    {
      Zet newZet(it->getI(), it->getR(), it->getRij(), it->getKolom());
      zetten.push_back(newZet);
    }
  }
  return zetten;
}  // bepaalGoedeZetten

//*************************************************************************

void AapjeOmino::undoZet ()
{
  //Bepalen een steen dat geretourneerd moet worden en retourneren hem
  Steen returnSteen = stenenOpHetBord.back();
  if (aanBeurt == 1)
    Femke.push_back(returnSteen);
  else
    Lieke.push_back(returnSteen);
  stenenOpHetBord.pop_back();
  //Verwijderen uit het bord
  for (int i = 0; i < hoogte; i++)
  {
    for (int j = 0; j < breedte; j++)
    {
      if (bord[i][j].first == returnSteen.getSteenNummer())
      {
        bord[i][j].first = -1;
        bord[i][j].second = 0;
      }
    }
  }
}  // undoZet

//*************************************************************************

void AapjeOmino::undoPot (int steenN)
{
  //Voor een speler die de steen uit het pot gepaakt had,
  //retouneren steen naar het pot en verwijderen de steen van een speler
  int pos;
  if (aanBeurt == 1)
  {
    for (int i = 0; i < Femke.size(); i++) 
      if (Femke[i].getSteenNummer() == steenN) 
        pos = i;
    pot.insert(pot.begin(), Femke.at(pos));
    Femke.erase(Femke.begin() + pos);
  }
  if (aanBeurt == 2)
  {
    for (int i = 0; i < Lieke.size(); i++)
      if (Lieke[i].getSteenNummer() == steenN) 
        pos = i;
    pot.insert(pot.begin(), Lieke.at(pos));
    Lieke.erase(Lieke.begin() + pos);
  }  
}  // undoPot

//*************************************************************************

int AapjeOmino::padNaarBesteScore (int currentSpeler, int recursieLevel, 
                                   int & maxScore, vector<Zet> & besteZetten, 
                                   long long & aantalStanden)
{
  //Eindstand (basis van recursieve aanroep)
  if (eindstand())
  {
    int score = int(Lieke.size()) - int(Femke.size());
    if (currentSpeler == 1) 
      return score;
    return -score;
  }
  //Als een steen uit de pot gepakt is
  bool gepakt = false;
  //Current score
  int score;
  //Speler aan de beurt
  int spelerADBeurt = aanBeurt;

  //Pakken als het nodig en mogelijk is een steen uit de pot
  int nummerVDSteen = haalSteenUitPot();
  if (nummerVDSteen != -1) 
    gepakt = true;
  
  //Vepalen mogelijke zetten
  vector <Zet> zetten = bepaalMogelijkeZetten();

  //Als er nog steeds geen mogelijke zetten
  if (zetten.empty())
  {
    //De beurt gaat naar een andere speel
    wisselSpeler();
    aantalStanden++;
    //padNaarBesteScore voor een veranderende speler
    score = padNaarBesteScore (currentSpeler, recursieLevel + 1, 
                               maxScore, besteZetten, aantalStanden);
    //Bewaren de hoogste score
    if (score > maxScore)
    {
      maxScore = score;
      besteZetten.clear();
    }
    //Terug naar de goede speler
    aanBeurt = spelerADBeurt;
    
    //De steen terug naar de pot terugzetten
    if (nummerVDSteen != -1)
      undoPot(nummerVDSteen);
    return maxScore;
  }
  
  //Speler heeft wel een zet OF hij heeft een steen gepakt en kan nu een zet uitvoeren
  for (vector<Zet>::iterator it = zetten.begin(); it != zetten.end(); ++it)
  {
    aanBeurt = spelerADBeurt;
    //Doen een zet
    if (!doeZet(*it))
      continue;
    aantalStanden++;
    //padNaarBesteScore voor een veranderende speler
    score = padNaarBesteScore(currentSpeler, recursieLevel + 1, 
                              maxScore, besteZetten, aantalStanden);
    //Bewaren de hoogste score
    if (score > maxScore)
    {
      maxScore = score;
      besteZetten.clear();
    }
    //Bewaren de beste zetten
    if (score == maxScore && recursieLevel == 0)
      besteZetten.push_back(*it);
    //Terug naar een goede speler
    aanBeurt = spelerADBeurt;
    undoZet();
  }
  //Terug naar een goede speler
  aanBeurt = spelerADBeurt;
  //Als een steen gepakt was
  if (gepakt)
    undoPot(nummerVDSteen);
  return maxScore;
}  // padNaarBesteScore

//*************************************************************************

int AapjeOmino::optimaalSpel (int currentSpeler, Zet & besteZet, 
                              long long & aantalStanden)
{
   //Eindstand (basis van recursieve aanroep)
  if (eindstand())
  {
    int score = int(Lieke.size()) - int(Femke.size());
    if (currentSpeler == 1) 
      return score;
    return -score;
  }
  //Hetzelfde principe als bij padNaarBesteScore
  bool gepakt = false;
  int score;
  int spelerADBeurt = aanBeurt;
  //Pakken als het nodig en mogelijk is een steen uit de pot
  int nummerVDSteen = haalSteenUitPot();
  if (nummerVDSteen != -1) 
    gepakt = true;
  //Beste zetten voor een huidige speler
  vector <Zet> zetten;
  int optimaleScore = INT_MIN;
  
  //Bepalen de beste score en zetten voor een huidige speler
  padNaarBesteScore(spelerADBeurt, 0, optimaleScore, zetten, aantalStanden);

  //Speler kan geen zet uitvoeren 
  if (zetten.empty() || !doeZet(zetten[0]))
  {
    wisselSpeler();
    aantalStanden++;
    //Verwisselen speler en bepalen optimaalSpel voor een veraderende speler
    score = optimaalSpel (currentSpeler, besteZet, aantalStanden);
    //Bewaren de hoogste score
    if (score > maxScore)
    {
      maxScore = score;
      besteZet.setDefaultWaardes();
    }
    //Terug naar een goede speler
    aanBeurt = spelerADBeurt;
    
    //Een steen terug naar de pot terugzetten
    if (nummerVDSteen != -1)
      undoPot(nummerVDSteen);
    return maxScore;
  }
  
  aantalStanden++;
  //Bepalen optimaalSpel voor een veraderende speler
  score = optimaalSpel (currentSpeler, besteZet, aantalStanden);
  //Bewaren de hooste score
  if (score > maxScore)
    maxScore = score;
  //Bewaren de beste (eerste) zet
  if (score == maxScore)
    besteZet = zetten[0];
  //Terug naar een goede speler
  aanBeurt = spelerADBeurt;
  //Undo changes
  undoZet();
  if (gepakt)
    undoPot(nummerVDSteen);
  return maxScore;
}  // optimaalSpel

//*************************************************************************

int AapjeOmino::besteScore (Zet & besteZet, long long & aantalStanden)
{
  //Bij herhaaldelijk bepalen de beste score (en ook een zet) van een speler
  //die aan de beurt is, vinde wij de besteScore voor de speler
  //als beiden optimaal spelen. 
  int spelerADBeurt = aanBeurt;
  int score = optimaalSpel (spelerADBeurt, besteZet, aantalStanden);
  aanBeurt = spelerADBeurt;
  maxScore = INT_MIN;
  return score;
}  // besteScore

//*************************************************************************

bool AapjeOmino::genereerRandomSpel (int hoogte0, int breedte0,
       int nrStenen0, int nrStenenInHand0, int rij0, int kolom0,
       int minGetal, int maxGetal)
{
  int n, o, z, w;

  //Hoogte checken 
  if (!checkHoogte(hoogte0))
    return false;
  hoogte = hoogte0;
  //Breedte checken
  if (!checkBreedte(breedte0))
    return false;
  breedte = breedte0;
  //Aantal stenen checken (nrStenen >= 3!)
  if (!checkNrStenen(nrStenen0))
    return false;
  nrStenen = nrStenen0;
  //Beginaantal stenen van spelers checken
  if (!checkBeginAantalStenen(nrStenenInHand0))
    return false;
  //De positie van de 0-steen checken
  if (!checkPositieNULLSteen(rij0, kolom0))
    return false;

  //De waardes van de stenen genereren
  for (int i = 0; i < nrStenen; i++)
  {
    n = randomGetal(minGetal, maxGetal);
    o = randomGetal(minGetal, maxGetal);
    z = randomGetal(minGetal, maxGetal);
    w = randomGetal(minGetal, maxGetal);
    Steen newSteen(n, o, z, w, i);
    pot.push_back(newSteen);
  }
  //Stenen verdelen
  verdeelStenen(rij0, kolom0, nrStenenInHand0); 
  return true;
}  // genereerRandomSpel
