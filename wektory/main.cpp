#include <iostream>

using namespace std;

class Vector
{
public:
    int x;
    int y;
    Vector()
    {
        this->x = 0;
        this->y = 0;
    }
    Vector(int a, int b)
    {
        this->x = a;
        this->y = b;
    }
    Vector operator +(const Vector &v)
    {
        return Vector(this->x + v.x, this->y + v.y);
    }

    Vector &operator +=(const Vector &v)
    {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    Vector operator -(const Vector &v)
    {
        return Vector(this->x - v.x, this->y - v.y);
    }

    Vector &operator -=(const Vector &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    Vector operator *(const double &d)
    {
        Vector ret;
        ret.x = this->x * d;
        ret.y = this->y * d;
        return ret;
    }

    Vector &operator *=(const double &d)
    {
        this->x *= d;
        this->y *= d;
        return *this;
    }

    Vector operator !()
    {
        return Vector(this->x *= -1, this->y *= -1);
    }

    void tostring()
    {
        cout<<endl<<"x = "<<this->x<<" y = "<<this->y;
    }
};





int main()
{
    Vector a(1, 5), b(6, 7), c;
    c = a+b;
    c.tostring();
    !c;
    c.tostring();
    return 0;
}
