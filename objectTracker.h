#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "object.h"

class objectTracker
{
private:
	cv::Mat frame;
	std::vector<cv::KeyPoint> keypoints;
	cv::SimpleBlobDetector::Params params;
	std::vector<object> objectInfos;
	std::vector<object> objects;
public:
	objectTracker();
	void setParams(float minThreshold, float maxThreshold, bool filterByArea, float minArea,
		bool filterByCircularity, float minCircularity, bool filterByConvexity,
		float minConvexity, bool filterByInertia, float minInertiaRatio);
	void toDetect(cv::Mat* result);
};

