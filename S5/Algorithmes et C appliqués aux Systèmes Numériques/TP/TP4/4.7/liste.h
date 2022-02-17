
struct liste_couleurs
{
    // Remplissez ça pour gérer une liste (simplement chainée) de scouleurs.

    // liste chainée de couleurs
    struct liste_couleurs *suivant;
    struct liste_couleurs *precedent;
    
};

void insertion (struct couleur *, struct liste_couleurs *);
void parcours (struct liste_couleurs *);


