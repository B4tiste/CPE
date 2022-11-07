import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("path", help="Le dossier à scanner")

args = parser.parse_args()

path = args.path

liste_fichiers = []

for root, dirs, fichiers in os.walk(path):

    for fichier in fichiers:
        liste_fichiers.append(os.path.join(root, fichier))

for nom in liste_fichiers :
    print(nom)
