#include "image_processor.hpp"

//изменение матрицы по размеру
cv::Mat Image_processor::resize(const cv::Mat& image, int width, int height){
    cv::Mat resized;

    cv::resize(image, resized, cv::Size(width, height));
    return resized;




};

//canny filter


cv::Mat Image_processor::canny_edge(const cv::Mat& image){
    cv::Mat canny;

    cv::Canny(image, canny, 50, 150, 3);

    return canny;

}



// из cv::Mat в torch::Tensor

torch::Tensor Image_processor::toTensor(const cv::Mat& image){
    cv::Mat rgb;

    cv::cvtColor(image, rgb, cv::COLOR_BGR2RGB);

    auto tensor = torch::from_blob(rgb.data, {rgb.rows, rgb.cols, 3}, torch::kUInt8);

    tensor = tensor.permute({2, 0, 1});
    tensor = tensor.to(torch::kFloat32);

    //нормализация (0.0, 1.0)
    tensor = tensor/255;

    return tensor.clone();


}







