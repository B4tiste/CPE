# Exo 3

"""
    L’opérateur ternaire ? : est un opérateur que l’on retrouve dans de nombreux langages de programmation,
et qui permet d’écrire de manière concise des conditions.

    Ainsi, au lieu d’écrire if a then b else c, on écrira plus simplement a?b:c.
"""


class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


# Fonction pour convertir une expression ternaire en arbre binaire

def convert(expression, i):

    if i >= len(expression):
        return None

    # Creation d'un nouveau node
    root = Node(expression[i])

    i += 1

    # Si c = ?
    # On ajoute le prochain c à gauche du node actuel
    if (i < len(expression) and expression[i] == "?"):
        root.left = convert(expression, i + 1)

    # Sinon on l'ajoute à droite
    elif i < len(expression):
        root.right = convert(expression, i + 1)

    return root


# Fonction pour afficher l'arbre binaire
def aff(root):
    if root is None:
        return
    aff(root.right)
    print(root.value)
    aff(root.left)


# Contruction de l'arbre à partir de l'expression

ex = "a?b:c"
# ex = "a?b?c:d:e"

root_node = convert(ex, 0)
aff(root_node)
