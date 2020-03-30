/**********************************************************
Name:	opencv_image_processing
Date:	20200327
Author: DC.Chneg
Note:	Git Release
Brief:	1. image filter
		2. image sobel/canny
Reference: 
		1. https://medium.com/@pomelyu5199/canny-edge-detector-%E5%AF%A6%E4%BD%9C-opencv-f7d1a0a57d19
		2. https://docs.opencv.org/3.4/da/d5c/tutorial_canny_detector.html
		3. https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/sobel_derivatives/sobel_derivatives.html
**********************************************************/
#include <windows.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>

cv::Mat m_cvImageMat;

void deleteSSBuffer(std::stringstream& _ss)
{
	_ss.str("");
	_ss.clear();
}
std::string createSSContent(std::string& _strFolder, std::string& _str)
{
	std::stringstream ss;
	ss << _strFolder << _str;
	std::string _strResult;
	ss >> _strResult;
	deleteSSBuffer(ss);
	return _strResult;
}
void getImageBuffer(std::string& strFolder)
{
	std::string strSrc_Ori = "lena512.bmp";
	strSrc_Ori = createSSContent(strFolder, strSrc_Ori);
	m_cvImageMat = cv::imread(strSrc_Ori);
}
void medianFilter(std::string& strFolder)
{

	std::string strDst_Median = "lena512_Median.bmp";
	strDst_Median = createSSContent(strFolder, strDst_Median);
	cv::Mat cvImageMat_Median;
	cv::medianBlur(m_cvImageMat,cvImageMat_Median,5);
	cv::imwrite(strDst_Median,cvImageMat_Median);
}
void blurFilter(std::string& strFolder)
{
	std::string strDst_Smooth = "lena512_Smoothing.bmp";
	strDst_Smooth = createSSContent(strFolder, strDst_Smooth);
	cv::Mat cvImageMat_Smooth;
	cv::blur(m_cvImageMat,cvImageMat_Smooth,cv::Size(5,5));
	cv::imwrite(strDst_Smooth,cvImageMat_Smooth);
}
void gaussianFilter(std::string& strFolder)
{	
	std::string strDst_Gaussian = "lena512_Gaussian.bmp";
	strDst_Gaussian = createSSContent(strFolder, strDst_Gaussian);
	cv::Mat cvImageMat_Gaussian;
	cv::GaussianBlur(m_cvImageMat,cvImageMat_Gaussian,cv::Size(5,5),0);	
	cv::imwrite(strDst_Gaussian,cvImageMat_Gaussian);

	//gaussian+sobel
	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y;
	cv::Mat cvImageMat_Gaussian_Sobel;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	cv::Sobel( cvImageMat_Gaussian, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
	cv::convertScaleAbs( grad_x, abs_grad_x );
	cv::Sobel( cvImageMat_Gaussian, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
	cv::convertScaleAbs( grad_y, abs_grad_y );
	cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, cvImageMat_Gaussian_Sobel );
	std::string strDst_Gaussian_Sobel = "lena512_Gaussian_Sobel.bmp";
	strDst_Gaussian_Sobel = createSSContent(strFolder, strDst_Gaussian_Sobel);
	cv::imwrite(strDst_Gaussian_Sobel,cvImageMat_Gaussian_Sobel);

	//gaussian+canny
	cv::Mat cvImageMat_Gaussian_Canny;
	double threshold1 = 0;
	double threshold2 = 100;
	cv::Canny(cvImageMat_Gaussian,cvImageMat_Gaussian_Canny,threshold1,threshold2,3);
	std::string strDst_Gaussian_Canny = "lena512_Gaussian_Canny.bmp";
	strDst_Gaussian_Canny = createSSContent(strFolder, strDst_Gaussian_Canny);
	cv::imwrite(strDst_Gaussian_Canny,cvImageMat_Gaussian_Canny);

}

int main(int argc, char const *argv[]) 
{
	std::string strFolder = "..\\material\\";
	getImageBuffer(strFolder);
	gaussianFilter(strFolder);
	medianFilter(strFolder);
	blurFilter(strFolder);
	MessageBox(NULL,"Done!","Result",MB_OK);
	return 0;
}
