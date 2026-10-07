#pragma once
#include <opencv2/opencv.hpp>
#include <torch/torch.h>


class Image_processor{

    public:
    cv::Mat resize(const cv::Mat& image, int width, int height);

    cv::Mat canny_edge(const cv::Mat& image);

    torch::Tensor toTensor(const cv::Mat& image);


};