import os

def clear():
    os.system('cls' if os.name == 'nt' else 'clear')

"""
1. Implémentez une classe ListeChainee sans utiliser les listes de Python : vous devez donc d’abord
écrire une classe Noeud, puis utiliser cette classe pour votre ListeChainee.
"""

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
    
    def __repr__(self):
        return self.data

"""
2. Ajoutez les méthodes inserer(valeur, k), supprimer(k), rechercher(valeur), taille() et estVide()
"""

class LinkedList:
    def __init__(self):
        self.head = None

    # Print method using '->'
    def llprint(self):
        current = self.head
        while current:
            print(current.data, end=' -> ')
            current = current.next
        print('None')

    # Insertion method to insert a node at index k
    def insert(self, data, k):
        newNode = Node(data)
        if k == 0:
            newNode.next = self.head
            self.head = newNode
        else:
            current = self.head
            for i in range(k-1):
                current = current.next
            newNode.next = current.next
            current.next = newNode
    
    # Remove method to remove the node at index k
    def remove(self, k):
        current = self.head
        if k == 0:
            self.head = current.next
        else:
            for i in range(k-1):
                current = current.next
            current.next = current.next.next

    # Search method
    def search(self, data):
        current = self.head
        while current:
            if current.data == data:
                return True
            current = current.next
        return False

    # Size method
    def size(self):
        current = self.head
        size = 0
        while current:
            size += 1
            current = current.next
        return size
    
    # isEmpty method
    def isEmpty(self):
        return self.head == None

"""
Réutilisez le code de la question précédente pour implémenter une classe Pile et toutes ses méthodes.
Utilisez-la pour écrire un validateur de parenthésage, c’est-à-dire un programme qui prend en paramètre
un fichier texte, et qui valide que chaque caractère ouvrant {, <, ( ou [ est correectement associé au
caractère fermant correspondant (tous les éventuels autres caractères du fichier ne sont pas pris en compte).
Le programme doit écrire "Aucune erreur de syntaxe" si le fichier est valide, ou ”Erreur de syntaxe à la
ligne k”
"""

class Stack:
    def __init__(self):
        self.stack = []
    
    def push(self, data):
        self.stack.append(data)
    
    def peek(self):
        return self.stack[-1]

    def pop(self):
        return self.stack.pop()
    
    def isEmpty(self):
        return len(self.stack) == 0
    
    def __repr__(self):
        return str(self.stack) 


"""
Implémentez une classe HashTable. Utilisez-la pour écrire un programme qui compte le
nombre d’occurrences de chaque mot d’un texte. Complétez ensuite ce programme pour
qu’il affiche toutes les occurrences d’un mot recherché, et les affiche sous la forme :
Le mot 'algorithme' apparaît :
- à la ligne 3, mot 4
- à la ligne 7, mot 8
- à la ligne 17, mot 14
"""

# class HashTable: