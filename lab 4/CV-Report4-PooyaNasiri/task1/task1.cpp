#include "headers.h"

cv::Mat src;
int threshold1 = 845, threshold2 = 435;
const int max_Threshold = 1000;
static void RefreshTrackBars(int, void *)
{
    cv::Mat dst, canny_image;
    cv::Canny(src, canny_image, threshold1, threshold2, 3);
    dst = src.clone();
    dst.setTo(cv::Scalar(0, 0, 255), canny_image);
    cv::imshow("image", dst);
    cv::imshow("Canny image", canny_image);
}

int main(int argc, char **argv)
{
    src = cv::imread("street_scene.png");
    if (src.empty())
    {
        std::cout << "Could not open or find the image!\n";
        return -1;
    }
    namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Threshold1", "image", &threshold1, max_Threshold, RefreshTrackBars);
    cv::createTrackbar("Threshold2", "image", &threshold2, max_Threshold, RefreshTrackBars);
    RefreshTrackBars(0, 0);
    cv::waitKey(0);
    return 0;
}
