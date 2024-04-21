#include "headers.h"
#include "circle.h"

static void RefreshTrackBars(int CircleSize, void *userdata)
{
    cv::Mat src = *(cv::Mat *)userdata;
    cv::Mat yellowImage = DetectYellow(src);
    cv::imshow("Yellow Pixels", yellowImage);
    cv::Mat circleImage = DetectCircle(yellowImage, CircleSize);
    cv::imshow("Detected Circles", circleImage);
    cv::imshow("image", DrawCircle(circleImage, src));
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
    int CircleSize = 8;
    namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("CircleSize", "image", &CircleSize, 300, RefreshTrackBars, &img);
    RefreshTrackBars(CircleSize, &img);
    cv::waitKey(0);
    return 0;
}
