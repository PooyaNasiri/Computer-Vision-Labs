#include "headers.h"
#include "ImageFilters.h"

cv::Mat min_filter(cv::Mat image, int kernel_size)
{
    if (kernel_size % 2 == 0)
    {
        std::cout << "Wrong Kernel Size. Kernel Size should be odd.\n";
        return image;
    }
    cv::Mat kernel = cv::Mat::ones(kernel_size, kernel_size, CV_8UC1);
    cv::Mat filtered_image;
    cv::erode(image, filtered_image, kernel);
    return filtered_image;
}
cv::Mat max_filter(cv::Mat image, int kernel_size)
{
    if (kernel_size % 2 == 0)
    {
        std::cout << "Wrong Kernel Size. Kernel Size should be odd.\n";
        return image;
    }
    cv::Mat kernel = cv::Mat::ones(kernel_size, kernel_size, CV_8UC1);
    cv::Mat filtered_image;
    cv::dilate(image, filtered_image, kernel);
    return filtered_image;
}