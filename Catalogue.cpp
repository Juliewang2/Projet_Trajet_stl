#include "Trajet.h"
#include "TrajetCompose.h"
#include "TrajetSimple.h"
#include "Catalogue.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void Catalogue::Afficher()const
{
    for (const Trajet* t : catalogue){
        t->Afficher();
    }

}
void Catalogue::Sauvgarder(const string & nomFichier)
{
    ofstream fic(nomFichier);
    if (!fic) return;
    for (const Trajet* t:catalogue)
    {
        t->Sauvgarder(fic);
    }

}
void Catalogue::Charger(const string & nomFichier)
{
    ifstream fic(nomFichier);
    if (!fic) return;

    string type;
    while (fic >> type)
    {
        if (type == "S")
        {
            string dep, arr, trans;
            int len;
            fic >> dep >> arr >> trans >> len;

            Trajet* t = new TrajetSimple(dep, arr, trans, len);
            catalogue.push_back(t);
            graphe.AjouterTrajet(t);
        }
        else if (type == "C")
        {
            int n;
            fic >> n;

            vector<Trajet*> unTrajCom;

            for (int i = 0; i < n; ++i)
            {
                string subType, dep, arr, trans;
                int len;

                fic >> subType;              // lit "S"
                fic >> dep >> arr >> trans >> len;

                TrajetSimple* ts = new TrajetSimple(dep, arr, trans, len);
                unTrajCom.push_back(ts);
                graphe.AjouterTrajet(ts);
            }

            Trajet* tc = new TrajetCompose(unTrajCom);
            catalogue.push_back(tc);
        }
    }
}

Graphe& Catalogue::GetGraphe(){return graphe;}
const vector<Trajet *>& Catalogue::GetTrajet()const
{
      return catalogue;
}
void Catalogue::AjouterTrajet(Trajet * t)
{
     if (!t)return;
     if (VerifierRecherche(t))
     {
             cout << "Trajet deja present dans le catalogue" << endl;
             delete t;
             return;
     }
     catalogue.push_back(t);
     graphe.AjouterTrajet(t);
}
bool Catalogue::Equals(const TrajetSimple* a,const TrajetSimple* b)const
{
     if (!a||!b) return false;
       return a->GetVilleDepart()  == b->GetVilleDepart() &&
                a->GetVilleArrive()  == b->GetVilleArrive() &&
                a->GetMoyenTransport() == b->GetMoyenTransport() &&
                a->GetLongueur()     == b->GetLongueur();
}
bool Catalogue::Equals(const TrajetCompose* a, const TrajetCompose* b)const
{
    if (!a || !b) return false;

    if (a->NbEtapes() != b->NbEtapes())
        return false;

    for (int i = 0; i < a->NbEtapes(); ++i)
    {
        const Trajet* etapeA = a->GetEtape(i);
        const Trajet* etapeB = b->GetEtape(i);
        
        const TrajetSimple* tsA = dynamic_cast<const TrajetSimple*>(etapeA);
        const TrajetSimple* tsB = dynamic_cast<const TrajetSimple*>(etapeB);
        
        if (!tsA || !tsB || !Equals(tsA, tsB))
            return false;
    }

    return true;
}
bool Catalogue::VerifierRecherche(const Trajet* t) const
{
    if (!t) return false;

    // ===== cas TrajetSimple =====
    if (auto ts = dynamic_cast<const TrajetSimple*>(t))
    {
        for (const Trajet* existant : catalogue)
        {
            auto tsExist = dynamic_cast<const TrajetSimple*>(existant);
            if (tsExist && Equals(ts, tsExist))
            {
                return true;
            }
        }
    }

    // ===== cas TrajetCompose =====
    if (auto tc = dynamic_cast<const TrajetCompose*>(t))
    {
        for (const Trajet* existant : catalogue)
        {
            auto tcExist = dynamic_cast<const TrajetCompose*>(existant);
            if (tcExist && Equals(tc, tcExist))
            {
                return true;
            }
        }
    }

    return false;
}
void Catalogue::RechercheChemins(const string& depart,const string& arrive)const
{
     graphe.ChercherCheminsPossibles(depart,arrive);
}











