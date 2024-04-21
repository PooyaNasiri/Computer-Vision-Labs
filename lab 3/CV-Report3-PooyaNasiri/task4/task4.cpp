#include "headers.h"
#include "mouse_callback.h"

int main(int argc, char **argv)
{
    cv::Mat img = cv::imread("./robocup.jpg");
    cv::imshow("Image", img);
    cv::setMouseCallback("Image", OnMouse, (void *)&img);
    cv::waitKey(0);
    return 0;
}
