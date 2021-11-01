#include <iterator>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <algorithm>
#include <math.h>

#pragma region common_used
const Scalar RED(0, 0, 255), GREEN(0, 255, 0), BLUE(255, 0, 0), WHITE(255,255,255), BLACK(0,0,0);
int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;
Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";
static void Threshold_Demo(int, void*)
{
	/* 0: Binary
	 1: Binary Inverted
	 2: Threshold Truncated
	 3: Threshold to Zero
	 4: Threshold to Zero Inverted
	*/
	threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
	imshow(window_name, dst);
}
void fillPx(uint8_t *imgPx)
{
	imgPx[0] = 255;
	imgPx[1] = 255;
	imgPx[2] = 255;
	imgPx[3] = 255;
	imgPx[4] = 128;
	imgPx[5] = 255;
	imgPx[6] = 255;
	imgPx[7] = 255;
	imgPx[8] = 255;
	return;
}
using namespace std;
using namespace cv;
#pragma endregion common_used

int main()
{
	//_4_ Threshold demo
	const char* window_name = "Threshold Demo";
	const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
	const char* trackbar_value = "Value";

	string path = "H:\\Database\\public\\butterfly.jpg";

	src = imread(path);
	cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
	namedWindow(window_name, WINDOW_AUTOSIZE); // Create a window to display results
	createTrackbar(trackbar_type,
		window_name, &threshold_type,
		max_type, Threshold_Demo); // Create a Trackbar to choose type of Threshold
	createTrackbar(trackbar_value,
		window_name, &threshold_value,
		max_value, Threshold_Demo); // Create a Trackbar to choose Threshold value
	Threshold_Demo(0, 0); // Call the function to initialize
	waitKey();
	return 0;
}
