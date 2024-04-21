#include "headers.h"
int main(int argc, char **argv)
{
    if(argc<2){
        std::cout<<"The Image file name should be provided.\n";
        return 0;
    }
    cv::Mat img = cv::imread(argv[1]);
    if(img.data==NULL){
        std::cout<<"Could not read the image file.\n";
        return 0;
    }
    cv::namedWindow("Image");
    cv::imshow("Image", img);
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::imwrite("Garden_grayscale.jpg", gray);
    cv::waitKey(0);
    return 0;
}