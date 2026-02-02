#include "TrajetCompose.h"
#include <iostream>
#include <fstream>
using namespace std;

TrajetCompose::TrajetCompose(const vector<Trajet*>& trajets) : Trajet("", "", "")
{
    for (const Trajet* t : trajets)
        unTrajCom.push_back(t->clone());
}

TrajetCompose::~TrajetCompose()
{
    for (Trajet* t : unTrajCom)
        delete t;
}

void TrajetCompose::Afficher() const
{
    cout << "C " << unTrajCom.size() << endl;
    for (const Trajet* t : unTrajCom)
        t->Afficher();
}

void TrajetCompose::Sauvgarder(ofstream& out) const
{
    out << "C " << unTrajCom.size() << endl;
    for (const Trajet* t : unTrajCom)
        t->Sauvgarder(out);
}

int TrajetCompose::NbEtapes() const
{
    return unTrajCom.size();
}

void TrajetCompose::AjouterEtape(Trajet* t)
{
    unTrajCom.push_back(t);
}

const Trajet* TrajetCompose::GetEtape(int i) const
{
    if (i < 0 || i >= (int)unTrajCom.size())
        return nullptr;
    return unTrajCom[i];
}

int TrajetCompose::GetLongueur() const
{
    int somme = 0;
    for (const Trajet* t : unTrajCom)
        somme += t->GetLongueur();
    return somme;
}
Trajet*TrajetCompose:: clone() const
{ return new TrajetCompose(*this); }

bool TrajetValide(const vector<Trajet*>& trajets)
{
    for (size_t i = 1; i < trajets.size(); ++i)
    {
        if (trajets[i - 1]->GetVilleArrive() != trajets[i]->GetVilleDepart())
            return false;
    }
    return true;
}
