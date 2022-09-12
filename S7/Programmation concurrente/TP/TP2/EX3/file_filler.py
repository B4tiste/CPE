import os
import random

alpha = "abcdefghijklmnopqrstuvwxyz"

for i in range(20):
    u = ""
    for i in range(25, 60):
        u += random.choice(alpha)
    os.system(f"echo {u} >> test.txt ")
