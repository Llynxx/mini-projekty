#include <iostream>

using namespace std;


class Instrument
{
    public:
    virtual void wydajDzwiek()
    {
        cout<<"sound of silence"<<endl;
    }
};

class Werbel:public Instrument
{
    public:
    void wydajDzwiek()
    {
        cout<<"werb werb"<<endl;
    }
};
class Trabka:public Instrument
{
    public:
    void wydajDzwiek()
    {
        cout<<"trut trut"<<endl;
    }
};
class Fortepian:public Instrument
{
    public:
    void wydajDzwiek()
    {
        cout<<"fort fort"<<endl;
    }
};

void muzyk(Instrument &powierzonyInstrument)
{
    cout<<"muzykant:";
    powierzonyInstrument.wydajDzwiek();
}

int main()
{
    Instrument obiekt;
    Werbel a;
    Trabka b;
    Fortepian c;
    a.wydajDzwiek();
    b.wydajDzwiek();
    c.wydajDzwiek();
    Instrument *wsk = &a;
    wsk->wydajDzwiek();
    wsk=&b;
    wsk->wydajDzwiek();
    wsk=&c;
    wsk->wydajDzwiek();
    muzyk(a);
    muzyk(b);
    muzyk(c);

    return 0;
}
