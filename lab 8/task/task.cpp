#include "headers.h"

double computeReprojectionError(const std::vector<std::vector<cv::Point3f>> &objPoints,
                                const std::vector<std::vector<cv::Point2f>> &imagePoints,
                                const cv::Mat &cameraMatrix, const cv::Mat &distCoeffs,
                                const std::vector<cv::Mat> &rvecs, const std::vector<cv::Mat> &tvecs)
{
    double totalError = 0.0;
    for (size_t i = 0; i < objPoints.size(); ++i)
    {
        std::vector<cv::Point2f> projectedPoints;
        cv::projectPoints(objPoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, projectedPoints);
        totalError += cv::norm(imagePoints[i], projectedPoints, cv::NORM_L2);
    }
    return std::sqrt(totalError / objPoints.size());
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "The data folder path and pattern size (width,hight) should be provided.\nThe path should contain a folder named checkerboard_images containing the image dataset and an image named test_image.png" << std::endl;
        std::cout << "input format: task.exe <Path> <W> <H>" << std::endl;
        return 0;
    }
    int w = std::stoi(argv[2]), h = std::stoi(argv[3]);
    cv::Size patternSize(w, h);
    cv::String path = argv[1];
    std::vector<cv::String> imagePaths;
    cv::glob(path + "checkerboard_images\\*.*", imagePaths);

    /////////////////////////////////////////////////////////Find the chessboard
    std::vector<std::vector<cv::Point2f>> imagePoints;
    std::vector<cv::Mat> images;
    for (const auto &imagePath : imagePaths)
    {
        cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
        if (image.empty())
        {
            std::cout << "Failed to load image: " << imagePath << std::endl;
            continue;
        }
        std::vector<cv::Point2f> corners;
        bool patternFound = cv::findChessboardCorners(image, patternSize, corners);
        if (patternFound)
        {
            std::cout << "Checkerboard pattern found in image: " << imagePath << std::endl;
            cv::cornerSubPix(image, corners, cv::Size(5, 5), cv::Size(-1, -1),
                             cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, w * h, 0.1));
            imagePoints.push_back(corners);
            cv::drawChessboardCorners(image, patternSize, corners, patternFound);
            images.push_back(image);
        }
        else
            std::cout << "Checkerboard pattern not found in image: " << imagePath << std::endl;
    }
    std::cout << "Checkerboard pattern found in " << images.size() << " images out of " << imagePaths.size() << std::endl;

    /////////////////////////////////////////////////////////Colibrating camera
    std::cout << "Colibrating camera..." << std::endl;
    std::vector<cv::Point3f> objPointsRow;
    for (int i = 0; i < patternSize.height; ++i)
        for (int j = 0; j < patternSize.width; ++j)
            objPointsRow.push_back(cv::Point3f(j, i, 0));
    std::vector<std::vector<cv::Point3f>> objPoints;
    objPoints.resize(imagePoints.size(), objPointsRow);
    cv::Mat cameraMatrix, distCoeffs;
    std::vector<cv::Mat> rvecs, tvecs;
    double reprojectionError = cv::calibrateCamera(objPoints, imagePoints, images[0].size(),
                                                   cameraMatrix, distCoeffs, rvecs, tvecs);
    if (reprojectionError)
    {
        double meanError = computeReprojectionError(objPoints, imagePoints, cameraMatrix,
                                                    distCoeffs, rvecs, tvecs);
        std::cout << "Camera calibration successful!" << std::endl
                  << "Reprojection error: " << reprojectionError << std::endl
                  << "Camera matrix:" << std::endl
                  << cameraMatrix << std::endl
                  << "Distortion coefficients:" << std::endl
                  << distCoeffs << std::endl
                  << "Mean reprojection error: " << meanError << std::endl;
        for (const auto &img : images)
        {
            cv::Mat undistortedImage;
            cv::Mat map1, map2;
            cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), cameraMatrix,
                                        img.size(), CV_32FC1, map1, map2);
            cv::remap(img, undistortedImage, map1, map2, cv::INTER_LINEAR);
            cv::Mat result;
            cv::hconcat(img, undistortedImage, result);
            cv::resize(result, result, cv::Size(result.cols / 2, result.rows / 2));
            cv::imshow("Distorted vs Undistorted", result);
            cv::waitKey(0);
        }


        /////////////////////////////////////////////////Undistort the test image
        cv::Mat testImage = cv::imread(path + "test_image.png");
        cv::Mat undistortedImage;
        cv::Mat map1, map2;
        cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), cameraMatrix,
                                    testImage.size(), CV_32FC1, map1, map2);
        cv::remap(testImage, undistortedImage, map1, map2, cv::INTER_LINEAR);
        cv::Mat result;
        cv::hconcat(testImage, undistortedImage, result);
        cv::resize(result, result, cv::Size(result.cols / 2, result.rows / 2));
        cv::imshow("Distorted vs Undistorted", result);
        cv::waitKey(0);
    }
    else
        std::cout << "Camera calibration failed!" << std::endl;

    return 0;
}
