"""
    
    4IRC
    Exercice course hippique
    Groupe :
        - Maxime BATTU
        - Eileen BALAGUER
        - Batiste LALOI

"""


# Cours hippique
# Version très basique, sans mutex sur l'écran, sans arbitre, sans annoncer le gagant, ... ...

# Quelques codes d'échappement (tous ne sont pas utilisés)
CLEARSCR="\x1B[2J\x1B[;H"          #  Clear SCReen
CLEAREOS = "\x1B[J"                #  Clear End Of Screen
CLEARELN = "\x1B[2K"               #  Clear Entire LiNe
CLEARCUP = "\x1B[1J"               #  Clear Curseur UP
GOTOYX   = "\x1B[%.2d;%.2dH"       #  ('H' ou 'f') : Goto at (y,x), voir le code

DELAFCURSOR = "\x1B[K"             #  effacer après la position du curseur
CRLF  = "\r\n"                     #  Retour à la ligne

# Nov 2021
# Course Hippique (version élèves)
# VT100 : Actions sur le curseur
CURSON   = "\x1B[?25h"             #  Curseur visible
CURSOFF  = "\x1B[?25l"             #  Curseur invisible

# VT100 : Actions sur les caractères affichables
NORMAL = "\x1B[0m"                  #  Normal
BOLD = "\x1B[1m"                    #  Gras
UNDERLINE = "\x1B[4m"               #  Souligné


# VT100 : Couleurs : "22" pour normal intensity
CL_BLACK="\033[22;30m"                  #  Noir. NE PAS UTILISER. On verra rien !!
CL_RED="\033[22;31m"                    #  Rouge
CL_GREEN="\033[22;32m"                  #  Vert
CL_BROWN = "\033[22;33m"                #  Brun
CL_BLUE="\033[22;34m"                   #  Bleu
CL_MAGENTA="\033[22;35m"                #  Magenta
CL_CYAN="\033[22;36m"                   #  Cyan
CL_GRAY="\033[22;37m"                   #  Gris

# "01" pour quoi ? (bold ?)
CL_DARKGRAY="\033[01;30m"               #  Gris foncé
CL_LIGHTRED="\033[01;31m"               #  Rouge clair
CL_LIGHTGREEN="\033[01;32m"             #  Vert clair
CL_YELLOW="\033[01;33m"                 #  Jaune
CL_LIGHTBLU= "\033[01;34m"              #  Bleu clair
CL_LIGHTMAGENTA="\033[01;35m"           #  Magenta clair
CL_LIGHTCYAN="\033[01;36m"              #  Cyan clair
CL_WHITE="\033[01;37m"                  #  Blanc

#-------------------------------------------------------

import multiprocessing as mp
 
import os, time, math, random, sys, ctypes, numpy as np

# Constantes
NB_PROCESS=20
OFFSET = 5


# Variables partagées
leaderboard = mp.Array(ctypes.c_int, NB_PROCESS)
resultats = mp.Array(ctypes.c_int, NB_PROCESS)
finished = mp.Value('i', 0)
rang = mp.Value(ctypes.c_int, 1)
gagnant = ""
perdant = ""

#-------------------------------------------------------

# Une liste de couleurs à affecter aléatoirement aux chevaux
lyst_colors=[CL_WHITE, CL_RED, CL_GREEN, CL_BROWN , CL_BLUE, CL_MAGENTA, CL_CYAN, CL_GRAY,
             CL_DARKGRAY, CL_LIGHTRED, CL_LIGHTGREEN,  CL_LIGHTBLU, CL_YELLOW, CL_LIGHTMAGENTA, CL_LIGHTCYAN]

def effacer_ecran() : print(CLEARSCR,end='')
def erase_line_from_beg_to_curs() : print("\033[1K",end='')
def curseur_invisible() : print(CURSOFF,end='')
def curseur_visible() : print(CURSON,end='')
def move_to(lig, col) : print("\033[" + str(lig) + ";" + str(col) + "f",end='')

def en_couleur(Coul) : print(Coul,end='')
def en_rouge() : print(CL_RED,end='') # Un exemple !

# Referee
def arbitre(keep_running, leaderboard) :
    while keep_running.value :
        move_to(NB_PROCESS+OFFSET+2, 10)
        erase_line_from_beg_to_curs()
        en_couleur(CL_WHITE)

        if finished.value == NB_PROCESS :
            move_to(NB_PROCESS+OFFSET+5+NB_PROCESS, 0)
            keep_running.value = False
        else :
            print(f"Leader : {chr(ord('A') + np.argmax(leaderboard))} - Dernier : {chr(ord('A') + np.argmin(leaderboard))}")

        time.sleep(0.1)

# La tache d'un cheval
def un_cheval(ma_ligne : int, keep_running, leaderboard) : # ma_ligne commence à 0

    col=1

    while col < LONGUEUR_COURSE and keep_running.value :
        move_to(ma_ligne+1,col)         # pour effacer toute ma ligne
        erase_line_from_beg_to_curs()
        en_couleur(lyst_colors[ma_ligne%len(lyst_colors)])
        print(f"+|__{chr(ord('A')+ma_ligne)}__/{' '*(LONGUEUR_COURSE-col-1)}|")

        leaderboard[ma_ligne] = col

        col += 1
        time.sleep(0.1 * random.randint(1,5))

        if col == LONGUEUR_COURSE :
            finished.value += 1
            with resultats.get_lock():
                resultats[ma_ligne] = rang.value
                rang.value += 1
                move_to(ma_ligne + 1, LONGUEUR_COURSE+1 + 10)
                en_couleur(CL_WHITE)
                print(f"Finis ! {resultats[ma_ligne]}e")
                
# ---------------------------------------------------
# La partie principale :
if __name__ == "__main__" :

    LONGUEUR_COURSE = 10 # Tout le monde aura la même copie (donc no need to have a 'value')
    keep_running=mp.Value(ctypes.c_bool, True)
    lettres = [chr(ord('A')+i) for i in range(NB_PROCESS)]
    predicton = input(f"Entrer une lettre entre A et {lettres[-1]} : ")

    while predicton not in lettres :
        predicton = input(f"Erreur ! Entrer une lettre entre A et {lettres[-1]} : ")
     
    mes_process = [0 for i in range(NB_PROCESS)]

    effacer_ecran()
    curseur_invisible()

    # Referee that looks fot the horse in first place and the one in last place
    arbitre = mp.Process(target=arbitre, args=(keep_running, leaderboard))
    arbitre.start()

    for i in range(NB_PROCESS):  # Lancer Nb_process processus
        mes_process[i] = mp.Process(target=un_cheval, args= (i,keep_running, leaderboard))
        mes_process[i].start()

    for i in range(NB_PROCESS): mes_process[i].join()

    move_to(NB_PROCESS + OFFSET + 2, 1)
    print(CLEARELN)
    classement_final = [chr(ord('A') + i) for i in np.argsort(resultats)]
    print("Clasement : ")
    for i in range(NB_PROCESS):
        print(f"{i+1} : {classement_final[i]}")
    
    if classement_final[0] == predicton.upper() :
        print(f"Vous avez gagné ! Le gagnant est {classement_final[0]}")
    else :
        print(f"Vous avez perdu ! Le gagnant est : {classement_final[0]}")
    
    curseur_visible()
