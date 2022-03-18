# Algorithme de tri

"""
Exercice 4 : Comparaison des temps de tri pour N : 10, 100, 1000, 10000, 100000
"""

import random
import time

# Augmenter la limite de recursivité pour pouvoir tester plus de temps
import sys
sys.setrecursionlimit(100000)

# Tri par insertion
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


# Tri par selection
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


# Tri à bulles
def bubble_sort(tab):
    # Compléxiter : O(n^2)

    for i in range(len(tab) - 1, 0, -1):
        for j in range(0, i):
            if tab[j+1] < tab[j]:
                tab[j+1], tab[j] = tab[j], tab[j+1]

    return tab
    

# Tri fusion
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


# Tri rapide
def quick_sort(tab):
    # Compléxité : O(n log n)

    if len(tab) <= 1:
        return tab
    else:
        pivot = tab[0]
        tab1 = [x for x in tab[1:] if x <= pivot]
        tab2 = [x for x in tab[1:] if x > pivot]
        return quick_sort(tab1) + [pivot] + quick_sort(tab2)

liste_taille = [10, 100, 1000, 10000, 100000, 1000000]

for taille in liste_taille:
    
    print("===========================")

    tableau = [random.randint(0, taille * 3) for _ in range(taille)]

    for i in range(5):
        # Création d'un tableau dupliqué :
        tableau_copy = []
        for j in range(len(tableau)):
            tableau_copy.append(tableau[j])

        t1 = time.time()

        if i == 0 and taille <= 10000:
            insert_sort(tableau)
            algo = "insertion"
            t2 = time.time()
            print(f"Taille : {taille} | Algorithme : {algo} | Temps : {t2 - t1}")

        if i == 1 and taille <= 10000:
            selection_sort(tableau)
            algo = "selection"
            t2 = time.time()
            print(f"Taille : {taille} | Algorithme : {algo} | Temps : {t2 - t1}")

        if i == 2 and taille <= 10000:
            bubble_sort(tableau)
            algo = "bubble"
            t2 = time.time()
            print(f"Taille : {taille} | Algorithme : {algo} | Temps : {t2 - t1}")

        if i == 3:
            tri_fusion(tableau)
            algo = "fusion"
            t2 = time.time()
            print(f"Taille : {taille} | Algorithme : {algo} | Temps : {t2 - t1}")

        if i == 4 and taille <= 10000:
            quick_sort(tableau)
            algo = "quick"
            t2 = time.time()
            print(f"Taille : {taille} | Algorithme : {algo} | Temps : {t2 - t1}")

        
