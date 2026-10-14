#pragma once

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

#include <string>

class FaceDetector {
public:
    explicit FaceDetector(const std::string& modelPath)
    {
        detector_ = cv::FaceDetectorYN::create(
            modelPath,
            "",
            cv::Size(320, 320),
            0.9f,
            0.3f,
            5000
        );
    }

    cv::Mat detect(const cv::Mat& frame)
    {
        detector_->setInputSize(frame.size());

        cv::Mat faces;
        detector_->detect(frame, faces);

        return faces;
    }

private:
    cv::Ptr<cv::FaceDetectorYN> detector_;
};