#include "frameTracker.h"

frameTracker::frameTracker(cv::Mat* orj, cv::Mat* copy)
{
	this->orjFrame = *orj;
	this->copyFrame = *copy;

}

void frameTracker::toGray(int code)
{
	//A grayscale image only requires information of density.
	//All we need is one byte per pixel of grayscale image.
	// A byte can store a value between 0 and 255 so it contains all possible shades of gray.
	// In some cases, its highly recommended that work with grayscale image.
	// Thats why that i convert this frames into grayscale frames.

	cv::cvtColor(this->orjFrame, this->orjFrame, CV_BGR2GRAY);
	cv::cvtColor(this->copyFrame, this->copyFrame, CV_BGR2GRAY);
}


void frameTracker::toBlur(cv::Size ksize)
{
	//types of to blur 
	//blur - GaussianBlur - medianBlur - bilateralFilter 
	// There are several reason to use gaussian filter for this case. The Gaussian filter is a linear filter that can use -
	// - them for "unsharp masking" (edge detection). 
	// Unlike the gaussian filter, median filter is nonlineer filter that removes noise while keeping edges relatively sharp.
	// The video that i used for this project, the edges of product line must be blur as much as possible.

	cv::GaussianBlur(this->orjFrame, this->orjFrame, ksize, 0);
	cv::GaussianBlur(this->copyFrame, this->copyFrame, ksize, 0);
}


void frameTracker::toDif()
{
	//Calculates the per-element absolute difference between two arrays or between an array and a scalar.
	//I.e. calculates the differences between thw two frames.
	//As a result of this extraction process, the changing parts, such as moving parts, are shown.
	//The objective of the project is get some information on total count of each product.

	cv::absdiff(this->orjFrame, this->copyFrame, this->difFrame);
}

void frameTracker::toTreshHolding(double thresh, double maxval, int type)
{
	//Thresholding is typically used to get a bi-level (binary) image out of a grayscale image or or removing a noise
	//Filtering out pixels can have too small or too large values
	//Need to update the pixels on black or white according to the given threshold value.

	threshold(this->difFrame, this->thresh, thresh, maxval, type);
}

void frameTracker::toDilate()
{
	//Increases the object area
	//Used to accentuate features
	// To dilate objects ensure the detection of any object as much as possible
	// There are three types objects, two of which is in need of dilation

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9), cv::Point(-1, -1));
	dilate(this->thresh, this->thresh, kernel);
}

cv::Mat frameTracker::toRemoveBackground()
{
	//There are three ways to remove background 
	//BackgroundSubtractorMOG,  ve BackgroundSubtractorGMG
	//BackgroundSubtractorMOG2 selects the appropriate number of Gaussian distributions for each pixel. That's why i prefer the BackgroundSubtractorMOG2.
	// For more information = https://www.geeksforgeeks.org/background-subtraction-opencv/

	cv::BackgroundSubtractorMOG2 mog2;
	mog2(this->thresh, this->result);

	return this->result;
}

