# Algorithme de tri

"""
Exercice 2 : Tri fusion
"""

import random

tableau = [random.randint(0, 100) for _ in range(40)]

print("Tableau de base : ", tableau)

def fusion(tab1, tab2):
    tab3 = []
    i = 0
    j = 0
    while i < len(tab1) and j < len(tab2):
        if tab1[i] < tab2[j]:
            tab3.append(tab1[i])
            i += 1
        else:
            tab3.append(tab2[j])
            j += 1
    if i < len(tab1):
        tab3.extend(tab1[i:])
    if j < len(tab2):
        tab3.extend(tab2[j:])
    return tab3

def tri_fusion(tab):
    # Compléxité : O(n log n)

    if len(tab) <= 1:
        return tab
    else:
        tab1 = tri_fusion(tab[:len(tab)//2])
        tab2 = tri_fusion(tab[len(tab)//2:])
        return fusion(tab1, tab2)


print("Tableau trié : ", tri_fusion(tableau))