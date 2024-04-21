#include "headers.h"
#include "mouse_callback.h"

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
    cv::namedWindow("HSV Image");
    cv::Mat hsvImage;
    cv::cvtColor(img, hsvImage, cv::COLOR_BGR2HSV);
    cv::imshow("HSV Image", hsvImage);
    cv::setMouseCallback("Image", OnMouse, (void *)&hsvImage);
    cv::waitKey(0);
    return 0;
}
