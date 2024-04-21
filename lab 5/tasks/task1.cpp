#include "headers.h"
#include "segmenter.h"

static void OnChange(int value, void *userdata)
{
    if (userdata == nullptr)
        return;
    cv::imshow("result", Segment((*(cv::Mat *)userdata).clone(),
                                 cv::Scalar(0, 0, 0), cv::getTrackbarPos("color T", "image"),
                                 cv::getTrackbarPos("remove T", "image"),
                                 cv::getTrackbarPos("add T", "image")));
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "The Image file name should be provided.\n";
        return 0;
    }
    cv::Mat src = cv::imread(argv[1]);
    if (src.empty())
    {
        std::cout << "Could not open or find the image!\n";
        return -1;
    }
    cv::imshow("image", src);
    cv::createTrackbar("color T", "image", NULL, 255, OnChange, &src);
    cv::createTrackbar("remove T", "image", NULL, 5000, OnChange, &src);
    cv::createTrackbar("add T", "image", NULL, 5000, OnChange, &src);
    cv::setTrackbarPos("color T", "image", 75);
    cv::setTrackbarPos("remove T", "image", 300);
    cv::setTrackbarPos("add T", "image", 0);
    OnChange(0, 0);
    cv::waitKey(0);
    return 0;
}