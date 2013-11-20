#include <cmath>
#include <iostream>

#include "Matrix4.h"

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
}

Matrix4::Matrix4(
  double m00, double m01, double m02, double m03,
  double m10, double m11, double m12, double m13,
  double m20, double m21, double m22, double m23,
  double m30, double m31, double m32, double m33 )
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;

  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;

  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;

  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

Matrix4::Matrix4(double a[4][4]) {
	this->assign(a);
}

void Matrix4::assign(const double a[4][4]) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m[j][i] = a[i][j];
}

//operators

Matrix4& Matrix4::operator=(Matrix4 rhs) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m[i][j] = rhs.m[i][j];

	return (*this);
}


Matrix4 Matrix4::operator*(const Matrix4& rhs) {
	Matrix4 result;
	result.m[0][0] = this->get(0, 0) * rhs.get(0, 0) + this->get(0, 1) * rhs.get(1, 0) + this->get(0, 2) * rhs.get(2, 0) + this->get(0, 3) * rhs.get(3, 0);
	result.m[0][1] = this->get(0, 0) * rhs.get(0, 1) + this->get(0, 1) * rhs.get(1, 1) + this->get(0, 2) * rhs.get(2, 1) + this->get(0, 3) * rhs.get(3, 1);
	result.m[0][2] = this->get(0, 0) * rhs.get(0, 2) + this->get(0, 1) * rhs.get(1, 2) + this->get(0, 2) * rhs.get(2, 2) + this->get(0, 3) * rhs.get(3, 2);
	result.m[0][3] = this->get(0, 0) * rhs.get(0, 3) + this->get(0, 1) * rhs.get(1, 3) + this->get(0, 2) * rhs.get(2, 3) + this->get(0, 3) * rhs.get(3, 3);
	result.m[1][0] = this->get(1, 0) * rhs.get(0, 0) + this->get(1, 1) * rhs.get(1, 0) + this->get(1, 2) * rhs.get(2, 0) + this->get(1, 3) * rhs.get(3, 0);
	result.m[1][1] = this->get(1, 0) * rhs.get(0, 1) + this->get(1, 1) * rhs.get(1, 1) + this->get(1, 2) * rhs.get(2, 1) + this->get(1, 3) * rhs.get(3, 1);
	result.m[1][2] = this->get(1, 0) * rhs.get(0, 2) + this->get(1, 1) * rhs.get(1, 2) + this->get(1, 2) * rhs.get(2, 2) + this->get(1, 3) * rhs.get(3, 2);
	result.m[1][3] = this->get(1, 0) * rhs.get(0, 3) + this->get(1, 1) * rhs.get(1, 3) + this->get(1, 2) * rhs.get(2, 3) + this->get(1, 3) * rhs.get(3, 3);
	result.m[2][0] = this->get(2, 0) * rhs.get(0, 0) + this->get(2, 1) * rhs.get(1, 0) + this->get(2, 2) * rhs.get(2, 0) + this->get(2, 3) * rhs.get(3, 0);
	result.m[2][1] = this->get(2, 0) * rhs.get(0, 1) + this->get(2, 1) * rhs.get(1, 1) + this->get(2, 2) * rhs.get(2, 1) + this->get(2, 3) * rhs.get(3, 1);
	result.m[2][2] = this->get(2, 0) * rhs.get(0, 2) + this->get(2, 1) * rhs.get(1, 2) + this->get(2, 2) * rhs.get(2, 2) + this->get(2, 3) * rhs.get(3, 2);
	result.m[2][3] = this->get(2, 0) * rhs.get(0, 3) + this->get(2, 1) * rhs.get(1, 3) + this->get(2, 2) * rhs.get(2, 3) + this->get(2, 3) * rhs.get(3, 3);
	result.m[3][0] = this->get(3, 0) * rhs.get(0, 0) + this->get(3, 1) * rhs.get(1, 0) + this->get(3, 2) * rhs.get(2, 0) + this->get(3, 3) * rhs.get(3, 0);
	result.m[3][1] = this->get(3, 0) * rhs.get(0, 1) + this->get(3, 1) * rhs.get(1, 1) + this->get(3, 2) * rhs.get(2, 1) + this->get(3, 3) * rhs.get(3, 1);
	result.m[3][2] = this->get(3, 0) * rhs.get(0, 2) + this->get(3, 1) * rhs.get(1, 2) + this->get(3, 2) * rhs.get(2, 2) + this->get(3, 3) * rhs.get(3, 2);
	result.m[3][3] = this->get(3, 0) * rhs.get(0, 3) + this->get(3, 1) * rhs.get(1, 3) + this->get(3, 2) * rhs.get(2, 3) + this->get(3, 3) * rhs.get(3, 3);


	return result.transpose();
}

