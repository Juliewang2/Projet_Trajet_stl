#include "Trajet.h"

void Trajet::Afficher() const
{
    cout << VilleDepart << "->"
         << VilleArrive << " ("
         << MoyenTransport << ")" << endl;
}

const string & Trajet::GetVilleDepart() const
{
    return VilleDepart;
}

const string & Trajet::GetVilleArrive() const
{
    return VilleArrive;
}

const string & Trajet::GetMoyenTransport() const
{
    return MoyenTransport;
}

Trajet::Trajet(const string & depart,
               const string & arrive,
               const string & transport)
    : VilleDepart(depart),
      VilleArrive(arrive),
      MoyenTransport(transport)
{
}

Trajet::~Trajet() {}

ostream & operator<<(ostream & out, const Trajet & t)
{
    out << "VilleDepart: " << t.VilleDepart
        << " VilleArrive: " << t.VilleArrive
        << " MoyenTransport: " << t.MoyenTransport;
    return out;
}


          
