#pragma once
struct Vector2
{





	float x;
	float y;
	Vector2();
	Vector2(float x, float y);
	float length()const;
	Vector2& normalize();
	float dot(const Vector2& v)const;
	Vector2 operator+()const;
	Vector2 operator-()const;

	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};
	const  Vector2 operator+(const Vector2& v1, const Vector2& v2);
	const Vector2 operator-(const Vector2&  v1, const Vector2& v2);
	const Vector2 operator*(const Vector2& v, float s);
	const Vector2 operator*(float s,const Vector2& v);
	const Vector2 operator/(const Vector2& v, float s);

	 


