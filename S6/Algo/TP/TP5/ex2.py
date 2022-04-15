# Question 4 de l'exo 2

# Expression mathématique écrite avec la notation polonaise inverse :
ex = "1 2 + 4 * 3 +".split()

operateurs = {
    "+": (lambda x, y: x + y),
    "-": (lambda x, y: x - y),
    "/": (lambda x, y: x / y),
    "*": (lambda x, y: x * y)
}

def NPI(expression):

    stack = []

    for z in expression:
        if z not in operateurs.keys():
            stack.append(int(z))
            continue

        operande1 = stack.pop()
        operande2 = stack.pop()

        stack.append(operateurs[z](operande2, operande1))
    
    return stack[0]

print(f"Résultat de l'expression NPI [{' '.join(ex)}] : {NPI(ex)}")