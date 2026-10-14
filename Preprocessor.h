//
// Created by bladerunner on 10/14/26.
//

#ifndef OPENCVPROJECT_PREPROCESSOR_H
#define OPENCVPROJECT_PREPROCESSOR_H
#pragma once

#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>

class Preprocessor {
public:
    explicit Preprocessor(int width = 224, int height = 224)
        : inputSize_(width, height)
    {
    }

    cv::Mat toTensor(const cv::Mat& frame) const
    {
        return cv::dnn::blobFromImage(
            frame,
            1.0 / 255.0,    // Масштаб: 0–255 → 0–1
            inputSize_,     // Размер изображения на входе модели
            cv::Scalar(),   // Ничего не вычитаем из значений
            true,           // Меняем BGR на RGB
            false,          // Изменяем размер без обрезки
            CV_32F          // Тип элементов: float
        );
    }

private:
    cv::Size inputSize_;
};
#endif //OPENCVPROJECT_PREPROCESSOR_H
