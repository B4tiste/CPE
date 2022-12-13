import random
import random

N = 100

def formule(array):
    somme = 0

    formule = "math.sqrt(1 - math.pow(x, 2))"

    for nombre in array:
        f = formule.replace("x", str(nombre))
        somme += eval(f)
    
    return somme

# Tableau de N valeurs aléatoires entre 0 et 1
tableau = [random.random() for _ in range(N)]

print(f"Valeur de pi approchés{4*formule(tableau)/len(tableau)}")
