#include "Camera.hpp"
#include <opencv2/opencv.hpp>

Camera::Camera(){

    cap.open(0);


}



void Camera::show(){
    while (true){

    cv::Mat frame = getFrame();

    if (frame.empty()) break;
    cv::Mat canny;
    cv::Canny(frame, canny, 40, 40, 3);
    cv::imshow("Camera", canny);
    

    if (cv::waitKey(90) == 'q') break; // нажать q для остановки
    
    }

}

bool Camera::isOpened(){
    return cap.isOpened();

}





cv::Mat Camera::getFrame(){
    cv::Mat frame;

    cap >> frame;

    return frame;


}

