
//camera class realisation

#ifndef OPENCVPROJECT_CAMERA_H
#define OPENCVPROJECT_CAMERA_H

#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class Camera {
public:
    explicit Camera(int deviceIndex = 0)
        : capture_(deviceIndex)
    {
    }

    bool isOpened() const
    {
        return capture_.isOpened();
    }

    bool read(cv::Mat& frame)
    {
        return capture_.read(frame) && !frame.empty();
    }

private:
    cv::VideoCapture capture_;
};
#endif //OPENCVPROJECT_CAMERA_H
