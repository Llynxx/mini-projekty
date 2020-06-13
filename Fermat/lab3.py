import math
import random

def dlp_shanks(g, h, p):
    m = int(math.ceil(math.sqrt(p-1)))
    jaj={}
    
    for j in range (0, int(m)):
        jaj[j]=(g**j)%p
    
    a=(g**(p-m-1))%p
    d = h
    
    for i in range (0, int(m)):
        if(d in jaj.values()):
            return (i*m + jaj.keys()[jaj.values().index(d)] )
        d = (d * a)%p

    return None

try:
    g=int(input('g:'))
except ValueError:
    print ("Not a number")
try:
    h=int(input('h:'))
except ValueError:
    print ("Not a number")
try:
    p=int(input('p:'))
except ValueError:
    print ("Not a number")

x = dlp_shanks(g, h, p)
print x
