"""
    Grâce aux données présentes dans le fichier /data/population.csv, on veut :
        - La population la plus élevée et l'année associée
        - La population la plus faible et l'année associée
        - La population moyenne
"""

import csv

data_path = "./data/population.csv"

population_totale = 0

p_max = []
p_min = []

with open(data_path) as fichier :
    
    reader = csv.reader(fichier)

    cpt = 0

    for row in reader:
        if row[0].isdecimal():
            
            cpt += 1

            y, p = int(row[0]), int(row[1])

            # Init
            if p_max == []:
                p_max = [y, p]
            if p_min == []:
                p_min = [y, p]
            
            # Récupération des données
            population_totale += p

            if p > p_max[1] :
                p_max = [y, p]
            if p < p_min[1] :
                p_min = [y, p]

moyenne = population_totale/(cpt)

print(f"Pmin : {p_min}, Pmax : {p_max}, Moyenne : {moyenne}")

