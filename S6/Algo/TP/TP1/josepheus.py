l = [i for i in range(0, 10)]

def josephus_survivor(l, k):
    n = len(l)
    i = 0
    while n > 1:
        i = (i + k - 1) % n 
        print(l, l[i])
        l.pop(i)
        n -= 1
    return l[0]

print(josephus_survivor(l, 3))
"""
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9] 2
[0, 1, 3, 4, 5, 6, 7, 8, 9] 5
[0, 1, 3, 4, 6, 7, 8, 9] 8   
[0, 1, 3, 4, 6, 7, 9] 1      
[0, 3, 4, 6, 7, 9] 6
[0, 3, 4, 7, 9] 0
[3, 4, 7, 9] 7
[3, 4, 9] 4
[3, 9] 9
3 <- Survivant
"""

l = [i for i in range(0, 10)]

print(josephus_survivor(l, 8))
"""
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9] 7
[0, 1, 2, 3, 4, 5, 6, 8, 9] 5
[0, 1, 2, 3, 4, 6, 8, 9] 4
[0, 1, 2, 3, 6, 8, 9] 6
[0, 1, 2, 3, 8, 9] 9
[0, 1, 2, 3, 8] 2
[0, 1, 3, 8] 1
[0, 3, 8] 8
[0, 3] 3
0 <- Survivant
"""