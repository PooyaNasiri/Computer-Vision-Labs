#include "headers.h"
#include "mouse_callback.h"
#include "BGR.h"
#include "mask.h"

void OnMouse(int event, int x, int y, int flags, void *userdata)
{
    if (event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN)
    {
        cv::Mat src = *(cv::Mat *)userdata;
        cv::Mat img = src.clone();
        if (!img.empty()){
            print_BGR(img, x, y);
            cv::Scalar mean = mean_BGR(img, x, y, 9);
            std::cout << "Mean [B,G,R,A]:" << mean;
            cv::imshow("Mask image", mask(img, mean, 65));
        }
    }
}