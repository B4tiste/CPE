# Algorithme de tri

"""
Exercice 1 : Tri par insertion, tri par selection et Tri à bulles
"""

import random

tableau = [random.randint(0, 100) for _ in range(40)]

print("Tableau de base : ", tableau)


def insert_sort(tab):
    # Compléxité : O(n^2)

    for i in range(1, len(tab)-1):
        # Mémoriser t[i] dans une variable
        x = tab[i]

        # Décalage des éléments qui sont plus grands que x, en partant de tab[i-1]
        j = i
        while j > 0 and tab[j-1] > x:
            tab[j] = tab[j-1]
            j = j - 1

            # Placer x dans le trou créé par le décalage
            tab[j] = x

    return tab


def selection_sort(tab):
    # Compléxité : O(n^2)

    for i in range(0, len(tab) - 1):
        min = i
        for j in range(i+1, len(tab)):
            if tab[j] < tab[min]:
                min = j

        if min != i:
            tab[i], tab[min] = tab[min], tab[i]

    return tab


def bubble_sort(tab):
    # Compléxiter : O(n^2)

    for i in range(len(tab) - 1, 0, -1):
        for j in range(0, i):
            if tab[j+1] < tab[j]:
                tab[j+1], tab[j] = tab[j], tab[j+1]

    return tab

print("Tableau trié : ", insert_sort(tableau))
print("Tableau trié : ", selection_sort(tableau))
print("Tableau trié : ", bubble_sort(tableau))
