

# Calcul max d'une liste avec Divisier / regner 

def maximum(liste):
    assert(len(liste) > 0)

    if len(liste) == 1 :
        return liste[0]
    
    else : 
        moitie = len(liste)//2
        
        l1 = liste[:moitie]
        l2 = liste[moitie:]
        
        max1 = maximum(l1)
        max2 = maximum(l2)

        if max1 > max2 : return max1
        else : return max2

import random

TAILLE = 100 
l = [random.randint(1, TAILLE*3) for i in range(TAILLE)]

print(f"Liste : {l}")
print(f"Maximum de la liste : {maximum(l)}")