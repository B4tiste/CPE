/*
Question 5. Coder en C une structure de données Capteur qui comporte les éléments
suivants : identifiant, temps, luminosité, pression, température, bâtiment. Les trois valeurs
des mesures (luminosité, pression, température) doivent être des nombres flottants.
L’élément bâtiment est la localisation de capteur, c’est-à-dire, le nom du bâtiment et son
adresse. temps correspond à l'heure à laquelle les valeurs du capteur ont été obtenues.
Instanciez une variable de cette structure. (2 points)
*/

#include <stdio.h>

struct Capteur{
    int identifiant;
    int temps;
    float luminosite;
    float pression;
    float temperature;
    char batiment[10];
};

int main(int argc, char const *argv[])
{
    
    struct Capteur capt = {0, 12, 1.5, 12.0, 35.5, "batA"};

    printf("ID : %d\n", capt.identifiant);
    printf("Temps d'acquisition : %d\n", capt.temps);
    printf("Luminosité : %f\n", capt.luminosite);
    printf("Pression : %f\n", capt.pression);
    printf("Temperature : %f\n", capt.temperature);
    printf("Batiment : %s\n", capt.batiment);

    return 0;
}
