//
// Created by bladerunner on 10/14/26.
//

#ifndef OPENCVPROJECT_APPLICATION_H
#define OPENCVPROJECT_APPLICATION_H
#pragma once

#include "Camera.h"
#include "Preprocessor.h"

#include <opencv2/highgui.hpp>
#include <iostream>

class Application {
public:
    int run()
    {
        if (!camera_.isOpened()) {
            std::cerr << "Cannot open camera\n";
            return 1;
        }

        while (true) {
            if (!camera_.read(frame_)) {
                std::cerr << "Cannot read frame\n";
                cv::destroyAllWindows();
                return 1;
            }

            processFrame();
            showFrame();

            if (exitRequested()) {
                break;
            }
        }

        cv::destroyAllWindows();
        return 0;
    }

private:
    void processFrame()
    {
        tensor_ = preprocessor_.toTensor(frame_);

        if (!printedTensorInfo_) {
            printTensorInfo();
            printedTensorInfo_ = true;
        }
    }

    void printTensorInfo() const
    {
        std::cout << "Tensor shape: ["
                  << tensor_.size[0] << ", "
                  << tensor_.size[1] << ", "
                  << tensor_.size[2] << ", "
                  << tensor_.size[3] << "]\n";
    }

    void showFrame() const
    {
        cv::imshow("Webcam", frame_);
    }

    bool exitRequested() const
    {
        return cv::waitKey(1) == 27;
    }

    Camera camera_{0};
    Preprocessor preprocessor_{224, 224};

    cv::Mat frame_;
    cv::Mat tensor_;

    bool printedTensorInfo_ = false;
};
#endif //OPENCVPROJECT_APPLICATION_H
