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
 
import os, time,math, random, sys, ctypes

#-------------------------------------------------------

NB_PROCESS = 6
OFFSET = 5

tubes = []

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


# La tache d'un cheval
def un_cheval(ma_ligne : int, keep_running, pos) :
    col=1

    while col < LONGEUR_COURSE and keep_running.value :
        move_to(ma_ligne+1,col)         # pour effacer toute ma ligne
        erase_line_from_beg_to_curs()
        en_couleur(lyst_colors[ma_ligne%len(lyst_colors)])
        print('('+chr(ord('A')+ma_ligne)+'>')
        
        # Ecrire la position du cheval dans la liste partagée
        # pos[ma_ligne] = col

        col+=1
        time.sleep(0.1 * random.randint(1,5))

        
def arbitre(keep_running, pos) :
    while keep_running:
        move_to(NB_PROCESS+2,1)
        erase_line_from_beg_to_curs()

        for i in range(2):
            print(pos[i], end=' ')

        time.sleep(0.5)


# ---------------------------------------------------
# La partie principale :
if __name__ == "__main__" :
                 
    LONGEUR_COURSE = 10
    keep_running=mp.Value(ctypes.c_bool, True)
    pos = mp.Array('i', 5) # Tableau de NB_PROCESS entiers
    for i in range(5) :
        pos[i] = -1
     
    mes_process = [0 for i in range(NB_PROCESS)]
    
    effacer_ecran()
    curseur_invisible()

    for i in range(NB_PROCESS):  # Lancer   Nb_process  processus
        mes_process[i] = mp.Process(target=un_cheval, args= (i, keep_running, pos))
        mes_process[i].start()
    
    mes_process[-1] = mp.Process(target=arbitre, args= (keep_running, pos))
    mes_process[-1].start()

    move_to(NB_PROCESS + OFFSET, 1)
    print("Course lancée")

    for i in range(NB_PROCESS):
        mes_process[i].join()    

    move_to(NB_PROCESS + OFFSET, 1)
    curseur_visible()
    print("Course terminée")