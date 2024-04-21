#include "headers.h"
#include "BGR.h"

void print_BGR(cv::Mat img, int x, int y)
{
    if (!img.empty())
    {
        std::cout << "\n------------------------------------------------------";
        std::cout << "\nMouse clicked position (x,y): " << x << ", " << y << "\n";
        int b = img.at<cv::Vec3b>(y, x)[0];
        int g = img.at<cv::Vec3b>(y, x)[1];
        int r = img.at<cv::Vec3b>(y, x)[2];
        std::cout << "B: " << b << " | G: " << g << " | R: " << r << "\n";
    }
}

cv::Scalar mean_BGR(cv::Mat img, int x, int y, int neighborhood)
{
    if (!img.empty())
    {
        if (y + neighborhood > img.rows || x + neighborhood > img.cols)
            return cv::Scalar(0, 0, 0, 0);
        cv::Rect rect(x, y, neighborhood, neighborhood);
        cv::Scalar mean = cv::mean(img(rect));
        return mean;
    }
    return cv::Scalar(0, 0, 0, 0);
}