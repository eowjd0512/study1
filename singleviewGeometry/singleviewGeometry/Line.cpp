#include "Line.h"
extern int rows;
extern int cols;
void Line::defineGaussianPoint(){
	this->gaussian_p1 = Point3d((this->p1.x) - cols / 2, this->p1.y - rows / 2, float(cols));
	this->gaussian_p1 = Point3d((this->p2.x) - cols / 2, this->p2.y - rows / 2, float(cols));
}
void Line::cal_pi() {
	Vector3d v(this->gaussian_p1.x, this->gaussian_p1.y, this->gaussian_p1.z);
	Vector3d w(this->gaussian_p2.x, this->gaussian_p2.y, this->gaussian_p2.z);
	this->pi = v.cross(w);
};
void Line::drawLine() {

};