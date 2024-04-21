#include "headers.h"

int color_low = 240, color_high = 255;
static void RefreshTrackBars(int, void *userdata)
{
    cv::Mat src = *(cv::Mat *)userdata;
    cv::Mat dst = src.clone(), canny_image;
    cv::Mat color_mask;
    cv::inRange(src, cv::Scalar(color_low, color_low, color_low), cv::Scalar(color_high, color_high, color_high), color_mask);
    cv::Canny(color_mask, canny_image, 650, 450, 3);
    dst.setTo(cv::Scalar(0, 0, 255), canny_image);
    cv::imshow("color mask", color_mask);
    cv::imshow("image", dst);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "The Image file name should be provided.\n";
        return 0;
    }
    cv::Mat img = cv::imread(argv[1]);
    if (img.data == NULL)
    {
        std::cout << "Could not read the image file.\n";
        return 0;
    }
    namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Color low", "image", &color_low, 255, RefreshTrackBars, &img);
    cv::createTrackbar("Color high", "image", &color_high, 255, RefreshTrackBars, &img);
    RefreshTrackBars(0, &img);
    cv::waitKey(0);
    return 0;
}