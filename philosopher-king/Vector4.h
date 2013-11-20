#ifndef _VECTOR4_H
#define _VECTOR4_H

#define VECTOR4_RANGE_ERR "index must be in [0,4)"

class Vector4
{
protected:
	double vector[4];

public:
	
	static const int SIZE = 4;

	// Constructors
	Vector4();
	Vector4(double, double, double);
	Vector4(double, double, double, double);
	Vector4(const Vector4&);

	//Setters and Getters
	void set(double, double, double, double);
	void set(double, double, double);
	void set(int, double);

	double get(int) const;
	double& operator [](const int);
	double operator [](const int) const;

	inline double x() const {
		return this->vector[0];
	}

	inline double y() const {
		return this->vector[1];
	}

	inline double z() const {
		return this->vector[2];
	}

	inline double w() const {
		return this->vector[3];
	}

	//Arithmetic
	Vector4& operator+=(const Vector4&) ;
	void add(const Vector4&);

	Vector4& operator-=(const Vector4&) ;
	void subtract(const Vector4&);
    
    Vector4& operator*=(const float f);
    
    Vector4& negate(const Vector4&);
    void negate();

	static Vector4 cross(Vector4 u, const Vector4& v);
	void cross(const Vector4&);

	static double dot(const Vector4& u, const Vector4& v);
	double dot(const Vector4& u) const;

	static double angle(const Vector4& u, const Vector4& v);
	double angle(const Vector4&) const;

	//Utility
	static Vector4 dehomogenize(Vector4);
	void dehomogenize();

	static Vector4 normalize(Vector4);
	void normalize();

	double length() const;
	double lengthSquared() const;

	void print() const;

	static Vector4 lerp(float f, const Vector4&, const Vector4&);
};

inline Vector4 operator+(Vector4 u, const Vector4& v) {
	u += v;
	return u;
}

inline Vector4 operator-(Vector4 u, const Vector4& v) {
	u -= v;
	return u;
}

inline Vector4 operator*(Vector4 u, const float f) {
    u *= f;
    return u;
}

inline Vector4 operator-(Vector4 u) {
    u.negate();
    return u;
}

#endif //_VECTOR4_H


