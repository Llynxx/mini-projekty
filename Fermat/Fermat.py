import math
import random


def gen_fermat(s, x):
    p = 1
    q = 1
    n = 0
    while n<=0 or is_prime(n) or n%2==0:
        n=random.getrandbits(s)
    j = 1
    while j<n:
        if is_prime(j):
            p = math.floor(n/j)
            if is_prime(math.floor(n/p)):
                q = math.floor(n/p)
                if(math.fabs(p-q)<=x):
                    break
        j = j + 1
    tab = []
    tab.append(int(p*q))
    tab.append(int(p))
    tab.append(int(q))
    return tab

def fact_fermat(n):
    a, b = gen_a(n)
    print(a, b)
    p = a - b
    q = a + b
    tab = []
    tab.append(q)
    tab.append(p)
    print (tab)
    

def gen_a(n):
    a=math.ceil(math.sqrt(n))
    b_2 = (a*a)-n
    if not(square(b_2)):
        a = a + 1
        b_2 = a*a - n
    while not(square(b_2)):
        a = a + 1
        b_2 = a*a - n
    return a, int(math.sqrt(b_2))


def square(n):
    root = math.sqrt(n)
    if int(root + 0.5) ** 2 == n:
        return True
    else:
        return False

def is_prime(n):
  if n == 2 or n == 3: return True
  if n < 2 or n%2 == 0: return False
  if n < 9: return True
  if n%3 == 0: return False
  r = int(n**0.5)
  f = 5
  while f <= r:
    if n % f == 0: return False
    if n % (f+2) == 0: return False
    f += 6
  return True   



try:
    s=int(input('podaj size:'))
except ValueError:
    print ("Not a number")
try:
    x = int(input('podaj x:'))
except ValueError:
    print ("Not a number")

print(gen_fermat(s,x))
try:
    n=int(input('podaj liczbe:'))
except ValueError:
    print ("Not a number")
fact_fermat(n)
