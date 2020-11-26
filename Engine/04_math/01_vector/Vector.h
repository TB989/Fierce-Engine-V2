#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/
#include <cmath>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Vector2f {
public:
	Vector2f();
	Vector2f(float value);
	Vector2f(float x, float y);
	Vector2f(const Vector2f& vector);

public:
	float length();
	float lengthSquared();
	float distance(const Vector2f& vector);
	float distanceSquared(const Vector2f& vector);

	void normalize();

	void print();

public:
	float getX() { return m_x; }
	float getY() { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void setTo(const Vector2f& vector) { m_x = vector.m_x; m_y = vector.m_y; }
	void setTo(float x,float y) { m_x = x; m_y = y; }

public:
	friend Vector2f operator+(const Vector2f& v1, const Vector2f& v2);
	friend Vector2f operator-(const Vector2f& v1, const Vector2f& v2);
	friend Vector2f operator*(const Vector2f& v1, const float factor);
	friend Vector2f operator/(const Vector2f& v1, const float factor);

	friend float operator*(const Vector2f& v1, const Vector2f& v2);

	friend bool operator== (const Vector2f& v1, const Vector2f& v2);
	friend bool operator!= (const Vector2f& v1, const Vector2f& v2);

private:
	float m_x;
	float m_y;
};

class Vector3f {
public:
	Vector3f();
	Vector3f(float value);
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& vector);

public:
	float length();
	float lengthSquared();
	float distance(const Vector3f& vector);
	float distanceSquared(const Vector3f& vector);

	void normalize();

	void print();

public:
	static Vector3f cross(const Vector3f& v1,const Vector3f& v2);

public:
	float getX() { return m_x; }
	float getY() { return m_y; }
	float getZ() { return m_z; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void setZ(float z) { m_z = z; }
	void setTo(const Vector3f& vector) { m_x = vector.m_x; m_y = vector.m_y; m_z = vector.m_z; }
	void setTo(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }

public:
	friend Vector3f operator+(const Vector3f& v1, const Vector3f& v2);
	friend Vector3f operator-(const Vector3f& v1, const Vector3f& v2);
	friend Vector3f operator*(const Vector3f& v1, const float factor);
	friend Vector3f operator/(const Vector3f& v1, const float factor);

	friend float operator*(const Vector3f& v1, const Vector3f& v2);

	friend bool operator== (const Vector3f& v1, const Vector3f& v2);
	friend bool operator!= (const Vector3f& v1, const Vector3f& v2);

private:
	float m_x;
	float m_y;
	float m_z;
};

class Vector4f {
public:
	Vector4f();
	Vector4f(float value);
	Vector4f(float x, float y, float z, float w);
	Vector4f(const Vector4f& vector);

public:
	float length();
	float lengthSquared();
	float distance(const Vector4f& vector);
	float distanceSquared(const Vector4f& vector);

	void normalize();

	void print();

public:
	float getX() { return m_x; }
	float getY() { return m_y; }
	float getZ() { return m_z; }
	float getW() { return m_w; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void setZ(float z) { m_z = z; }
	void setW(float w) { m_w = w; }
	void setTo(const Vector4f& vector) { m_x = vector.m_x; m_y = vector.m_y; m_z = vector.m_z; m_w = vector.m_w;}
	void setTo(float x, float y, float z, float w) { m_x = x; m_y = y; m_z = z; m_w = w; }

public:
	friend Vector4f operator+(const Vector4f& v1, const Vector4f& v2);
	friend Vector4f operator-(const Vector4f& v1, const Vector4f& v2);
	friend Vector4f operator*(const Vector4f& v1, const float factor);
	friend Vector4f operator/(const Vector4f& v1, const float factor);

	friend float operator*(const Vector4f& v1, const Vector4f& v2);

	friend bool operator== (const Vector4f& v1, const Vector4f& v2);
	friend bool operator!= (const Vector4f& v1, const Vector4f& v2);

private:
	float m_x;
	float m_y;
	float m_z;
	float m_w;
};