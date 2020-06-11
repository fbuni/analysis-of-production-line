#include <opencv2/opencv.hpp>
#include <iostream>
#include<string>
#include"objectTracker.h"
#include"frameTracker.h"
int main() {

	cv::Mat orjFrame, copyFrame,result;
	cv::VideoCapture cap("C:\\Users\\OmerSait\\Desktop\\uretimHatti.mp4");
	if (!cap.isOpened()) {
		std::cout << "Error: Video cannot be opened" << std::endl;
		return -1;
	}
	cap.read(copyFrame);
	while (cap.isOpened()) {
		cap >> orjFrame;
		if (orjFrame.empty())
			break;

		cv::imshow("orjFrame", orjFrame); 

		frameTracker frTracker(&orjFrame, &copyFrame);

		frTracker.toGray(CV_BGR2GRAY);

		frTracker.toBlur(cv::Size(9, 9));

		frTracker.toDif();

		frTracker.toTreshHolding(72, 255, CV_THRESH_BINARY);
		frTracker.toDilate();
		result = frTracker.toRemoveBackground();

		objectTracker objTracker;
		objTracker.setParams(0, 500, true, 300, false, 0.1, false, 0.87, false, 0.01);
		objTracker.toDetect(&result);

		char c = (char)cv::waitKey(3);
		if (c == 27) break; // 27 refers to button of escape button. If you press the esc button for three second, program comes to halt
	}
	return 0;
}

