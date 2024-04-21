#include "oneColor.h"

void oneColor(cv::Mat img)
{
    if (img.channels() == 3)
    {
        std::vector<cv::Mat> channels(3);
        split(img, channels);
        cv::Mat new_img(img.rows, img.cols, CV_8UC1, cv::Scalar(0));
        new_img = channels[0];
        cv::imshow(" channel 0 ", new_img);
        new_img = channels[1];
        cv::imshow(" channel 1 ", new_img);
        new_img = channels[2];
        cv::imshow(" channel 2 ", new_img);
    }
}