from lib import LinkedList, Stack, clear
import random

clear()

# Create a linked list
ll = LinkedList()

# Fill the linked list
for i in range(10):
    ll.insert(random.randint(0, 100), i)

# ============= Q2 =============
print('\n============= Q2 =============\n')

# Print the linked list
ll.llprint()

# Look for 4 in the linked list
print(f'4 is in the linked list: {ll.search(4)}')

# Look for 15 in the linked list
print(f'15 is in the linked list: {ll.search(15)}')

# Add 15 to the linked list
ll.insert(15, 7)

# Print the linked list
ll.llprint()

# Look for 15 in the linked list
print(f'15 is in the linked list: {ll.search(15)}')

# Print the size of the linked list
print(f'Size of the linked list: {ll.size()}')

# Delete the first node of the linked list
print('Deleting the first node of the linked list')
ll.remove(0)

# Print the new linked list
ll.llprint()
print(f'Size of the linked list: {ll.size()}')

# Delete all nodes of the linked list
print('Deleting all nodes of the linked list')
for i in range(ll.size()):
    ll.remove(0)

# Print the new linked list
ll.llprint()
print(f'Size of the linked list: {ll.size()}')

# ============= Q3 =============
print('\n============= Q3 =============\n')

char = '()[]{}<>'

# text = ')([{]}azeazeaze)'
text = '([{}azeazeaze])'

balanced = True

stk = Stack()

for i in text:
    if i in char:
        if i in '([{':
            stk.push(i)
        else:
            if stk.isEmpty():
                balanced = False
                break
            else:
                if stk.peek() == '(' and i == ')':
                    stk.pop()
                elif stk.peek() == '[' and i == ']':
                    stk.pop()
                elif stk.peek() == '{' and i == '}':
                    stk.pop()
                else:
                    balanced = False
                    break

print('The text is balanced' if balanced else 'The text is not balanced')

# ============= Q4 =============
print('\n============= Q4 =============\n')

# Tables de hachage

"""
Implémentez une classe HashTable. Utilisez-la pour écrire un programme qui compte le nombre d’occurrences de
chaque mot d’un texte. Complétez ensuite ce programme pour qu’il affiche toutes les occurrences
d’un mot recherché, et les affiche sous la forme :

Le mot 'algorithme' apparaît :
- à la ligne 3, mot 4
- à la ligne 7, mot 8
- à la ligne 17, mot 14
"""

texte = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod, urna eget aliquet aliquet, nisl nisl aliquet nisl, eget tincidunt nisl nisl eget nisl. Sed euismod,"

# class HashTable:


        