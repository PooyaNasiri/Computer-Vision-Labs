#include "headers.h"
#include "mouse_callback.h"
#include "BGR.h"

void OnMouse(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN)
    {
        cv::Mat src = *(cv::Mat *)userdata;
        cv::Mat img = src.clone();
        if (!img.empty())
            print_BGR(img, x, y);
    }
}