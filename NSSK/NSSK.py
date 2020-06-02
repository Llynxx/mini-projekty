import sage.all
from random import seed
from random import randint
from crypto.block_cipher.sdes import SimplifiedDES
from crypto.block_cipher.miniaes import MiniAES

def generate_nonce(seedd):
    seed(seedd)
    return randint(10^3,10^5)

def bin_to_list(x):
    lista=[]
    for i in range (len(x)):
        lista.append(int(x[i:i+1]))
    return lista

def list_to_bin(x):
    liczba=''
    for i in range (len(x)):
        liczba=liczba+str(x[i])
    return liczba

def int_to_bin(x):
    liczba=''
    while x>=1:
        liczba=str(int(x)%2)+liczba
        x=int(x)/2
    return liczba

def gen_rsa_key():
    p = random_prime(10^2,10^3)
    q = random_prime(10^2,10^3)
    while p == q:
        q=random_prime(10^3,10^4)
    n=p*q
    phi=euler_phi(n)
    e = ZZ.random_element(phi)
    while (gcd(e, phi) != 1) or len(str(e))>=4 :
        e = ZZ.random_element(phi)
    return e

class NSSK(object):
    def __init__(self, modul, baza, private_key):
        self.modul = modul
        self.baza = baza
        self.private_key = private_key
        self.part_key = None
        self.full_key = None
        self.IdA=None
        self.IdB=None
        self.Na=None
        self.Nb=None
        self.wiadomosc = None
        self.odebrane = None
        self.odszyfrowane = None
        self.Ka=None
        self.Kb=None
        self.Kab=None
        self.error = 0

    def generate_part_key(self):
        part_key = self.baza**self.private_key
        part_key = part_key%self.modul
        self.part_key = part_key

    def generate_full_key(self, part_key_r):
        full_key = part_key_r**self.private_key
        full_key = full_key%self.modul
        zmienna=int_to_bin(full_key)
        if(len(zmienna)<16):
            for i in range (0,16-len(zmienna)):
                zmienna='0'+zmienna
        return zmienna
    
    def nawiazanie_komunikacji(self, S):
        S.odebrane = str(self.IdA)+","+str(self.IdB)+","+str(self.Na)
    
    def generowanie_klucza(self):
        self.odebrane = self.odebrane.split(',')
        self.IdA = self.odebrane[0]
        self.IdB = self.odebrane[1]
        self.Na = self.odebrane[2]
        self.Kab =  gen_rsa_key()
    def S_szyfrowanie(self,A):
        self.wiadomosc = str(self.IdA)+','+str(self.Kab)
        while len(self.wiadomosc)%2 !=0:
            self.wiadomosc='0'+self.wiadomosc
        maes = MiniAES()
        bin = BinaryStrings()
        key = bin(self.Kb)
        P = bin.encoding(self.wiadomosc)
        czesciowa = maes(P, key, algorithm="encrypt")
        self.wiadomosc = str(self.IdB)+','+str(self.Kab)+','+str(self.Na)+','+str(czesciowa)
        while len(self.wiadomosc)%2 !=0:
            self.wiadomosc='0'+self.wiadomosc
        key = bin(self.Ka)
        P = bin.encoding(self.wiadomosc)
        C = maes(P, key, algorithm="encrypt")
        A.odebrane = C

    def A_otrzymanie_i_wyslanie(self,B):
        maes = MiniAES()
        bin = BinaryStrings()
        key = bin(self.Ka)
        plaintxt = maes(self.odebrane, key, algorithm="decrypt")
        self.odszyfrowane = plaintxt.decoding()
        self.odszyfrowane = self.odszyfrowane.split(',')
        self.IdB = int(str(self.odszyfrowane[0]))
        self.Kab = int(str(self.odszyfrowane[1]))
        if(str(self.Na) != self.odszyfrowane[2]):
            print ("Wartosc Na jest rozna")
            self.error=self.error+1
        self.wiadomosc = self.odszyfrowane[3]
        B.odebrane = self.wiadomosc

    def B_odszyfrowanie_i_wyslanie(self,A):
        maes = MiniAES()
        bin = BinaryStrings()
        key = bin(self.Kb)
        plaintxt = maes(bin(self.odebrane), key, algorithm="decrypt")
        self.odszyfrowane = plaintxt.decoding()
        self.odszyfrowane = self.odszyfrowane.split(',')
        self.IdA = int(str(self.odszyfrowane[0]))
        self.Kab = int(str(self.odszyfrowane[1]))
        key=int_to_bin(self.Kab)
        if(len(key)<16):
            for i in range (0,16-len(key)):
                key='0'+key
        keyy = bin(key)
        self.wiadomosc = str(self.Nb)
        while len(self.wiadomosc)%2 !=0:
            self.wiadomosc='0'+self.wiadomosc
        P = bin.encoding(self.wiadomosc)
        self.wiadomosc = maes(P, keyy, algorithm="encrypt")
        A.odebrane = self.wiadomosc
    
    def A_operacja_na_Nb(self,B):
        maes = MiniAES()
        bin = BinaryStrings()
        key=int_to_bin(self.Kab)
        if(len(key)<16):
            for i in range (0,16-len(key)):
                key='0'+key
        keyy = bin(key)
        plaintxt = maes(bin(self.odebrane), keyy, algorithm="decrypt")
        self.odszyfrowane = plaintxt.decoding()
        self.Nb = int(self.odszyfrowane)
        self.wiadomosc = self.Nb-1
        self.wiadomosc = str(self.wiadomosc)
        while len(self.wiadomosc)%2 !=0:
            self.wiadomosc='0'+self.wiadomosc
        P = bin.encoding(self.wiadomosc)
        self.wiadomosc = maes(P, keyy, algorithm="encrypt")
        B.odebrane = self.wiadomosc
    
    def B_weryfikacja(self):
        maes = MiniAES()
        bin = BinaryStrings()
        key=int_to_bin(self.Kab)
        if(len(key)<16):
            for i in range (0,16-len(key)):
                key='0'+key
        keyy = bin(key)
        plaintxt = maes(bin(self.odebrane), keyy, algorithm="decrypt")
        self.odszyfrowane = int(plaintxt.decoding())

