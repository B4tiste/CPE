# -*- coding: utf-8 -*-
import multiprocessing as mp
import os
import sys
import math
import time

size = 1000
zoo = pow(0.5, 13.0 * 0.7)
percentCompletion = 1

print(f"Image de taille {size}x{size}")
NB_PROCESS = int(input(f"Entrer un nombre de processus (Entre 1 et {mp.cpu_count()}): "))
print(f"Rendu de l'image en cours avec {NB_PROCESS} processus...")

# Cette fonction permet de calculer la couleur d'un pixel en utilisant
def calcul(x, y, image, pixel_index):
    p_x = x/size * 2.0 - 1.0
    p_y = y/size * 2.0 - 1.0
    cc_x = -0.05 + p_x * zoo
    cc_y = 0.6805 + p_y * zoo
    z_x = 0.0
    z_y = 0.0
    m2 = 0.0
    co = 0.0
    dz_x = 0.0
    dz_y = 0.0
    for i in range(2560):
        old_dz_x = 0.0
        old_z_x = 0.0
        if m2 > 1024.0:
            break
        old_dz_x = dz_x
        dz_x = 2.0 * z_x * dz_x - z_y * dz_y + 1.0
        dz_y = 2.0 * z_x * dz_y + z_y * old_dz_x

        old_z_x = z_x
        z_x = cc_x + z_x * z_x - z_y * z_y
        z_y = cc_y + 2.0 * old_z_x * z_y
        m2 = z_x * z_x + z_y * z_y
        co += 1.0
    d = 0.0
    if co < 2560.0:
        dot_z = z_x * z_x + z_y * z_y
        d = math.sqrt(dot_z/(dz_x*dz_x+dz_y*dz_y)) * math.log(dot_z)
        image[pixel_index + 0] = int(co % 256)
        d = 4.0 * d / zoo
        if d < 0.0:
            d = 0.0
        if d > 1.0:
            d = 1.0
        image[pixel_index + 1] = int((1.0-d) * 76500 % 255.0)
        d = pow(d, 12.5) 

        image[pixel_index + 2] = int(d * 255.0)
    else:
        image[pixel_index + 0] = image[pixel_index + 1] = image[pixel_index + 2] = 0

"""
Maintenant créé une fonction qui peut créer 5 processus, chacun gérant le rendu d'une ligne
Quand une ligne est terminée, le processus envoie le résultat au processus principal, qui l'écrit dans l'image, et demande ensuite la ligne suivante à rendre
"""
def render_line(line, image):
    for x in range(size):
        calcul(x, line, image, 3*(line * size + x))

# Init the l'image dans un tableau partagé
image = mp.Array('B', size*size*3)

# monoProcess()
def monoProcess():
    for y in range(size):
        for x in range(size):
            calcul(x, y, image, 3*(y * size + x))

# multiProcess()
def multiProcess():
    #  Créer un pool de processus
    for pack in range(size//NB_PROCESS):
        # On les lance chacun sur la prochaine ligne à render
        for line in range(NB_PROCESS):
            p = mp.Process(target=render_line, args=(pack*NB_PROCESS+line, image))
            p.start()
        for line in range(NB_PROCESS):
            p.join()

        # Afficher la progression du rendu
        percentCompletion = round(pack * 100 / (size//NB_PROCESS))
        print("[" + "=" * (percentCompletion//2) + " " * (50 - percentCompletion//2) + "] " + str(percentCompletion) + "%", end="\r")


# Commencer le timer
start_time = time.time()
multiProcess()
end_time = time.time()

# Afficher le temps d'exécution avec 2 chiffres après la virgule
print(f"\nTemps d'exécution: {end_time - start_time:.2f} secondes")

fd = os.open("image1.ppm", os.O_CREAT | os.O_WRONLY, 0o644)
os.write(fd, "P6\n{} {}\n255\n".format(size, size).encode())
os.write(fd, bytes(image))
os.close(fd)
