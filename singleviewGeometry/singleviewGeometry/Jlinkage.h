#pragma once
#include <cv.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <math.h>
#include "LineOperator.cpp"
#include "Line.h"
using namespace Eigen;
using namespace std;
using namespace cv;

class Jlinkage
{
	vector<Line> E; //the set of all the edges
	vector<vector<Line>> M; //two line sets for calculation of v
	vector<vector<Line>> S; //clustered edges sets
	vector<Vector3d> hV; //hypothesis vanishing points sets
	vector<vector<int>> P; //preference matrix
	float Jpi = 0.;
	int JM = 0;
	int std = 0;
	
	Jlinkage(vector<Line> mergedLine, float Jpi, int JM, int std) {
		this->E = mergedLine;
		this->Jpi = Jpi;
		this->JM = JM;
		this->std = std;
		operate();
	}
	void operate();
	void lineClustering();
	void setMandHypothesisV();
	void setPreferenceMatrix();
	Vector3d calVanishingPoint(vector<Line> twoLines);
	vector<int> Union(vector<int> S1, vector<int>S2);
	double JaccardDistance(vector<int> P1, vector<int>P2);
	vector<Line> findTwoLineBtwStd();
	double distanceFromStd();
	double D(Vector3d v, Line E);
	double dist();
	Vector3d getImplicitLine();
	~Jlinkage(){}
};