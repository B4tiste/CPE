import time
import os
import random
import math

import multiprocessing as mp
import numpy as np

GRID_SIZE = 10

def clear() :
    os.system('cls' if os.name == 'nt' else 'clear')

# 1 : 
def init_grid() :
    grid = np.random.randint(2, size=(GRID_SIZE, GRID_SIZE))
    return grid

# 2 :
def update_grid(grid) :
    new_grid = np.zeros((GRID_SIZE, GRID_SIZE))
    for x in range(GRID_SIZE) :
        for y in range(GRID_SIZE) :
            # Check if the current cell is outside of the grid bounds
            if x < 0 or x >= GRID_SIZE or y < 0 or y >= GRID_SIZE :
                continue

            live_neighbors = 0
            for i in range(-1, 2) :
                for j in range(-1, 2) :
                    if i == 0 and j == 0 :
                        continue
                    elif x + i < 0 or x + i >= GRID_SIZE or y + j < 0 or y + j >= GRID_SIZE :
                        continue
                    elif grid[x + i][y + j] == 1 :
                        live_neighbors += 1
            if grid[x][y] == 1 :
                if live_neighbors == 2 or live_neighbors == 3 :
                    new_grid[x][y] = 1
            else :
                if live_neighbors == 3 :
                    new_grid[x][y] = 1
    return new_grid


# 3 :
def update_grid_parallel(grid) :
    pool = mp.Pool(5)
    new_grid = pool.map(update_grid, np.array_split(grid, 5))
    pool.close()
    return np.concatenate(new_grid)

# 4 :
def display_grid(grid) :
    for x in range(GRID_SIZE) :
        for y in range(GRID_SIZE) :
            if grid[x][y] == 1 :
                print('X', end='')
            else :
                print(' ', end='')
        print()

def main() :
    grid = init_grid()
    while True :
        clear()
        display_grid(grid)
        grid = update_grid_parallel(grid)
        time.sleep(0.5)

if __name__ == '__main__' :
    main()
