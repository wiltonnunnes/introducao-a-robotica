#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void DecomposicaoTrapezoidal(Mat img) {
	Mat aux = img.clone();
	for (int x = 0; x < img.cols; x++)
		for (int y = 0; y < img.rows; y++) {			
			if (aux.at<Vec3b>(y, x) == Vec3b(0, 0, 0))
				cout << "Is black.\n"; 
		}
}

int main(int argc, char** argv) {
	Mat img, gray;

	img = imread(argv[1], 1);

	if (!img.data) {
		return -1;
	}

	DecomposicaoTrapezoidal(img);
	/*
	cvtColor(img, gray, CV_BGR2GRAY);

	GaussianBlur(gray, gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows / 8, 200, 100, 0, 0);

	for (size_t i = 0; i < circles.size(); i++) {
		cout << "x=" << circles[i][0] << ", y=" << circles[i][1] << ", radius=" << circles[i][2] << endl;
	}
	*/

	return 0;
}
