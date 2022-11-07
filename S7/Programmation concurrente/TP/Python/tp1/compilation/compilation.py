import os
import argparse

# On récupère les noms des fichiers passés en paramètre
parser = argparse.ArgumentParser()
parser.add_argument("fichiers", nargs="*", help="Les fichiers à compiler")
args = parser.parse_args()

fichiers = args.fichiers

path = "./src/"

# Pour chaque fichier, on lance un processus fils 
for fichier in fichiers:
    pid = os.fork()
    if pid == 0:
        # Processus fils
        # Compilation du fichier source et dépot dans le dossier obj
        os.system("gcc " + path + fichier + " -o obj/" + fichier[:-2] + ".out")

# On exécute les fichiers compilés
for fichier in fichiers:
    os.system("./obj/" + fichier[:-2] + ".out")