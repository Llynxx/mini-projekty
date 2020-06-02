#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>

using namespace std;

class Zawodnik
{
    int id;
    string imie;
    string nazwisko;
    string nr_rej;
    string nr_pr_j;
    int czas;
public:

    Zawodnik(string imie, string nazwisko, int id)
    {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->id = id;
        nr_rej = "AAAAAAAA";
        this->nr_rej[0] = rand()%25+65;
        this->nr_rej[1] = rand()%25+65;
        this->nr_rej[2] = rand()%10+48;
        this->nr_rej[3] = rand()%10+48;
        this->nr_rej[4] = rand()%10+48;
        this->nr_rej[5] = rand()%10+48;
        this->nr_rej[6] = rand()%10+48;
        this->nr_rej[7] = rand()%10+48;
        this->nr_pr_j = "AAAAAAAA";
        this->nr_pr_j[0] = rand()%25+65;
        this->nr_pr_j[1] = rand()%25+65;
        this->nr_pr_j[2] = rand()%25+65;
        this->nr_pr_j[3] = rand()%10+48;
        this->nr_pr_j[4] = rand()%10+48;
        this->nr_pr_j[5] = rand()%10+48;
        this->nr_pr_j[6] = rand()%10+48;
        this->nr_pr_j[7] = rand()%10+48;
    }
    friend bool comparator();
    void start()
    {
        this->czas = rand()%60+75;
    }

    int jakiczas()
    {
        return this->czas;
    }

    void tostring()
    {
        cout<<"IMIE: "<<this->imie<<endl<<"NAZWISKO: "<<this->nazwisko<<endl<<"ID: "<<this->id<<endl<<"NR_REJ: "<<this->nr_rej<<endl<<"NR_PR_J: "<<this->nr_pr_j<<endl<<endl;
    }

    void tostringwithtime()
    {
        cout<<"IMIE: "<<this->imie<<endl<<"NAZWISKO: "<<this->nazwisko<<endl<<"ID: "<<this->id<<endl<<"Czas: "<<this->czas<<" sekund"<<endl<<endl;
    }
};

bool comparator(Zawodnik& lhs, Zawodnik& rhs)
{
    return (lhs.jakiczas() < rhs.jakiczas());
}

int main()
{
    srand((unsigned)time(NULL));
    fstream imiona;
    fstream nazwiska;
    imiona.open("imie.txt", ios::in);
    nazwiska.open("nazwisko.txt", ios::in);

    int c;
    vector<string>imie;
    vector<string>nazwisko;
    string pom;
    int i, j;
    int curr_id = 1;
    getline(imiona, pom);
    getline(nazwiska, pom);
    while(!imiona.eof())
        {
            getline(imiona, pom);
            imie.push_back(pom);
        }
    while(!nazwiska.eof())
        {
            getline(nazwiska, pom);
            nazwisko.push_back(pom);
        }
    queue<Zawodnik>zawodnicy;
    vector<Zawodnik>generalka;
    queue<Zawodnik>kopia;
    int out = 1;
    int ktory;
    while(out!=0)
    {
        cout<<"1 - dodaj zawodnika"<<endl<<"2 - start zawodnika"<<endl<<"3 - wycofaj zawodnika"<<endl<<"4 - wyswietl liste"<<endl<<"5 - policz liste"<<endl<<"9 - zakoncz"<<endl<<"----"<<endl;
        cin>>c;
        cout<<endl<<endl;
        switch(c)
        {
        case 1:
            {
                i = rand()%(imie.size());
                j = rand()%(nazwisko.size());
                Zawodnik nowy(imie[i], nazwisko[j], curr_id);
                curr_id++;
                zawodnicy.push(nowy);
                break;
            }
        case 2:
            {
                while(!zawodnicy.empty())
                    {
                        zawodnicy.front().start();
                        generalka.push_back(zawodnicy.front());
                        zawodnicy.pop();
                    }
                break;
            }
        case 3:
            {
                zawodnicy.pop();
                break;
            }
        case 4:
            {
                kopia = zawodnicy;
                while(!kopia.empty())
                    {
                        kopia.front().tostring();
                        kopia.pop();
                    }
                break;
            }
        case 5:
            {
                cout<<"Rozmiar listy startowej: "<<zawodnicy.size()<<endl<<endl;
                break;
            }
        case 9:
            {
                out = 0;
                break;
            }
        default:
            {
                out = 1;
            }
        }
    }
    sort(generalka.begin(), generalka.end(), &comparator);
    for(int j = 0; j<generalka.size(); j++)
    {
        generalka[j].tostringwithtime();
    }
    return 0;
}
