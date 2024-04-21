#include "headers.h"
#include "ImageFilters.h"

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
    int kernel_size;
    do
    {
        std::cout << "Enter the size of kernel (it should be odd): ";
        std::cin >> kernel_size;
    } while (kernel_size%2 == 0 || kernel_size < 3);
    
    cv::namedWindow("Image");
    cv::imshow("Image", img);
    cv::imshow("Min Image", min_filter(img, kernel_size));
    cv::imshow("Max Image", max_filter(img, kernel_size));
    cv::waitKey(0);
    return 0;
}