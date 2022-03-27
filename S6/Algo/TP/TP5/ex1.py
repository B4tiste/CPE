# Arbres

"""
Exercice 1 : Arbre binaire de recherche
"""

liste = [25, 60, 35, 10, 5, 20, 65, 45, 70, 40, 50, 55, 30, 15]

# Construire un arbre binaire de recherche à partir de la liste
# Classes necessaires : BinaryTree, Node

class Node: 
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None