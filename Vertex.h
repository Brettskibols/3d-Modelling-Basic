#pragma once
#include "Vector3D.h"
class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float w);
	Vertex(const Vertex& other);

	// Accessors
	float GetX() const;
	void SetX(const float x);
	int GetIntX() const;    // Cast for int X Getter
	float GetY() const;
	int GetIntY() const;    // Cast for int Y Getter
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);
	float GetW() const;
	void SetW(const float w);
	void Dehomogenize();

	//Dehomogenize method
	// Method to multiply the transformed vertices collection by Pz or W value??? (check this) to give new vertices suitable to be displayed in 2D space

	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	Vertex operator* (const float);

	const Vertex operator+ (const Vertex& rhs) const;

	static Vector3D VertexToVector3D(const Vertex first, const Vertex second);  //Takes in 2 Vertices and spits out a Vector3D

private:
	float _x;
	float _y;
	float _z;
	float _w;
};

