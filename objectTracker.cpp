#include "objectTracker.h"


objectTracker::objectTracker()
{
	object obj;

	// small objects 
	obj.xAxis = 34;
	obj.yAxis = 218;
	obj.size = 16;
	objectInfos.push_back(obj);

	// medium objects 
	obj.xAxis = 52;
	obj.yAxis = 201;
	obj.size = 30;
	objectInfos.push_back(obj);

	// large objects 
	obj.xAxis = 98;
	obj.yAxis = 147;
	obj.size = 37;
	objectInfos.push_back(obj);

}

void objectTracker::setParams(float minThreshold, float maxThreshold, bool filterByArea, 
	float minArea, bool filterByCircularity, float minCircularity, bool filterByConvexity, 
	float minConvexity, bool filterByInertia, float minInertiaRatio)
{
	this->params.minThreshold = minThreshold;
	this->params.maxThreshold = maxThreshold;

	this->params.filterByArea = filterByArea;
	this->params.minArea = minArea;

	this->params.filterByCircularity = filterByCircularity;
	this->params.minCircularity = minCircularity;

	this->params.filterByConvexity = filterByConvexity;
	this->params.minConvexity = minConvexity;

	this->params.filterByInertia = filterByInertia;
	this->params.minInertiaRatio = minInertiaRatio;

}

void objectTracker::toDetect(cv::Mat* result)
{

	cv::Mat im_with_keypoints;
	cv::SimpleBlobDetector detector(this->params);
	detector.detect(*result, keypoints);
	static int s = 0, m = 0, l = 0;

	for (int i = 0; i < keypoints.size(); i++)
	{ 
		if (floor(keypoints[i].pt.x) == objectInfos.at(0).xAxis && floor(keypoints[i].pt.y) == objectInfos.at(0).yAxis && floor(keypoints[i].size) == objectInfos.at(0).size)
		{
			s++;
		}
		else if (floor(keypoints[i].pt.x) == objectInfos.at(1).xAxis && floor(keypoints[i].pt.y) == objectInfos.at(1).yAxis && floor(keypoints[i].size) == objectInfos.at(1).size)
		{
			m++;
		}
		else if (floor(keypoints[i].pt.x) == objectInfos.at(2).xAxis && floor(keypoints[i].pt.y) == objectInfos.at(2).yAxis && floor(keypoints[i].size) == objectInfos.at(2).size)
		{
			l++;
		}

		if (l == 5) {
			std::cout << "small objects current count : " << s << std::endl;
			std::cout << "medium objects current count : " << m << std::endl;
			std::cout << "large objects current count : " << l << std::endl;
			std::cout << "objects total count : " << s+m+l << std::endl;

		}

	}

	drawKeypoints(*result, keypoints, im_with_keypoints, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("keypoints", im_with_keypoints);	

}
