#ifndef TRAJET_H
#define TRAJET_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Trajet
{
public:
    virtual void Afficher() const;

    const string & GetVilleDepart() const;
    const string & GetVilleArrive() const;
    const string & GetMoyenTransport() const;
    virtual Trajet* clone() const = 0;
    virtual int GetLongueur() const = 0;

    Trajet(const string & VilleDepart,
           const string & VilleArrive,
           const string & MoyenTransport);

    virtual void Sauvgarder(ofstream & out) const = 0;

    
    friend ostream & operator<<(ostream & out, const Trajet & unTrajet);

    virtual ~Trajet();

protected:
    string VilleDepart;
    string VilleArrive;
    string MoyenTransport;
};

#endif
