//Vector is need for GameObjects
// with operator overloading
#pragma once
#include<math.h>

//Create a vector class
class Vector2D
{
public:
	Vector2D() : m_x(0), m_y(0) {}//Default value makes (0, 0)
	Vector2D(float x, float y) : m_x(x), m_y(y) {}
	float getX() { return m_x; }
	float getY() { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	float length() { return sqrt(m_x * m_x + m_y * m_y); }

	/*Overloaded operators for my class vector
	With these functions we can add two vectors together using the standard
	addition operators, for example:
	Vector2D v1(10, 11);
	Vector2D v2(35,25);
	v1 += v2;
	Vector2D v3 = v1 + v2;*/
	Vector2D operator+(const Vector2D& v2) const
	{
		return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
	}

	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;
		return v1;
	}
	//Multiply by a scalar number, to inclrease x and y
	Vector2D operator*(float scalar)
	{
		return Vector2D(m_x * scalar, m_y * scalar);
	}

	Vector2D& operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;
		return *this;
	}
	//Subtraction of two vectors
	Vector2D operator-(const Vector2D& v2) const
	{
		return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
	}

	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;
		return v1;
	}
	//Divide by a scalar number
	Vector2D operator/(float scalar)
	{
		return Vector2D(m_x / scalar, m_y / scalar);
	}

	Vector2D& operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;
		return *this;
	}
	/*Normalize: Vectors with a length
	(magnitude) of 1 are known as unit vectors and are useful to represent just a
	direction*/
	void normalize()
	{
		float l = length();
		if (l > 0) // never want to attempt to divide by 0
		{
			(*this) *= 1 / l;
		}
	}

private:
	float m_x;
	float m_y;
};