#include "TrajetSimple.h"
#include <string>
#include <fstream>
#include <iostream>
void TrajetSimple::Afficher()const
{
    cout<<VilleDepart<<"->"
    <<VilleArrive<<"("
    <<MoyenTransport<<")"
    <<"longueur:"<<longueur<<endl;
}
void TrajetSimple::Sauvgarder(ofstream & out)const 
{
    out<<"S "
       <<VilleDepart<<" "
       <<VilleArrive<<" "
       <<MoyenTransport<<" "
       <<longueur<<endl;
}
int TrajetSimple::GetLongueur()const 
{
    return longueur;
}
Trajet* TrajetSimple::clone() const
{ return new TrajetSimple(*this); }
TrajetSimple::TrajetSimple(const string & depart,
             const string & arrive,
             const string & transport,
             int len)
             :Trajet(depart,arrive,transport),
              longueur(len)
{
}
TrajetSimple::~TrajetSimple(){}