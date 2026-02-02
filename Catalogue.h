#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Graphe.h"
using namespace std;
class Catalogue
{
    public:
        void Afficher()const;
        void Sauvgarder(const string & nomFichier);
        void Charger(const string & nomFichier);
        bool Equals(const TrajetSimple* a,const TrajetSimple* b)const;
        bool Equals(const TrajetCompose* a,const TrajetCompose* b)const;
        bool VerifierRecherche(const Trajet* t) const;
        void RechercheChemins(const string& depart,const string& arrive)const;
        Graphe& GetGraphe();
        const vector<Trajet *>& GetTrajet()const;
        void AjouterTrajet(Trajet * t);
    protected:
        vector<Trajet*> catalogue;
        Graphe graphe;
};
#endif
