#pragma once 
#include <cv.hpp>
#include <iostream>
#include <math.h>
#include "SCC.h"
#include "Line.h"
using namespace cv;
using namespace std;
vector<Line> lineMerger(vector<Line> ls, double offset_angle) {
	
	Graph g1 = Graph(ls.size());
	for (vector<Line>::iterator i = ls.begin(); i != ls.end(); ++i) {
		for (vector<Line>::iterator j = ls.begin(); j != ls.end(); ++j) {
			if (i->index != j->index) {
				double dotValue = i->pi.dot(j->pi);
				double theta = acos(dotValue) / (i->pi.norm()*j->pi.norm());
				double degrees = theta * (180.0 / 3.141592653589793238463);
				if (degrees < offset_angle) {
					g1.addEdge(i->index, j->index);
				}
			}
		}
	}
	vector<Line> merged_line_array = g1.SCC(ls);
	return merged_line_array;
}

void lineOutlierRemoval(vector<Vec4f> ls, vector<Line>* outlierRemovedLine) {
	//dist__ = [];
	//draw histogram
	double lsDistances = ls.size();
	Mat lsDistancesArray = Mat(1, lsDistances, CV_8UC1);
	uchar* data = (uchar*)lsDistancesArray.data;
	int index = 0;
	for(int i = 0; i < ls.size(); i++) {
		float x1 = ls[i][0];
		float y1 = ls[i][1];
		float x2 = ls[i][2];
		float y2 = ls[i][3];
		double dist_ = sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
		//insert a value to a mat which will use for histogram calculation
		//lsDistancesArray.at<uchar>(0,i) = dist_;
		
		//data[i] = dist_;
		if (dist_ > 30) {
			Line aLine = Line(x1,y1,x2,y2,index);
			aLine.defineGaussianPoint();
			aLine.cal_pi();
			outlierRemovedLine->push_back(aLine);
			index++;
		}
	}
	

		/*for x1, y1, x2, y2 in lines[i] :
			dist_ = sqrt((x2 - x1)**2 + (y2 - y1)**2)
			dist__.append(dist_)

			b = np.linspace(0.0, 100.0, num = 100)
			hist_, bin_edges = np.histogram(np.array(dist__), bins = b)
			print("len of hist: ", len(hist_))
			print("len of b : ", len(b))
			#for i in range(len(hist_)) :
			#print("i : ", i, "hist: ", hist_[i])
			plt.hist(np.array(dist__), bins = b)  # arguments are passed to np.histogram
			plt.title("Histogram with 'auto' bins")
			plt.show()

			param = getParam(b, hist_) + 5

			'''
			cnt = 0
			min_hist = 10
			for i in range(0, 80) :
				cnt = 0
				if hist_[i] <min_hist :
					for j in range(i + 1, 80) :
						if hist_[j]<min_hist :
							cnt += 1
							if cnt == (80 - i - 1) :
								Th_dist = i
								break
								print("Th_dist: ", Th_dist)
								'''

								line_array = []
								j = 0
								for i in range(len(lines)) :
									for x1, y1, x2, y2 in lines[i] :
										if dist__[i] >= param :
											line = Line(x1 - 320., y1 - 240., x2 - 320., y2 - 240., j, for_GS)
											j += 1
#line.cal_beta()
											line_array.append(line)*/
}
