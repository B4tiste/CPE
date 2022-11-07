"""
Pour calculer la somme des éléments d’une liste L à N entiers (initialisée aléatoirement) on
utilise deux processus qui s’exécutent en parallèle. Le processus P1 parcourt les éléments
d’indice impair et le processus P2 parcourt les éléments d’indice pair. Le processus père lance
les 2 processus P1 et P2. A la fin d’exécution de P1 et P2, le processus père récupère les 2
résultats R1 et R2 déposés dans un tube T par les deux processus et affiche la somme de R1 et
R2. 
"""

"""
#Processus P1
i = 1
SommeImpairs = 0
Tant que (i ≤ N)
faire
 SommeImpairs=SommeImpairs+L[i]
 i = i + 2
FinTantque
Déposer SommeImpairs dans le tube T 
"""

"""
#Processus P2
i = 0
SommePairs = 0
Tant que (i ≤ N)
faire
 SommePairs := Somme SommePairs + L[i]
 i = i + 2
FinTantque
Déposer SommePairs dans le tube T
"""

import os
import random

liste = [random.randint(0, 100) for i in range(10)]
print(liste, sum(liste))

def sommeImpairs():
    somme = 0
    for i in range(1, len(liste), 2):
        somme += liste[i]
    return somme

def sommePairs():
    somme = 0
    for i in range(0, len(liste), 2):
        somme += liste[i]
    return somme

def main():
    tube = os.pipe()
    pid = os.fork()

    if pid == 0:
        # Processus fils
        os.close(tube[0])
        # On écrit dans le tube la somme des éléments pairs
        os.write(tube[1], str(sommeImpairs()).encode())
        os.close(tube[1])
    else:
        # Processus "sous père"
        pid = os.fork()
        if pid == 0:
            # Processus fils
            os.close(tube[0])
            # On écrit la somme des pairs dans le tube
            os.write(tube[1], str(sommePairs()).encode())
            os.close(tube[1])
        else:
            # Processus père
            os.close(tube[1])
            somme = 0
            # Récupération des résultats
            for _ in range(2):
                somme += int(os.read(tube[0], 100).decode())
            print(somme)
            os.close(tube[0])
    
if __name__ == "__main__":
    main()