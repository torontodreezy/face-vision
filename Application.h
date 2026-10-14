#pragma once

#include "Camera.h"
#include "FaceDetector.h"
#include "FaceDetector.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

class Application {
public:
    static int run() {
        try {
            Application app;
            return app.runLoop();
        }
        catch (const cv::Exception& error) {
            cv::destroyAllWindows();
            std::cerr << "OpenCV error: " << error.what() << '\n';
            return 1;
        }
    }

private:
    Application() = default;

    int runLoop() {
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

    void processFrame() {
        faces_ = detector_.detect(frame_);

        // Рисуем на копии исходного кадра.
        displayFrame_ = frame_.clone();
        drawFaces();
    }

    void drawFaces() {
        const cv::Scalar cornerColor(255, 220, 0); // Голубой в BGR
        const cv::Scalar pointColor(0, 220, 255); // Жёлтый в BGR

        for (int i = 0; i < faces_.rows; ++i) {
            const float* face = faces_.ptr<float>(i);

            const int x = cvRound(face[0]);
            const int y = cvRound(face[1]);
            const int width = cvRound(face[2]);
            const int height = cvRound(face[3]);

            const int right = x + width;
            const int bottom = y + height;
            const int length = std::max(
                1, std::min(width, height) / 5
            );

            // Верхний левый угол.
            drawLine({x, y}, {x + length, y}, cornerColor);
            drawLine({x, y}, {x, y + length}, cornerColor);

            // Верхний правый угол.
            drawLine({right, y}, {right - length, y}, cornerColor);
            drawLine({right, y}, {right, y + length}, cornerColor);

            // Нижний левый угол.
            drawLine({x, bottom}, {x + length, bottom}, cornerColor);
            drawLine({x, bottom}, {x, bottom - length}, cornerColor);

            // Нижний правый угол.
            drawLine({right, bottom}, {right - length, bottom}, cornerColor);
            drawLine({right, bottom}, {right, bottom - length}, cornerColor);

            // Пять ключевых точек лица.
            for (int point = 0; point < 5; ++point) {
                const cv::Point position(
                    cvRound(face[4 + point * 2]),
                    cvRound(face[5 + point * 2])
                );

                cv::circle(
                    displayFrame_,
                    position,
                    3,
                    pointColor,
                    cv::FILLED,
                    cv::LINE_AA
                );
            }
        }
    }

    void drawLine(
        cv::Point start,
        cv::Point end,
        const cv::Scalar& color) {
        cv::line(displayFrame_, start, end, color, 3, cv::LINE_AA);
    }

    void showFrame() const {
        cv::imshow("Faces", displayFrame_);
    }

    bool exitRequested() const {
        return cv::waitKey(1) == 27;
    }

    Camera camera_{0};
    FaceDetector detector_{"detectface.onnx"};

    cv::Mat frame_;
    cv::Mat displayFrame_;
    cv::Mat faces_;
};
