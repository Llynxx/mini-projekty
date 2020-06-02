#include <iostream>
using namespace std;

template <typename mT>
class Point {
    template<typename mP>
	friend class PointManipulator;
	friend void mult(Point<int> *p, int z);
	mT x, y;

public:
	Point(mT aX, mT aY)
	{
	    this->x = aX;
	    this->y = aY;
	}

	void toString() {
        cout<<"Punkt x = "<<this->x<<", y = "<<this->y<<endl;
	}

	mT getX()
    {
        return this->x;
    }

    mT getY()
    {
        return this->y;
    }

    mT setX(mT nx)
    {
        this->x=nx;
    }

    mT setY(mT ny)
    {
        this->y=ny;
    }

    mT flip()
    {
		setX(-(this->x));
    	setY(-(this->y));
	}

	mT move(mT xw, mT yw)
	{
		setX((this->x)+xw);
		setY((this->y)+yw);
	}
};

template<typename mT>
class PointManipulator{
    Point<mT> *p;

public:

    Point<mT> createPoint(mT x, mT y)
    {
        this->p = new Point<mT>(x, y);
    }

    void superFlip(Point<int> *p2)
    {
        p2->move(-(p->x), -(p->y));
        p2->flip();
        p2->move(p->x, p->y);
    }

    Point<mT>* getPoint() {
        return p;
    }
};

void mult(Point<int> *p, int z)
{
    p->x*=z;
    p->y*=z;
}

int main() {
	Point<int> a(2, 2);
	Point<unsigned> b(8, 9);
	Point<float> c(3.3, 6.6);
	a.toString();
	b.toString();
	c.toString();
	/*a.flip();
	a.toString();
	mult(&a, 5);*/
	a.toString();
	PointManipulator<int> *pm = new PointManipulator<int>();
	pm->createPoint(1, 1);
	pm->superFlip(&a);
	a.toString();
	return 0;
}