modul = random_prime(10^3,10^5)
baza=mod(primitive_root(modul),modul)
print ("Modul i baza: "),modul,baza
a_prywatne = randint(1,modul)
b_prywatne = randint(1,modul)
s_prywatne = randint(1,modul)

Alice = NSSK(modul,baza,a_prywatne)
Bob = NSSK(modul,baza, b_prywatne)
Serwer=NSSK(modul,baza,s_prywatne)

Alice.Na=generate_nonce(randint(0,1000))
Bob.Nb=generate_nonce(randint(0,1000))

Alice.IdA=randint(0,255)
Bob.IdB=randint(0,255)
while Alice.IdA == Bob.IdB:
    Bob.IdB=randint(0,255)
Alice.IdB=Bob.IdB
print ("IDA: "),Alice.IdA
print ("IDB: "),Bob.IdB

Alice.generate_part_key()
Bob.generate_part_key()
Serwer.generate_part_key()

Alice.Ka=Alice.generate_full_key(Serwer.part_key)
Bob.Kb=Bob.generate_full_key(Serwer.part_key)
Serwer.Ka=Serwer.generate_full_key(Alice.part_key)
Serwer.Kb=Serwer.generate_full_key(Bob.part_key)
print ("Alice Ka: "),Alice.Ka
print ("Serwer Ka: "),Serwer.Ka
print ("Bob Kb: "),Bob.Kb
print ("Serwer Kb: "),Serwer.Kb
print ("Alice Na: "),Alice.Na
print ("Bob Nb: "),Bob.Nb

Alice.nawiazanie_komunikacji(Serwer)
print ("Serwer odebral chec komuniacji: "),Serwer.odebrane
Serwer.generowanie_klucza()
print ("Serwer wygenerowal klucz")
print ("Serwer: IdA: "),Serwer.IdA, (" IdB: "), Serwer.IdB,(" Na: "), Serwer.Na, ("Kab: "), Serwer.Kab
print ("Serwer wyslal wiadomosc do Alice")
Serwer.S_szyfrowanie(Alice)
Alice.A_otrzymanie_i_wyslanie(Bob)
if(Alice.error == 1):
    print ("otrzymana wartosc Na rozni sie od wyslanej")
else:
    print ("Alice odebrala: IdB:"),Alice.IdB,("Kab: "), Alice.Kab,("Na: "),Alice.Na,(" zaszyfrowany klucz dla B: "),Alice.wiadomosc
    print ("Alice wyslala kopie klucza do Boba")
    print ("Bob odebral wiadomosc: "), Bob.odebrane
    Bob.B_odszyfrowanie_i_wyslanie(Alice)
    print ("Bob odszyfrowal: IdA:"),Bob.IdA,("Kab:"),Bob.Kab
    print ("Bob wyslal zaszyfrowane Nb do Alice")
    print ("Alice otrzymala: "),Alice.odebrane
    Alice.A_operacja_na_Nb(Bob)
    print ("Alice odszyfrowala Nb="),Alice.Nb
    print ("Alice wyslala Nb po wykonanej operacji do Boba")
    Bob.odebrane
    Bob.B_weryfikacja()
    print ("Bob otrzymal:"),Bob.odszyfrowane
    print ("Czy otrzymana wiadomosc rowna sie Nb-1?"),Bob.odszyfrowane==Bob.Nb-1