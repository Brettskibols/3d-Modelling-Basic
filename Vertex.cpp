#include "Vertex.h"
#include <math.h>

Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 0.0f;
}

Vertex::Vertex(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

Vertex::Vertex(float x, float y, float z) 
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
}

Vertex::Vertex(const Vertex& other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
	_w = other.GetW();
}

float Vertex::GetX() const
{
	return _x;
}

int Vertex::GetIntX() const    //change to int Vertex::GetIntX() const
{
	return static_cast<int>(_x);       // Cast to access int value of X rather than casting it in the main program
}


void Vertex::SetX(const float x)
{
	_x = x;
}

float Vertex::GetY() const
{
	return _y;
}

int Vertex::GetIntY() const  //change to int Vertex::GetIntY() const
{
	return static_cast<int>(_y);      // Cast to access int value of X rather than casting it in the main program
}

void Vertex::SetY(const float y)
{
	_y = y;
}

float Vertex::GetZ() const
{
	return _z;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}

float Vertex::GetW() const
{
	return _w;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

void Vertex::Dehomogenize()
{
	_x = _x / _w;
	_y = _y / _w;
	_z = _z / _w;
	_w = _w / _w;
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_w = rhs.GetW();
	}
	return *this;
}

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() && _w == rhs.GetW());
}

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ(), _w + rhs.GetW());
}

Vector3D Vertex::VertexToVector3D(const Vertex first, const Vertex second)
{
	return Vector3D(first.GetX() - second.GetX(), first.GetY() - second.GetY(), first.GetZ() - second.GetZ());
}

Vertex Vertex::operator*(float angle) 
{	Vertex temp;

   // angle = WAYNES CODE FOR RADIANS - rather than add to the main line of the code

	temp.SetX(static_cast<float>((GetX() * (cos(angle))) - (GetY() * sin(angle))));
	temp.SetY(static_cast<float>((GetY() * (cos(angle))) + (GetX() * sin(angle))));                    //INPUT Z'S and add angle = radians formula.
	temp.SetW(1);                                                                                      // STILL NEEDS RADIANS INPUT BUT WORKS FINE

	return temp;

}