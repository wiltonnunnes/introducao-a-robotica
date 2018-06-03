#include <opencv2/opencv.hpp>
#include <iostream>
#include <map>

using namespace cv;
using namespace std;

Vec3b darkBlue(255, 0, 0);
Vec3b blue(255, 255, 0);
Vec3b black(159, 159, 159);
Vec3b green(0, 255, 0);
Vec3b yellow(0, 255, 255);
Vec3b red(0, 0, 255);
Vec3b magenta(255, 0, 255);

map<int, Vec3b> colors = {{0, darkBlue}, {1, blue}, {2, black}, {3, green}, {4, yellow}, {5, red}, {6, magenta}};

vector<Point> getTargets(int order[]) {
	unsigned int numTargets = 7;

	Mat img, kernel, gray;
	img = imread("targets.png");

	kernel = Mat::ones(5, 5, CV_64F) / 25;

	filter2D(img, img, -1, kernel);

	cvtColor(img, gray, CV_BGR2GRAY);
	GaussianBlur(gray, gray, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows / 8, 200, 100, 0, 0);

	vector<Point> targets;

	unsigned int i, j;
	for (i = 0; i < numTargets; i++) {
		Vec3b color = colors[order[i]];
		for (j = 0; j < circles.size(); j++) {
			Vec3b intensity = img.at<Vec3b>(circles[j][1], circles[j][0]);
			if (intensity == color)
				targets.push_back(Point(circles[j][0], circles[j][1]));
		}
	}

	return targets;
}

int main() {
	int order[] = {0, 1, 2, 3, 4, 5, 6};

	vector<Point> targets = getTargets(order);

	for (size_t i = 0; i < targets.size(); i++)
		cout << "x=" << targets[i].x << ", y=" << targets[i].y << endl;

	return 0;
}