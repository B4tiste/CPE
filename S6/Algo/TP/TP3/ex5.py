# Exercice 5 : Tours de Hanoï

def hanoi(n, a='départ', b='intermédiaire', c='objectif', z=1):
	"""
    a piquet de départ.
	b piquet intermédiaire.
	c piquet d'arrivée.
	n nombre d'anneaux à déplacer.
	z anneau déplacé.
    """
	if n == 1 :
		print(f"Déplacer l'anneau {z} du piquet {a} vers le piquet {c}")
	else:
		hanoi(n-1, a, c, b)
		hanoi(1, a, b, c, n)
		hanoi(n-1, b, a, c)


hanoi(5)