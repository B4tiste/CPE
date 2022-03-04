# Exercice 6 : Recherche dichotomique

def recherche(x, tbl):
    def dichotomie(minimum, maximum):
        """
        Recherche dichotomique dans une liste qui renvoie :
        - l'indice de l'élément recherché si il est présent
        - -1 sinon
        """
        if minimum > maximum:
            return -1
        m = (minimum + maximum)//2
        if tbl[m] == x:
            return m
        elif tbl[m] < x:
            return dichotomie(m+1, maximum)
        else:
            return dichotomie(minimum, m-1)

    return dichotomie(0, len(tbl)-1)


liste = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

print(f"5 se trouve à l'indice : {recherche(5, liste)}")
print(f"11 se trouve à l'indice : {recherche(11, liste)}")
