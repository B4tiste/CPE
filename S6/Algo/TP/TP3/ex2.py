# Exercice 2 : Suite de Syracuse / Conjecture de Collatz

'''
Suite de Syracuse : 
u(n+1) :
    - un/2 si un est pair
    - 3*un+1 si un est impair
'''

# Fonction syracuse recursive qui affiche sous forme de liste les valeurs de la suite de Syracuse de n 
def suite_syracuse_recursive(n):
    if n == 1:
        return [1]
    else:
        return [n] + suite_syracuse_recursive(n//2 if n%2 == 0 else 3*n+1)

'''
print(f"Suite de Syracuse : {suite_syracuse_recursive(13)}")
'''

# Afficher :
#   - la suite de Syracuse de n
#   - le temps de vol de la suite -> le plus petit indice de n tel que syracuse(n) == 1
#   - La valeur maximale de la suite

syracuse = suite_syracuse_recursive(27)


print(f"Suite de Syracuse : {syracuse}")
print(f"Temps de vol : {len(syracuse)}")
print(f"Altitude : {max(syracuse)}")


import matplotlib.pyplot as plt
import numpy as np

# Afficher graphiquement la suite suite de Syracuse
plt.figure()
plt.plot(np.arange(1, len(syracuse)+1), syracuse)

# Effectuer les suites de syracuse pour tous les entiers de 1 à 100, et mettre sur un graphique leurs temps de vol et altitude
altitudes = []
tps_de_vol = []

MAX = 1000

for i in range(1, MAX + 1):
    altitudes.append(max(suite_syracuse_recursive(i)))
    tps_de_vol.append(len(suite_syracuse_recursive(i)))


# Afficher en rouge les altitudes
plt.figure()
plt.plot(np.arange(1, MAX + 1), altitudes, color='red')
# Afficher en bleue les temps de vol
plt.figure()
plt.plot(np.arange(1, MAX + 1), tps_de_vol, color='blue')


plt.show()
