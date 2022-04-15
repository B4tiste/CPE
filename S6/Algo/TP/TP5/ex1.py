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


class BinaryTree:
    def __init__(self, value):
        self.root = Node(value)

    def insert(self, value):
        self.insert_node(self.root, value)

    def insert_node(self, node, value):
        if value < node.value:
            if node.left is None:
                node.left = Node(value)
            else:
                self.insert_node(node.left, value)
        else:
            if node.right is None:
                node.right = Node(value)
            else:
                self.insert_node(node.right, value)

    def aff(self):
        self.aff_node(self.root, 0)

    def aff_node(self, node, indent):
        if node is None:
            return
        self.aff_node(node.right, indent + 1)
        print('\t' * indent + f'{indent}-', node.value)
        self.aff_node(node.left, indent + 1)

def suppr_node(root, value):
    if root is None:
        return None
    if value < root.value:
        root.left = suppr_node(root.left, value)
    elif value > root.value:
        root.right = suppr_node(root.right, value)
    else:
        if root.left is None:
            return root.right
        elif root.right is None:
            return root.left
        else:
            temp = root.right
            while temp.left is not None:
                temp = temp.left
            root.value = temp.value
            root.right = suppr_node(root.right, temp.value)
    return root

print(liste)

# Création d'un arbre binaire de recherche à partir de la liste de gauche à droite
tree = BinaryTree(liste[0])
for i in range(1, len(liste)):
    tree.insert(liste[i])


# Afficher l'arbre
tree.aff()

print("==================================")

suppr_node(tree.root, 35)

print('Après suppression de la valeur 35 :')
tree.aff()

print("==================================")

suppr_node(tree.root, 25)

print('Après suppression de la valeur 25 :')
tree.aff()