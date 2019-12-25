#pragma once
class Vector3D
{
public:
	Vector3D();
	~Vector3D();
	Vector3D(float xv, float yv, float zv);
	Vector3D(const Vector3D& other);
	
	// Accessors
	float GetXv() const;
	void SetXv(const float xv);
	float GetYv() const;
	void SetYv(const float yv);
	float GetZv() const;
	void SetZv(const float zv);
	
	//Assignment operators
	Vector3D& operator= (const Vector3D& rhs);
	bool operator== (const Vector3D& rhs) const;
	const Vector3D operator- (const Vector3D& rhs) const;
	const Vector3D operator+ (const Vector3D& rhs) const;
	const Vector3D operator* (const Vector3D& rhs) const;
	float GetLength() const;
	static float DotProduct(const Vector3D first, const Vector3D second);
	static Vector3D CrossProduct(const Vector3D first, const Vector3D second);
	Vector3D NormaliseVector3D();

private:
	float _xv;
	float _yv;
	float _zv;
};

