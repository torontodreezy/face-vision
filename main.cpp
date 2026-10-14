#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    cv::Mat g = cv::imread("/home/bladerunner/Pictures/topg.webp");
    cv::imshow("g", g);
    cv::waitKey(0);


}