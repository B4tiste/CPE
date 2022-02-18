
# TP 2

# Ex 1 : Dénombrer le nombre d'instructions d'un programme

n = 128

# 1.

test = 0

for i in range(n):  # n iterations
    test += 1

for j in range(n):  # n iterations
    test -= 1

# Nombre total d'instructions : 2*n
# Complexité : O(n)

# 2.

test = 0
for i in range(n):  # n iterations
    for j in range(n):  # n iterations
        test = test + i + j

# Nombre total d'instructions : n*n
# Complexité : O(n²)

# 3.

a = 5
b = 6
c = 10
for i in range(n):  # n iterations
    for j in range(n):  # n iterations
        x = i * i
        y = j * j
        z = i * j

for k in range(n):  # n iterations

    w = a*k + 45

    v = b*b

# Nombre total d'instructions : (n*n)+n
# Complexité : O(n²)

# 4.

i = n
cpt = 0

while i > 0: 
    cpt += 1
    k = 2 + 2
    i = i // 2

# Complexité : O(log(n))

# 5. 

sum = 0
for i in range(1, (n*n)+1): # n²
    for j in range(1, i+1): # n²
        for k in range(1, 7):
            sum += 1
print(sum)

# Complexité : O(n^4)

