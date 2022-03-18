# # Algorithme de tri

"""
Exercice 2 : Tri rapide
"""

import random

tableau = [random.randint(0, 100) for _ in range(40)]

print("Tableau de base : ", tableau)  

def partitionner(tableau, premier, dernier):
    pivot = tableau[dernier]
    i = premier - 1
    for j in range(premier, dernier):
        if tableau[j] <= pivot:
            i += 1
            tableau[i], tableau[j] = tableau[j], tableau[i]
    tableau[i+1], tableau[dernier] = tableau[dernier], tableau[i+1]
    return i+1


def quick_sort(tab, premier, dernier):
    if premier < dernier:
        pi = partitionner(tab, premier, dernier)
        quick_sort(tab, premier, pi - 1)
        quick_sort(tab, pi + 1, dernier)


quick_sort(tableau, 0, len(tableau) - 1)
print("Tableau trié : ", tableau)


