#include "headers.h"
#include "removeColors.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "The image path should be provided." << std::endl << "input format: task.exe <Path>" << std::endl;
        return 0;
    }
    cv::String imagePath = argv[1];
    if (imagePath.empty())
    {
        std::cout << "The image path should be provided." << std::endl << "input format: task.exe <Path>" << std::endl;
        return 0;
    }
    cv::Mat image = cv::imread(imagePath);
    if (image.empty() || image.data == NULL)
    {
        std::cout << "Failed to load image: " << imagePath << std::endl;
        return 0;
    }

    cv::namedWindow("image");
    cv::imshow("image", image);
    std::cout<<"\nNumber of channels: "<<image.channels();
    RemoveColors(image);
    char c = cv::waitKey(0);
    std::cout<<"\nInput char: "<<c;
    return 0;
}