Vector4 Matrix4::multiply(const Vector4& v) const {
	
	Vector4 result;
	for (int i = 0; i < 4; i++) {
		result[i] = this->multRow(v, i);
	}

	return result;
}

double Matrix4::multRow(const Vector4& v, int row) const {
	const double r[4] = { get(row, 0), get(row, 1), get(row, 2), get(row, 3) };
	return (r[0] * v[0]) + (r[1] * v[1]) + (r[2] * v[2]) + (r[3] * v[3]);
}


//stuff

double* Matrix4::getPointer()
{
  return &m[0][0];
}

double Matrix4::get(int row, int col) const {
	return m[col][row];
}

void Matrix4::set(int row, int col, double val) {
	m[col][row] = val;
}

Matrix4 Matrix4::identity()
{
	double ident[4][4] = {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};
	
	return Matrix4(ident);
}

Matrix4 Matrix4::rotateX(double angle) {

	double a[4][4] = {
		{ 1 , 0          , 0           , 0 },
		{ 0 , cos(angle) , -sin(angle) , 0 },
		{ 0 , sin(angle) , cos(angle)  , 0 },
		{ 0 , 0          , 0           , 1 }
	};

	return Matrix4(a);
}

// angle in radians
Matrix4 Matrix4::rotateY(double angle)
{
	double a[4][4] = {
		{ cos(angle) , 0 , sin(angle) , 0 },
		{ 0          , 1 , 0          , 0 },
		{ -sin(angle), 0 , cos(angle) , 0 },
		{ 0          , 0 , 0          , 1 }
	};
	
	return Matrix4(a);
}

Matrix4 Matrix4::rotateZ(double angle)
{
	double a[4][4] = {
		{ cos(angle) , -sin(angle) , 0 , 0 },
		{ sin(angle) , cos(angle)  , 0 , 0 },
		{ 0          , 0           , 1 , 0 },
		{ 0          , 0           , 0 , 1 }
	};

	return Matrix4(a);
}

Matrix4 Matrix4::rotate(const Vector4& v, double angle) {
    
    if(angle == 0 || isnan(angle)) return Matrix4::identity();
    
	double a[4][4] = {
		{ cos(angle) + v.x()*v.x()*(1 - cos(angle))       , v.x()*v.y()*(1 - cos(angle)) - v.z()*sin(angle) , v.x()*v.z()*(1 - cos(angle)) + v.y()*sin(angle) , 0 },
		{ v.y()*v.x()*(1 - cos(angle)) + v.z()*sin(angle) , cos(angle) + v.y()*v.y()*(1 - cos(angle))       , v.y()*v.z()*(1 - cos(angle)) - v.x()*sin(angle) , 0 },
		{ v.z()*v.x()*(1 - cos(angle)) - v.y()*sin(angle) , v.z()*v.y()*(1 - cos(angle)) + v.x()*sin(angle) , cos(angle) + v.z()*v.z()*(1 - cos(angle))       , 0 },
		{ 0, 0, 0, 1 }
	};

	return Matrix4(a); 
}

Matrix4 Matrix4::translate(double x, double y, double z) {
	double a[4][4] = {
		{ 1, 0, 0, x },
		{ 0, 1, 0, y },
		{ 0, 0, 1, z },
		{ 0, 0, 0, 1 }
	};

	return Matrix4(a);
}

Matrix4 Matrix4::translate(const Vector4& v) {
	return Matrix4::translate(v[0], v[1], v[2]);
}

Matrix4 Matrix4::scale(double s) {
    return Matrix4::scale(s,s,s);
}

Matrix4 Matrix4::scale(double x, double y, double z) {
	double a[4][4] = {
		{ x, 0, 0, 0 },
		{ 0, y, 0, 0 },
		{ 0, 0, z, 0 },
		{ 0, 0, 0, 1 }
	};

	return Matrix4(a);
}

void Matrix4::print() {
	for (int i = 0; i < 4; i++) {
		std::cout << "[ ";
		for (int j = 0; j < 4; j++)
			std::cout << this->m[j][i] << ", ";
		std::cout << "]" << std::endl;
	}
}

Matrix4 Matrix4::transpose() {
	//because the internal array is tranposed already, this should work.
	return Matrix4(m);
}

Matrix4 Matrix4::rtInverse() {
	double a[4][4] = {
		{ get(0, 0), get(1, 0), get(2, 0), 0 },
		{ get(0, 1), get(1, 1), get(2, 1), 0 },
		{ get(0, 2), get(1, 2), get(2, 2), 0 },
		{ 0, 0, 0, 1}
	};
	return Matrix4(a) * Matrix4::translate(-get(0,3),-get(1,3), -get(2,3));
}
