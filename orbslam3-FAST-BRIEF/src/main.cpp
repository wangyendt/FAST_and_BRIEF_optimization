//
// Created by wayne on 2023/2/7.
//


#include "iostream"
#include "ORBextractor.h"
#include "opencv2/opencv.hpp"
#include <chrono>

using namespace ORB_SLAM3;

int main() {
    ORBextractor *mpORBextractorLeft;
    mpORBextractorLeft = new ORBextractor(1000, 1.2f, 8, 20, 7);

    cv::VideoCapture cap(1);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640.0f);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480.0f);
    cv::Mat frame, gray;
    std::vector<cv::KeyPoint> mvKeys;
    cv::Mat mDescriptors;
    std::vector<int> vLapping = {0, 0};
    int monoLeft = 0;

    auto pre_fps = 10.0f;
    auto last_timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1e9;
    auto fps_win = 10;


    while (cap.isOpened()) {
        cap >> frame;
        cv::flip(frame, frame, 1);
        auto cur_timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1e9;
        auto cur_fps = 1.0 / (cur_timestamp - last_timestamp);
        last_timestamp = cur_timestamp;
        auto fps_n = pre_fps * fps_win;
        fps_n -= (pre_fps - cur_fps);
        auto fps = fps_n / fps_win;
        pre_fps = fps;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        monoLeft = (*mpORBextractorLeft)(gray, cv::Mat(), mvKeys, mDescriptors, vLapping);
        std::cout << monoLeft << std::endl;
        cv::cvtColor(gray, gray, cv::COLOR_GRAY2BGR);

        for (auto vKey: mvKeys) {
            cv::circle(gray, vKey.pt, 1, cv::Scalar());
            cv::rectangle(gray, cv::Point(vKey.pt.x - 1, vKey.pt.y - 1), cv::Point(vKey.pt.x + 1, vKey.pt.y + 1), cv::Scalar(0, 255, 0), 1);
        }


        cv::putText(gray, std::to_string(fps), cv::Point(0, 100), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 255), 4);
        cv::imshow("Video", gray);
        if (cv::waitKey(10) == 27) {
            break;
        }
    }

    return 0;
}