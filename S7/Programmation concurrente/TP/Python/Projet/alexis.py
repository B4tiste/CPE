import multiprocessing as mp
import numpy as np
import signal
import os
import time
import math
import random
import sys
import ctypes
GRID_W = 20
GRID_H = 20


# Quelques codes d'échappement (tous ne sont pas utilisés)
CLEARSCR = "\x1B[2J\x1B[;H"  # Clear SCReen
CLEAREOS = "\x1B[J"  # Clear End Of Screen
CLEARELN = "\x1B[2K"  # Clear Entire LiNe
CLEARCUP = "\x1B[1J"  # Clear Curseur UP
GOTOYX = "\x1B[%.2d;%.2dH"  # ('H' ou 'f') : Goto at (y,x), voir le code

DELAFCURSOR = "\x1B[K"  # effacer après la position du curseur
CRLF = "\r\n"  # Retour à la ligne

# Nov 2021
# Course Hippique (version élèves)
# VT100 : Actions sur le curseur
CURSON = "\x1B[?25h"  # Curseur visible
CURSOFF = "\x1B[?25l"  # Curseur invisible

# VT100 : Actions sur les caractères affichables
NORMAL = "\x1B[0m"  # Normal
BOLD = "\x1B[1m"  # Gras
UNDERLINE = "\x1B[4m"  # Souligné


# VT100 : Couleurs : "22" pour normal intensity
CL_BLACK = "\033[22;30m"  # Noir. NE PAS UTILISER. On verra rien !!
CL_RED = "\033[22;31m"  # Rouge
CL_GREEN = "\033[22;32m"  # Vert
CL_BROWN = "\033[22;33m"  # Brun
CL_BLUE = "\033[22;34m"  # Bleu
CL_MAGENTA = "\033[22;35m"  # Magenta
CL_CYAN = "\033[22;36m"  # Cyan
CL_GRAY = "\033[22;37m"  # Gris

# "01" pour quoi ? (bold ?)
CL_DARKGRAY = "\033[01;30m"  # Gris foncé
CL_LIGHTRED = "\033[01;31m"  # Rouge clair
CL_LIGHTGREEN = "\033[01;32m"  # Vert clair
CL_YELLOW = "\033[01;33m"  # Jaune
CL_LIGHTBLU = "\033[01;34m"  # Bleu clair
CL_LIGHTMAGENTA = "\033[01;35m"  # Magenta clair
CL_LIGHTCYAN = "\033[01;36m"  # Cyan clair
CL_WHITE = "\033[01;37m"  # Blanc


def effacer_ecran(): print(CLEARSCR, end='')
def erase_line_from_beg_to_curs(): print("\033[1K", end='')
def curseur_invisible(): print(CURSOFF, end='')
def curseur_visible(): print(CURSON, end='')
def move_to(lig, col): print("\033[" + str(lig) + ";" + str(col) + "f", end='')


def neighbors(X, row_number, column_number):
    return [[X[i][j] if i >= 0 and i < len(X) and j >= 0 and j < len(X[0]) else 0
             for j in range(column_number-1, column_number+2)]
            for i in range(row_number-1, row_number+2)]


def lifeStep(X, x, y):
    return np.sum(X[x-1:x+2, y-1:y+2]) - X[x, y]


isRunning = mp.Value(ctypes.c_bool, True)


def handler(signum, frame):
    isRunning.value = False
    exit(0)


def a_life(x, TickSem, UnTickSem, UiSem, isRunning, state1, state2):
    s1 = np.frombuffer(state1.get_obj(), ctypes.c_int)
    arr1 = s1.reshape((GRID_W, GRID_H))

    s2 = np.frombuffer(state2.get_obj(), ctypes.c_int)
    arr2 = s2.reshape((GRID_W, GRID_H))
    UnTickSem.release()

    while (isRunning.value):
        TickSem[x].acquire()

        for y in range(GRID_W):

            bit = arr1[y][x]

            nbn = lifeStep(arr1, y, x)

            arr2[y][x] = arr1[y][x]
            if arr1[y][x] == 1:
                if (nbn < 2) or (nbn > 3):
                    arr2[y][x] = 0
            else:
                if nbn == 3:
                    arr2[y][x] = 1
            bit = arr2[y][x]

            UiSem.acquire()
            move_to(y+1, x*2+1)
            # print('█' if bit else ' ')
            print('X' if bit else f"  ")

            s1 = f"{CL_RED}{nbn}{CL_GRAY}"
            s2 = f"{CL_BLUE}{nbn}{CL_GRAY}"
            UiSem.release()
    return


def addGlider(x, y, a):
    """adds a glider with top left cell at (i, j)"""
    glider = np.array([[0,   0, 1],
                       [1,  0, 1],
                       [0,  1, 1]])
    a[x:x+3, y:y+3] = glider


def addStatic1(x, y, a):
    static = np.array([[0, 1, 0],
                       [0, 1, 0],
                       [0, 1, 0]])
    a[x:x+3, y:y+3] = static


if __name__ == "__main__":

    signal.signal(signal.SIGINT, handler)

    state1 = mp.Array(ctypes.c_int, GRID_H*GRID_W)
    state2 = mp.Array(ctypes.c_int, GRID_H*GRID_W)
    s1 = np.frombuffer(state1.get_obj(), ctypes.c_int)
    a1 = s1.reshape((GRID_W, GRID_H))
    s2 = np.frombuffer(state2.get_obj(), ctypes.c_int)
    # for i in range(GRID_H*GRID_W):
    #     grid[i] = i

    print(a1)

    addGlider(2, 1, a1)
    addStatic1(10, 10, a1)

    print(a1)

    process = [0 for y in range(GRID_H)]
    # TickSem = mp.Semaphore(0)
    TickSem = [mp.Semaphore(0) for x in range(GRID_H)]
    UnTickSem = mp.Semaphore(0)
    UiSem = mp.Semaphore(1)

    effacer_ecran()
    curseur_invisible()

    UiSem.acquire()
    move_to(GRID_H+2, 1)
    print("Loading...")
    UiSem.release()
    for x in range(0, GRID_H):
        process[x] = mp.Process(target=a_life, args=(
            x, TickSem, UnTickSem, UiSem, isRunning, state1, state2))
        process[x].start()
    UiSem.acquire()
    move_to(GRID_H+2, 1)
    print("Waiting...")
    UiSem.release()
    for i in range(GRID_H):
        UnTickSem.acquire()
        move_to(GRID_H+2, 1)
        print(f"Waiting... ({i+1}/{GRID_H})")
    UiSem.acquire()
    move_to(GRID_H+2, 1)
    print("Go !                      ")
    UiSem.release()
    while (isRunning.value):
        for x in range(0, GRID_H):
            TickSem[x].release()

        time.sleep(0.05)

        # Copy nextstate to the current state

        for i in range(GRID_H*GRID_W):
            s1[i] = s2[i]
    for x in range(0, GRID_H):
        process[x].kill()
    print("Fini")
