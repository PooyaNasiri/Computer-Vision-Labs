#include "headers.h"
#include "mask.h"

cv::Mat mask(cv::Mat img, cv::Scalar mean, unsigned int T = 65)
{
    cv::Mat mask_img(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int y = 0; y < img.rows; y++)
        for (int x = 0; x < img.cols; x++)
            if (abs(img.at<cv::Vec3b>(cv::Point(x, y))(0) - mean[0]) < T && abs(img.at<cv::Vec3b>(cv::Point(x, y))(1) - mean[1]) < T && abs(img.at<cv::Vec3b>(cv::Point(x, y))(2) - mean[2]) < T)
                mask_img.at<cv::Vec3b>(cv::Point(x, y)) = {255, 255, 255, 0};
    return mask_img;
}