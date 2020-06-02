#include <iostream>

using namespace std;

class Date
{
    int day;
    int month;
    int year;
    public:
    Date()
    {
        this -> day = 0;
        this -> month = 0;
        this -> year = 0;
    }
    Date(int d, int m, int y)
    {
        if((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && (d<32 && d>0))
        {
            this -> day = d;
            this -> month = m;
            this -> year = y;
        }
        else if((m == 4 || m == 6 || m == 9 || m == 11) && (d<31 && d>0))
        {
            this -> day = d;
            this -> month = m;
            this -> year = y;
        }
        else if((m == 2) && (d<29 && d>0))
        {
            this -> day = d;
            this -> month = m;
            this -> year = y;
        }
        else
        {
            this -> day = 0;
            this -> month = 0;
            this -> year = 0;
        }
    }
    void tostring()
    {
        cout<<this->day<<"."<<this->month<<"."<<this->year<<endl;
    }

    operator +(const int &d)
    {
        for(int j = 0; j < d; j++)
        {
            (this->day)++;
            if(this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7 || this->month == 8 || this->month == 10 || this->month == 12)
            {
                if(this->day == 32)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
            if(this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11)
            {
                if(this->day == 31)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
            if(this->month == 2)
            {
                if(this->day == 29)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
        }
    }

    operator +=(const int &d)
    {
        for(int j = 0; j < d; j++)
        {
            (this->day)++;
            if(this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7 || this->month == 8 || this->month == 10 || this->month == 12)
            {
                if(this->day == 32)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
            if(this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11)
            {
                if(this->day == 31)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
            if(this->month == 2)
            {
                if(this->day == 29)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
        }
    }

    operator +(const Date &d)
    {
        this->year += d.year;
        for(int j = 0; j < d.month; j++)
        {
            (this->month)++;
            if(this->month>12)
            {
                (this->year)++;
                this->month = 1;
            }
        }
        for(int j = 0; j < d.day; j++)
        {
            (this->day)++;
            if(this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7 || this->month == 8 || this->month == 10 || this->month == 12)
            {
                if(this->day == 32)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
            if(this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11)
            {
                if(this->day == 31)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
            if(this->month == 2)
            {
                if(this->day == 29)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
        }
    }
    operator +=(const Date &d)
    {
        this->year += d.year;
        for(int j = 0; j < d.month; j++)
        {
            (this->month)++;
            if(this->month>12)
            {
                (this->year)++;
                this->month = 1;
            }
        }
        for(int j = 0; j < d.day; j++)
        {
            (this->day)++;
            if(this->month == 1 || this->month == 3 || this->month == 5 || this->month == 7 || this->month == 8 || this->month == 10 || this->month == 12)
            {
                if(this->day == 32)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
            if(this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11)
            {
                if(this->day == 31)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
            if(this->month == 2)
            {
                if(this->day == 29)
                {
                    month++;
                    this->day = 1;
                    if(month == 13)
                    {
                        this->month = 1;
                        this->year++;
                    }
                }
            }
        }
    }
    friend ostream& operator<<(ostream&, const Date&);
};

ostream& operator<<(ostream& str, const Date& d)
{
    return str<<d.day<<"."<<d.month<<"."<<d.year<<endl;
}

int main()
{
    Date a(31, 4, 2019);
    Date b(12, 10, 24);
    Date c(31, 4, 12);
    Date d(1, 1, 2019);
    a+=100;
    cout<<a;
    return 0;
}
