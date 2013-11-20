#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector4.h"

class Matrix4
{
private:
	void assign(const double[4][4]);
	double multRow(const Vector4& v, int row) const;

  protected:
    double m[4][4];   // matrix elements
    
  public:
    Matrix4();        // constructor
    Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
	Matrix4(double[4][4]);
    double* getPointer();  // return pointer to matrix elements
	double get(int, int) const;
	void set(int, int, double);

	Matrix4& operator =(Matrix4);
	Matrix4 operator*(const Matrix4&);

	Vector4 multiply(const Vector4&) const;


	/* Generators */
	static Matrix4 identity();  // create identity matrix

	static Matrix4 rotateX(double);
	static Matrix4 rotateY(double);
	static Matrix4 rotateZ(double);

	static Matrix4 rotate(const Vector4&, double);

	static Matrix4 translate(double, double, double);
	static Matrix4 translate(const Vector4&);

    static Matrix4 scale(double);
	static Matrix4 scale(double, double, double);

	void print();

	Matrix4 transpose();
	Matrix4 rtInverse();
};

inline Vector4 operator*(const Matrix4& lhs, const Vector4& rhs) {
	return lhs.multiply(rhs);
}

#endif