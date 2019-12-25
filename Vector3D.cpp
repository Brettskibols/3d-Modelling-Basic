#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D()
{
	_xv = 0.0f;
	_yv = 0.0f;
	_zv = 0.0f;
}

Vector3D::~Vector3D() 
{
}

Vector3D::Vector3D(float xv, float yv, float zv)
{
	_xv = xv;
	_yv = yv;
	_zv = zv;
}

Vector3D::Vector3D(const Vector3D& other)
{
	_xv = other.GetXv();
	_yv = other.GetYv();
	_zv = other.GetZv();
}

float Vector3D::GetXv() const
{
	return _xv;
}

void Vector3D::SetXv(const float xv)
{
	_xv = xv;
}

float Vector3D::GetYv() const 
{
	return _yv;
}

void Vector3D::SetYv(const float yv)
{
	_yv = yv;
}

float Vector3D::GetZv() const
{
	return _zv;
}

void Vector3D::SetZv(const float zv)
{
	_zv = zv;
}

Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
	if (this != &rhs)
	{
		_xv = rhs.GetXv();
		_yv = rhs.GetYv();
		_zv = rhs.GetZv();
	}
	return *this;
}

bool Vector3D::operator==(const Vector3D& rhs) const
{
	return (_xv == rhs.GetXv() && _yv == rhs.GetYv() && _zv == rhs.GetZv());
}

const Vector3D Vector3D::operator-(const Vector3D& rhs) const  //const Vector3D operator- (const Vector3D& rhs) const;
{
	return Vector3D(_xv - rhs.GetXv(), _yv - rhs.GetYv(), _zv - rhs.GetZv());
}

const Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return Vector3D(_xv + rhs.GetXv(), _yv + rhs.GetYv(), _zv + rhs.GetZv());
}

const Vector3D Vector3D::operator*(const Vector3D& rhs) const
{
	return Vector3D(_xv * rhs.GetXv(), _yv * rhs.GetYv(), _zv * rhs.GetZv());
}

float Vector3D::GetLength() const
{
	float squaredValue = 0;
	float squareRootedValue = 0;
	squaredValue = (float)(pow(GetXv(), 2.0)) + (float)(pow(GetYv(), 2.0)) + (float)(pow(GetZv(), 2.0));
	squareRootedValue = (float)sqrt(squaredValue);

	return squareRootedValue; 
}

//Makes Dot Product from 2 Vectors
float Vector3D::DotProduct(const Vector3D first, const Vector3D second) 
{
	float dotProduct = 0;
	dotProduct = (first.GetXv() * second.GetXv()) + (first.GetYv() * second.GetYv()) + (first.GetZv() * second.GetZv());
	
	return dotProduct;
}

//Makes Cross Product from 2 vectors
Vector3D Vector3D::CrossProduct(const Vector3D first, const Vector3D second)
{
	return Vector3D((first.GetYv() * second.GetZv()) - (first.GetZv() * second.GetYv()), 
		            (first.GetZv() * second.GetXv()) - (first.GetXv() * second.GetZv()), 
		            (first.GetXv() * second.GetYv()) - (first.GetYv() * second.GetXv()));
}

Vector3D Vector3D::NormaliseVector3D()                      //  Vector3D vector1 = (0, 1, 2, 3);
															//  Vector3D normalisedVector1 = vector1.NormaliseVector3D();
{

	//Vector3D temp = input;
	float vectorLength = GetLength();    //doesn't like it unsued may look to alter later
	return Vector3D();
}
