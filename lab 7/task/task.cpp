#include "headers.h"
#include "panoramic_utils.h"

std::vector<cv::Mat> openImagesInFolder(const std::string &folderPath)
{
    std::vector<cv::String> fileNames;
    cv::glob(folderPath + "/*.*", fileNames, true);
    std::vector<cv::Mat> images;
    for (const auto &fileName : fileNames)
    {
        cv::Mat image = cv::imread(fileName);
        if (image.empty())
            continue;
        images.push_back(image);
    }
    return images;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "The Images folder path and angle of Field of view should be provided.\n";
        std::cout << "input format: task.exe <Path> <FoV>\n";
        return 0;
    }
    std::vector<cv::Mat> images = openImagesInFolder(argv[1]);
    double angle = std::stod(argv[2]);
    if (images.size() < 2)
    {
        std::cout << "There should be at least 2 images in the folder.\n";
        return 0;
    }

    // make a vector of cylindrical projections of the images
    std::vector<cv::Mat> cylindricalImages;
    for (int i = 0; i < images.size(); i++)
        cylindricalImages.push_back(cylindricalProj(images[i], angle));

    // make a vector of translations between the images
    std::vector<cv::Mat> translations;
    for (int i = 0; i < cylindricalImages.size() - 1; i++)
        translations.push_back(imageMatcher(cv::SIFT::create(), cv::NORM_L2, cylindricalImages[i], cylindricalImages[i + 1], 0.7));

    // merge the images
    cv::Mat mergedPanorama = mergeImages(cylindricalImages, translations);
    cv::imshow("Result", mergedPanorama);
    cv::imwrite("Merged_Panorama.png", mergedPanorama);
    cv::waitKey(0);
    return 0;
}