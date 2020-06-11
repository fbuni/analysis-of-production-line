#pragma once
#include <opencv2/opencv.hpp>

class frameTracker
{
private:
	cv::Mat orjFrame;
	cv::Mat copyFrame;
	cv::Mat difFrame;
	cv::Mat result;
	cv::Mat thresh;
public:
	frameTracker(cv::Mat* orj, cv::Mat* copy);
	void toGray(int code);
	void toBlur(cv::Size ksize);
	void toDif();
	void toTreshHolding(double thresh, double maxval, int type);
	void toDilate();
	cv::Mat toRemoveBackground();
};

