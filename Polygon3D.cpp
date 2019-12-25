#include "Polygon3D.h"

Polygon3D::Polygon3D() : _indices{ 0 }
{
	//Empty constructor
	_cullPolygonFlag = false;
	_averageZValue = 0.0;
	_resultingColor = (RGB(0, 0, 0));
}

Polygon3D::Polygon3D(const int& index0, const int& index1, const int& index2) : _indices { 0 }   //Polygon that accepts 3 indices ONLY!!!
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_cullPolygonFlag = false;
	_averageZValue = 0.0;
	_resultingColor = (RGB(0, 0, 0));
}

Polygon3D::~Polygon3D()
{
	//Destructor for Polygons called upon exit from program
}

Polygon3D::Polygon3D(const Polygon3D& other) : _indices{ 0 }           //Copies indices values to new polygon.
{
	_indices[0] = other._indices[0];
	_indices[1] = other._indices[1];
	_indices[2] = other._indices[2];
	_cullPolygonFlag = other._cullPolygonFlag;
	_averageZValue = other._averageZValue;
	_resultingColor = other._resultingColor;
}

int Polygon3D::GetIndex(const int& i) const   // Pointer to _indices index
{
	if (i < 0 || i > 3)
	{
		return -1;
	}
	return _indices[i];
}

bool Polygon3D::GetcullPolygonFlag() const
{
	return _cullPolygonFlag;
}

void Polygon3D::SetcullPolygonFlag(bool input)
{
	_cullPolygonFlag = input;
}

float Polygon3D::GetaverageZValue() const
{
	return _averageZValue;
}

void Polygon3D::SetaverageZValue(float input)
{
	_averageZValue = input;
}

COLORREF Polygon3D::GetResultingColor()
{
	return _resultingColor;
}

void Polygon3D::SetResultingColor(COLORREF inputColor)
{
	_resultingColor = inputColor;
}

/*
const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ(), _w + rhs.GetW());
}
*/

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)                 //EQUALS OPERATOR casting current values to new polygon
{
	_resultingColor = rhs._resultingColor;
	_indices[0] = rhs._indices[0];
	_indices[1] = rhs._indices[1];
	_indices[2] = rhs._indices[2];
	_cullPolygonFlag = rhs._cullPolygonFlag;
	_averageZValue = rhs._averageZValue;
	return *this;
}