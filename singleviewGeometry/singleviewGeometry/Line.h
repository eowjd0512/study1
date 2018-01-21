#pragma once
#include <cv.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <math.h>
using namespace Eigen;
using namespace std;
using namespace cv;

//alpha = np.arange(-180, 181, 1)
extern int rows;
class Line
{
public:
	Point3d p1 = (0., 0., 0.);
	Point3d p2 = (0., 0., 0.);
	Point3d gaussian_p1 = (0., 0., 0.);
	Point3d gaussian_p2 = (0., 0., 0.);
	Point3d pm = (0., 0., 0.);
	Point3d implict_l = (0., 0., 0.);
	Vector3d pi;
	int index = 0;

	Line(float x1, float y1, float x2, float y2, int index) {
		this->p1 = Point3d(x1, y1, 1.0);
		this->p2 = Point3d(x2, y2, 1.0);
		this->pm = (this->p1 + this->p2)/2.0;
		this->index = index;

	};
	void defineGaussianPoint();
	void cal_pi();
	void drawLine();
	~Line(){}
};
	