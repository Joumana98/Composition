#include <iostream>

using namespace std;

const double PI = 3.14;

class pointType
{
public:
	// constructors
	pointType();
	pointType(int, int);

	// accessors
	void print() const;
	int getX() const;
	int getY();

	//mutators
	void setCoordinates(int, int);

private:
	int x;
	int y;
};

class circleType
{
public:
	// throw errors
	class Invalid {};

	// constructors
	circleType();
	circleType(int, int, double);
	circleType(const pointType&, double);

	// accessors
	void printInfo() const;
	double getRadius() const;
	double circumference() const;
	double area() const;

	//mutators
	void setInfo(int, int, double);

private:
	pointType center;
	double radius;
};

class cylinderType
{
public:
	// throw error
	class Invalid {};

	//constructors
	cylinderType();
	cylinderType(int, int, double, double);
	cylinderType(const circleType&, double);

	//accessors
	double volume() const;
	double area() const;


	//mutators
	void setHeight(double h);
	void setInfo(int c1, int c2, double r, double h);

private:
	circleType base;
	double height;
};

//-----------------------------------------------------------------------------------------------------------

int main()
try {
	pointType p1{ 1,1 };
	pointType p2{ 2,4 };
	p1.print();
	cout << endl;
	p2.print();
	cout << endl;

	cout << endl;
	circleType c1{ p1,2 };
	circleType c2{ p2,1 };
	c1.printInfo();
	cout << "Circumference of c2: " << c2.circumference() << endl;
	cout << "Area of c2: " << c2.area() << endl;

	cout << endl;
	cylinderType d1{ c1,3 };
	cout << "Surface area of the cylinder is: " << d1.area() << endl;
	cout << "Volume of the cylinder:" << d1.volume() << endl;

	return 0;
}
catch (circleType::Invalid)
{
	cerr << "Invalid radius value";
	return 1;
}
catch (cylinderType::Invalid)
{
	cerr << "Invalid cylinder height value";
	return 1;
}

//----------------------------------------------------------------------------------------------------------

pointType::pointType() : x{ 0 }, y{ 0 }
{

}
pointType::pointType(int c1, int c2) : x{ c1 }, y{ c2 }
{

}

void pointType::print() const
{
	cout << "(" << x << "," << y << ")";
}
int pointType::getX() const
{
	return x;
}
int pointType::getY()
{
	return y;
}

void pointType::setCoordinates(int c1, int c2)
{
	x = c1;
	y = c2;
}

//----------------------------------------------------------------------------------------------------------

circleType::circleType()
{
	radius = 1;
}

circleType::circleType(int c1, int c2, double r) : center{ c1,c2 }
{
	if (r <= 0)
		throw Invalid{};
	radius = r;
}

circleType::circleType(const pointType& p, double r)
{
	center = p;
	if (r <= 0)
		throw Invalid{};
	radius = r;

}


void circleType::printInfo() const
{
	cout << "Coordinates of the center: ";
	center.print();
	cout << endl;
	cout << "Radius: " << radius << endl;
}

double circleType::getRadius() const
{
	return radius;
}

double circleType::circumference() const
{
	return 2 * PI * radius;
}
double circleType::area() const
{
	return PI * pow(radius, 2);
}

void circleType::setInfo(int c1, int c2, double r)
{
	center.setCoordinates(c1, c2);

	if (r <= 0)
		throw Invalid{};
	radius = r;
}

//------------------------------------------------------------------------------------------------------------
cylinderType::cylinderType()
{
	height = 1;
}
cylinderType::cylinderType(int c1, int c2, double r, double h) : base{ c1,c2,r }
{
	if (h <= 0)
		throw Invalid{};
	height = h;
}

cylinderType::cylinderType(const circleType& b, double h)
{
	base = b;

	if (h <= 0)
		throw Invalid{};
	height = h;

}

double cylinderType::volume() const
{
	return base.area() * height;
}

double cylinderType::area() const
{
	return base.circumference() * height + 2 * base.area();
}

void cylinderType::setHeight(double h)
{
	if (h <= 0)
		throw Invalid{};
	height = h;


}
void cylinderType::setInfo(int c1, int c2, double r, double h)
{
	base.setInfo(c1, c2, r);
	if (h <= 0)
		throw Invalid{};
	height = h;
}
