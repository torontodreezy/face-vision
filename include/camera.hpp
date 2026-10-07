#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>



class Camera{
    public:
    Camera();


    bool isOpened();
    
    cv::Mat getFrame();

    void show();

    private:
    cv::VideoCapture cap;
    

};