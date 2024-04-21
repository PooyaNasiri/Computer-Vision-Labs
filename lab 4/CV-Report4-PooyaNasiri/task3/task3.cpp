#include "headers.h"
#include "detect_street.h"

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
    cv::Mat canny_image;
    cv::Mat color_mask;
    int l = 240, h = 255;
    cv::inRange(img, cv::Scalar(l, l, l), cv::Scalar(h, h, h), color_mask);
    cv::imshow("2) Color Mask", color_mask);
    cv::Canny(color_mask, canny_image, 0, 0, 3);
    cv::imshow("3) Canny Image", canny_image);
    cv::imshow("5) Street", DetectStreet(img, canny_image));
    img.setTo(cv::Scalar(0, 0, 255), canny_image);
    cv::imshow("1) image", img);
    cv::waitKey();
    return 0;
}