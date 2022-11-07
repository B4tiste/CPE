"""
On veut récupérer depuis le fichier donné en ligne de commande:
    - Le nombre de caractères
    - Le nombre de lignes
    - Le nombre de mots
    - Tous les mots distincts
    - Les vingts premiers mots du fichier
"""

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("file", help="Le fichier à analyser")

args = parser.parse_args()

# On ouvre le fichier
with open(args.file, "r") as f:
    # On récupère le contenu
    contenu = f.read()

    # On compte le nombre de caractères
    nbr_caracteres = len(contenu)

    # On compte le nombre de lignes
    nbr_lignes = len(contenu.splitlines())

    # On compte le nombre de mots
    nbr_mots = len(contenu.split())

    # On récupère tous les mots distincts
    mots_distincts = set(contenu.split())

    # On récupère les vingts premiers mots
    vingts_premiers_mots = contenu.split()[:20]

    # On affiche les résultats
    print(f"Nombre de caractères: {nbr_caracteres}")
    print(f"Nombre de lignes: {nbr_lignes}")
    print(f"Nombre de mots: {nbr_mots}")
    print(f"Mots distincts: {mots_distincts}")
    print(f"Vingts premiers mots: {vingts_premiers_mots}")


