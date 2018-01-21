#include "Jlinkage.h"
#include <stdlib.h>
#include <time.h>
void Jlinkage::operate() {
	//1. sampling and set M
	setMandHypothesisV();
	//2. set preference matrix P
	setPreferenceMatrix();
	//3. clustering edges using by P
	lineClustering();
}
void Jlinkage::setMandHypothesisV() {
	int JM = this->JM;
	this->M.reserve(JM);
	this->hV.reserve(JM);
	for (int i = 0; i < JM; i++) {
		//clr = (random.randrange(0, 255), random.randrange(0, 255), random.randrange(0, 255));
		vector<Line> twoLines = findTwoLineBtwStd();//randomly choose M minimal sample sets of 2 deges S1...M
		this->M.push_back(twoLines);
	
		Vector3d v = calVanishingPoint(twoLines);
		this->hV.push_back(v);
	}
}
void Jlinkage::setPreferenceMatrix() {
	int Esize = size(this->E);
	this->P.resize(Esize);

	for (int i = 0; i < Esize; i++) {

		this->P[i].resize(this->JM);

		for (int j = 0; j < this->JM; j++) {
			double d = D(this->hV[j],this->E[i]);
			if (d <= this->Jpi) {
				this->P[i][j] = 1;
			}
		}
	}
}
void Jlinkage::lineClustering() {
	//use lines index instead of real line set to reduce time
	vector<vector<int>> E_idx;
	int Esize = this->E.size();
	E_idx.reserve(Esize);
	for (int i = 0; i < Esize; i++) {
		E_idx[i].push_back(i);
	}
	int i = 0;
	while (1) {
		if (i == E_idx.size() - 1) {
			break;
		}
		vector<double> distanceVector;
		distanceVector.reserve(Esize);
		for (int j = 0; j < Esize; j++) {
			if (i != j) {
				double Jd = JaccardDistance(this->P[i], this->P[j]);
				distanceVector.push_back(Jd);
			}else {
				double Jd = 1.0;
				distanceVector.push_back(Jd);
			}
		}
		int minElement = *min_element(distanceVector.begin(), distanceVector.end());
		int minElementIndex = min_element(distanceVector.begin(), distanceVector.end()) - distanceVector.begin();

		if (minElement == 1.0) {
			vector<Line> S;
			for (int k = 0; k < E_idx[i].size(); k++) {
				S.push_back(this->E[E_idx[i][k]]);
			}
			this->S.push_back(S);
			E_idx.erase(E_idx.begin() + i);
			this->P.erase(this->P.begin() + i);
		}
		else {
			//merge and erase
			vector<int> unionS = Union(E_idx[i],E_idx[minElementIndex]);
			E_idx[i] = unionS;
			E_idx.erase(E_idx.begin() + minElementIndex);
			this->P.erase(this->P.begin() + minElementIndex);
		}
	}
}
Vector3d Jlinkage::calVanishingPoint(vector<Line> twoLines) {

}

vector<int>Jlinkage::Union(vector<int> S1, vector<int>S2) {

}
double Jlinkage::JaccardDistance(vector<int> P1, vector<int>P2) {

}
vector<Line> Jlinkage::findTwoLineBtwStd() {
	/* initialize random seed: */
	srand(time(NULL));
	int randNumber = rand() % this->E.size();
	Line aLine = E[randNumber];
	vector<double> distances;
	

}
double Jlinkage::distanceFromStd() {

}
double Jlinkage::D(Vector3d v, Line E) {

}
double Jlinkage::dist() {

}
Vector3d Jlinkage::getImplicitLine() {

}