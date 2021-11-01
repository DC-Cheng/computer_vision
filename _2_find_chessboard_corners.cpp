#include "header/main.h"

using namespace cv;
using namespace std;

/*-- Content --*/
/* input / processing / output */

int main()
{
	//input
	//Mat input = imread("H:\\Database\\public\\chessboard.png");
	Mat input = imread("H:\\Database\\public\\right01.jpg");
	Mat inImageGray;
	cvtColor(input, inImageGray, COLOR_BGR2GRAY);
	Size sz(9, 6);
	std::vector<cv::Point2f> outCorners;
	bool succeed = findChessboardCorners(inImageGray, sz, outCorners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

	//subpixel
	TermCriteria criteria = cv::TermCriteria(
		cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
		40,
		0.1);
	cornerSubPix(inImageGray, outCorners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	//result
	cv::drawChessboardCorners(input, sz, outCorners, succeed);

	cv::Mat imgShown;
	int ratio = 1;
	cv::resize(input, imgShown, Size(input.cols / ratio, (input.rows / ratio)));
	cv::imshow("Result", imgShown);
	imwrite("H:\\Database\\result\\\FindChessBoardCorners.jpg", imgShown);
	cv::waitKey(0);
	return 0;
}

/*-- Reference --*/
/* 
	1. https://docs.opencv.org/4.5.2/dc/d0d/tutorial_py_features_harris.html
	2. https://blog.csdn.net/guduruyu/article/details/69573824
*/
