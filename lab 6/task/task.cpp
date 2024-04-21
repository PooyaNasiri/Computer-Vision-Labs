#include "headers.h"
#include "imageMatcher.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "The Image file name should be provided.\n";
        std::cout << "input format: task.exe <image1> <image2>\n";
        return 0;
    }
    cv::Mat img1 = cv::imread(argv[1]);
    cv::Mat img2 = cv::imread(argv[2]);
    if (img1.data == NULL || img2.data == NULL)
    {
        std::cout << "Could not read the image file.\n";
        std::cout << "input format: task.exe <image1> <image2>\n";
        return 0;
    }
    ///////////////////////////// image matching using SIFT
    float SIFT_similarity, SIFT_angle, SIFT_threshold = 0.9;
    std::cout << std::endl
              << "--- SIFT ---" << std::endl;
    cv::Mat SIFT_resultImage = ImageMatcher(cv::SIFT::create(), cv::NORM_L2, img1, img2, SIFT_similarity, SIFT_angle, SIFT_threshold);
    std::cout << "Similarity: " << SIFT_similarity << "%" << std::endl;
    std::cout << "Rotation angle: " << SIFT_angle << std::endl;
    cv::imshow("SIFT Matches", SIFT_resultImage);

    ///////////////////////////// image matching using ORB
    float ORB_similarity, ORB_angle, ORB_threshold = 0.95;
    std::cout << std::endl
              << "--- ORB ---" << std::endl;
    cv::Mat ORB_resultImage = ImageMatcher(cv::ORB::create(), cv::NORM_HAMMING, img1, img2, ORB_similarity, ORB_angle, ORB_threshold);
    std::cout << "Similarity: " << ORB_similarity << "%" << std::endl;
    std::cout << "Rotation angle: " << ORB_angle << std::endl;
    cv::imshow("ORB Matches", ORB_resultImage);

    ///////////////////////////// result analysis and conclusion based on the similarity and rotation angle values obtained from SIFT and ORB
    // if the similarity values of SIFT and ORB are both greater than 20% and the rotation angle values are close to each other, then the images are considered similar
    // if the similarity values of SIFT or ORB is greater than 40%, then the images are considered similar
    // if the rotation angle values of SIFT and ORB are very close to each other (by 5%), then the images are considered similar
    float angle_diff = abs(SIFT_angle - ORB_angle);
    bool similar = (SIFT_similarity > 20 && ORB_similarity > 20 && angle_diff < 10) || (SIFT_similarity > 30 && ORB_similarity > 30) || (angle_diff < 5);
    if (similar)
        if ((angle_diff < 10 && abs(SIFT_angle) > 5))
            std::cout << std::endl
                      << "--- Result ---" << std::endl
                      << "Similar With Transformations" << std::endl;
        else
            std::cout << std::endl
                      << "--- Result ---" << std::endl
                      << "Similar Content" << std::endl;
    else
        std::cout << std::endl
                  << "--- Result ---" << std::endl
                  << "Different Content" << std::endl;

    cv::waitKey(0);
    return 0;
}
