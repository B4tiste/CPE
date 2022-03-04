# Exercice 1 : Une première fonction récursive

'''
Ecrire une fonction récurive qui affiche les nombre de 1 à n dans l'ordre croissant, 
    et une autre qui affiche les nombres de n à 1.
'''

# Croissant
def afficher_nombre_croissant(n):
    if n <= 0 :
        print(n)
    else :
        afficher_nombre_croissant(n-1)
        print(n)

# Decroissant
def afficher_nombre_decroissant(n):
    print(n)
    if n != 0:
        afficher_nombre_decroissant(n-1)


print("Valeur de n : 4")
print("0 à n :")
afficher_nombre_croissant(4)
print("n à 0 :")
afficher_nombre_decroissant(4)
