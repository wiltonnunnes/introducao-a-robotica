#include <opencv2/opencv.hpp>
#include <iostream>
#include <map>

using namespace cv;
using namespace std;

Vec3b darkBlue(255, 0, 0);
Vec3b blue(255, 255, 0);
Vec3b black(0, 0, 0);
Vec3b green(0, 255, 0);
Vec3b yellow(0, 255, 255);
Vec3b red(0, 0, 255);
Vec3b magenta(255, 0, 255);

map<int, Vec3b> colors = {{0, darkBlue}, {1, blue}, {2, black}, {3, green}, {4, yellow}, {5, red}, {6, magenta}};

void filtroRGB(Mat img, uchar r, uchar g, uchar b) {
	int x, y;
	for (y = 0; y < img.rows; y++)
		for (x = 0; x < img.cols; x++) {
			Vec3b intensity = img.at<Vec3b>(y, x);
			if (!(intensity[0] == b && intensity[1] == g && intensity[2] == r)) {
				img.at<Vec3b>(y, x)[0] = 255;
				img.at<Vec3b>(y, x)[1] = 255;
				img.at<Vec3b>(y, x)[2] = 255;
			}
		}
}

Point getTarget(Mat img) {
	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);
	GaussianBlur(gray, gray, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows / 8, 200, 100, 0, 0);
	Point target(circles[0][0], circles[0][1]);
	return target;
}

void getTargets(int order[], int numTargets) {
	Mat img, kernel;

	img = imread("targets.png");
	kernel = Mat::ones(9, 9, CV_64F) / 25;

	int i, j;
	for (i = 0; i < numTargets; i++) {
		Vec3b color = colors[order[i]];
		Mat aux = imread("targets.png");
		filtroRGB(aux, color[2], color[1], color[0]);

		for (j = 0; j < 10; j++)
			filter2D(aux, aux, -1, kernel);

		Point target = getTarget(aux);
		cout << "x=" << target.x << ", y=" << target.y << endl;
	}
}

int main() {
	int order[] = {0, 1, 2, 3, 4, 5, 6};
	getTargets(order, 7);
	/*
	Mat img, aux, kernel;
	img = imread("targets.png");

	aux = img.clone();
	filtroRGB(aux, 0, 0, 0);

	kernel = Mat::ones(9, 9, CV_64F) / 25;
	for (int i = 0; i < 10; i++)
		filter2D(aux, aux, -1, kernel);

	f(aux);	

	namedWindow("img", WINDOW_NORMAL);
	imshow("img", aux);
	waitKey(0);
	*/
	return 0;
}
