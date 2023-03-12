#include <iostream>
#include <bitset>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace Actions
{
    namespace Images
    {
        void Crop(cv::Mat &img, int ksize, std::vector<cv::Rect> &rects)
        {
            cv::Mat gray, thresh, close, dilate;
            cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);
            cv::threshold(gray, thresh, 0, 255, cv::THRESH_BINARY_INV + cv::THRESH_OTSU);
            auto kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(ksize, ksize));
            cv::morphologyEx(thresh, close, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 2);
            cv::dilate(close, dilate, kernel);

            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(dilate, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

            rects.reserve(contours.size());
            rects.clear();

            for (auto &&c : contours)
            {
                cv::Rect rect = cv::boundingRect(c);
                rects.emplace_back(rect);
                cv::rectangle(img, rect, cv::Scalar(0, 0, 255), 2);
            }
        }
    } // namespace Images
} // namespace Actions
