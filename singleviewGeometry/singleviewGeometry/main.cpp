#pragma once 
#include <cv.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <math.h>
#include "LineOperator.cpp"
#include "Line.h"
#define PI 3.14159265359
using namespace Eigen;
using namespace std;
using namespace cv;
int rows;
int cols;
int mergeLineIndex = 0;
int main(int argc, char** argv)
{

	Mat image;
	image = imread("./EurasianCitiesBase/EurasianCitiesBase/001.jpg", IMREAD_COLOR); // Read the file
	rows = image.rows;
	cols = image.cols;
	Mat src = image.clone();

	if (image.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	
	//1. line detection using by LSD line detector
	cvtColor(image, image, CV_BGR2GRAY);
	Canny(image, image, 50, 200, 3);

	// Create and LSD detector with standard or no refinement.
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);

	double start = double(getTickCount());   
	vector<Vec4f> lines_std;    // Detect the lines  
	vector<Line> outlierRemovedLine;
	vector<Line> mergedLine;
	ls->detect(image, lines_std);  
	lineOutlierRemoval(lines_std, &outlierRemovedLine);
	mergedLine = lineMerger(outlierRemovedLine, 1); //offset angle 1
	printf("len of wholelines: %d\n", size(lines_std));
	printf("len of outlierRemovedLine: %d\n", size(outlierRemovedLine));
	printf("len of mergedlines: %d\n", size(mergedLine));

	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();  
	std::cout << "It took " << duration_ms << " ms." << std::endl;   
	
	

	// Show found lines 
	Mat drawnLines(image); 
	ls->drawSegments(drawnLines, outlierRemovedLine);
	imshow("Standard refinement", drawnLines);
	
	


	//namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image);                // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}
