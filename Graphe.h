#ifndef GRAPHE_H
#define GRAPHE_H
#include <map>
#include <vector>
#include <string>
#include "Trajet.h"
using namespace std;
class Graphe 
{
    public:
           void AjouterTrajet(const Trajet * t);
           void Afficher()const;
           void ChercherCheminsPossibles(const string & depart,const string & arrive)const;
           void ChercherPlusCourtChemin(const string & depart,const string & arrive)const;
           Graphe();
           ~Graphe();
    private:
           map<string,vector<const Trajet*>>graphe;
           map<string,int>distance;
           void DFS(const string & courant,const string & arrive,map<string,bool> & visite,vector<string>&chemin)const;
           
};
#endif
