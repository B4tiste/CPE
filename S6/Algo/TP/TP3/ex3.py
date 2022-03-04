
# Exercice 3 : la suite de Fibonacci



'''
Suite de fibonnacci : 
    fn = f(n-1) + f(n-2)
'''

cpt = 0
# Fonction fibonacci récursive
def fibonacci1(n):
    if n <= 1 : return 1
    else :
        return fibonacci1(n-1) + fibonacci1(n-2)

l_fibo = [fibonacci1(i) for i in range(10)]

print(f"Fibo(10) : {l_fibo}")

# Affichage des temps de calcul de f5, f10, f20, f30, f40

import time

t1 = time.time()
fibonacci1(5)
print(f"Temps de calcul de F5 : {(time.time() - t1)*1000} ms") # 0.0 ms

t1 = time.time()
fibonacci1(10)
print(f"Temps de calcul de F10 : {(time.time() - t1)*1000} ms") # 0.0 ms

t1 = time.time()
fibonacci1(20)
print(f"Temps de calcul de F20 : {(time.time() - t1)*1000} ms") # 2.00 ms

t1 = time.time()
fibonacci1(30)
print(f"Temps de calcul de F30 : {(time.time() - t1)*1000} ms") # 334.9 ms

'''
t1 = time.time()
fibonacci1(40)
print(f"Temps de calcul de F40 : {(time.time() - t1)*1000} ms") #41344 ms
'''


# Afficher l'arbre de récurrence de f5 :

def tracer(f):
	decalage = 0
	def g(x):
		nonlocal decalage
		print('|        ' * decalage, end='')
		print('|Appel {}({})'.format(f.__name__,x))
		decalage +=1
		imagefx = f(x)
		print('|        ' * decalage, end='')
		print('|-> retourne {}'.format(imagefx) )
		decalage -= 1
		return imagefx
	return g

# On ajoute un decorateur pour tracer les appels
fibonacci1 = tracer(fibonacci1)

print("Affichage de l'arbre de calcul de F5")
fibonacci1(5)

'''
    Arbre de récurrence du calcul de f5 :
    |Appel fibonacci1(5)
|        |Appel fibonacci1(4)
|        |        |Appel fibonacci1(3)
|        |        |        |Appel fibonacci1(2)
|        |        |        |        |Appel fibonacci1(1)
|        |        |        |        |        |-> retourne 1
|        |        |        |        |Appel fibonacci1(0)
|        |        |        |        |        |-> retourne 0
|        |        |        |        |-> retourne 1
|        |        |        |Appel fibonacci1(1)
|        |        |        |        |-> retourne 1
|        |        |        |-> retourne 2
|        |        |Appel fibonacci1(2)
|        |        |        |Appel fibonacci1(1)
|        |        |        |        |-> retourne 1
|        |        |        |Appel fibonacci1(0)
|        |        |        |        |-> retourne 0
|        |        |        |-> retourne 1
|        |        |-> retourne 3
|        |Appel fibonacci1(3)
|        |        |Appel fibonacci1(2)
|        |        |        |Appel fibonacci1(1)
|        |        |        |        |-> retourne 1
|        |        |        |Appel fibonacci1(0)
|        |        |        |        |-> retourne 0
|        |        |        |-> retourne 1
|        |        |Appel fibonacci1(1)
|        |        |        |-> retourne 1
|        |        |-> retourne 2
|        |-> retourne 5
'''

print('===========================')
print('Fibonacci optimisée avec mémoire des valeurs')

# ==> On perds trop de temps en calculant de nombreuses valeurs plusieurs fois

# Fonction récursive fibonnaci2 qui garde en mémoire les valeurs déjà calculées
def fibonacci2(n):
    valeurs_memorisees  = {0:1, 1:1}

    def fibo(n):
        if n in valeurs_memorisees : return valeurs_memorisees[n]
        else :
            f = fibo(n-1) + fibo(n-2)
            valeurs_memorisees [n] = f
            return f
    
    return fibo(n)

t1 = time.time()
print(f"2F(400) : {fibonacci2(400)}")
print(f"Temps de calcul de 2F400 : {(time.time() - t1)*1000} ms")

print('===========================')
print('Fibonacci optimisée avec récursion terminale')

def fibonacci3(n, a=1, b=1):
    if n==0 : return a
    elif n==1 : return b
    else : return fibonacci3(n-1, b, a+b)


t1 = time.time()
print(f"3F(400) : {fibonacci3(400)}")
print(f"Temps de calcul de 3F400 : {(time.time() - t1)*1000} ms")

