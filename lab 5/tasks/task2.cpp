#include "headers.h"
#include "segmenter.h"

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
    cv::Mat result;
    src.copyTo(result, Segment(src, cv::Scalar(120, 120, 120), 35, 1000, 1100));
    src.copyTo(result, Segment(src, cv::Scalar(255, 200, 120), 60, 1000, 0));
    cv::imshow("result", result);
    cv::waitKey(0);
    return 0;
}