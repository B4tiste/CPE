```python

# Union-find

def union(i, j):
    """
    Ajoute tous les éléments de l'ensemble auquele appartient x dans l'ensemble auquel
    appartient y
    """
    if same_set(i, j) == False:
        ens_i = find(i)
        ens_j = find(j)

        for k in range(len(union_find)):
            paire = union_find[k]
            if find(paire[0]) == ens_j:
                paire[1] = ens_i

    else:
        print(f"{i} et {j} appartiennent deja au meme ensemble")

def find(x):
    """
    Return le représentant de l'ensemble auquel appartient x
    """

    for i in range(len(union_find)):
        paire = union_find[i]
        if paire[0] == x:
            return paire[1]

def same_set(i, j):
    """
    return true si i et j appartiennent au meme ensemble (= si leur réprésentants sont égaux)
    """

    return find(i) == find(j)
    

# Tableau qui associe les items aux représentants de leur ensemble respectif
union_find = []

def init(n):
    """
    Fonction d'initialisation du tableau des representants
    """
    for i in range(n):
        union_find.append([i, i])

init(10)
print(union_find)

toFind = 2
print(f"find({toFind}) = {find(toFind)}")

tocheck = [3, 4]
print(f"same_set({tocheck}) = {same_set(tocheck[0], tocheck[1])}")

toUnite = [3, 4]
union(toUnite[0], toUnite[1])
print(union_find)
print(f"same_set({tocheck}) = {same_set(tocheck[0], tocheck[1])}")


```


```python
def find(x):
    for paire in union_find:
        if paire[0] == x:
            break
    while paire[0] != paire[1]:
        for p in union_find:
            if p[0] == paire[1]:
                paire = p 
    
    return paire[0]

def same_set(i, j):
    return find(i) == find(j)

def union(i, j):
    if same_set(i, j) == False:
        root_i, root_j = find(i), find(j)

        for p in union_find:
            if p[1] == root_j:
                p[1] = i
                break
    else:
        print(f"{i} et {j} ont deja la meme racine")


# Tableau qui associe les items aux représentants de leur ensemble respectif
union_find = []

def init(n):
    """
    Fonction d'initialisation du tableau des representants
    """
    for i in range(n):
        union_find.append([i, i])

init(10)
print(union_find)

union_find[4][1] = 9
union_find[9][1] = 3
print(union_find)

toFindRoot = 4
print(f"Racine de {toFindRoot} = {find(toFindRoot)}")

tocheck = [3, 2]
print(f"same_set({tocheck}) = {same_set(tocheck[0], tocheck[1])}")

toUnion = [2, 4]
print(f"Racine de 2 : {find(2)}, racine de 4 : {find(4)}")
union(toUnion[0], toUnion[1])
print(union_find)
print(f"same_set({toUnion}) = {same_set(toUnion[0], toUnion[1])}")

union(toUnion[0], toUnion[1])
```

```python
"""
tbl = [....]

if sum(tbl[:i]) == sum(tbl[i:]) --> i est un indice équil

if sum(tbl) == 0 --> 0 est un indice équil

if sum(tbl[:len(tbl)-2]) == 0 --> len(tbl)-1 equil

[0, -3, 5, -4, -2, 3, 1, 0] -> 0, 3, 7
"""
import random

# tbl = [random.randint(-5,5) for i in range(10)]

tbl = [0, -3, 5, -4, -2, 3, 1, 0]

l_equil = []

# l_equil = [i for i in range(len(tbl)) if sum(tbl[:i]) == sum(tbl[i+1:])]

# for i in range(len(tbl)):
#     if sum(tbl[:i]) == sum(tbl[i+1:]):
#         l_equil.append(i)

gauche = []

for i in range(len(tbl)):
    gauche.append(sum(tbl[:i]))

print(tbl)
# print(gauche)
print(gauche[::-1])
print(l_equil)

tbl = [i for i in reversed(range(10))]
# print(tbl)
```

