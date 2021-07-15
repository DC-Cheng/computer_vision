#include "main.h"

int main()
{
	//find-chessboard-corner
	//https://docs.opencv.org/4.5.2/dc/d0d/tutorial_py_features_harris.html
	//https://blog.csdn.net/guduruyu/article/details/69573824

	Mat input = imread("H:\\Database\\public\\chessboard.png");
	Mat inImageGray;
	cvtColor(input, inImageGray, COLOR_BGR2GRAY);
	Size sz(7, 7);
	std::vector<cv::Point2f> outCorners;
	bool succeed = findChessboardCorners(inImageGray, sz, outCorners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

	//enable subpixel, calculation of criteria
	TermCriteria criteria = cv::TermCriteria(
		cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
		40,
		0.1);
	cornerSubPix(inImageGray, outCorners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	//draw & see/check result
	cv::drawChessboardCorners(input, sz, outCorners, succeed);
	    
	cv::Mat imgShown;
	int ratio = 8;
	cv::resize(input, imgShown, Size(input.cols/ratio, (input.rows / ratio)));
	cv::imshow("chessboard corners", imgShown);
	cv::waitKey(0);

	return 0;
}