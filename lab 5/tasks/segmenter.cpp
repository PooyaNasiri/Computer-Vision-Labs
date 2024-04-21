#include "headers.h"
#include "segmenter.h"

cv::Mat removeArea(const cv::Mat mask, const int minPixels = 50)
{
    cv::Mat labels, stats, centroids;
    int nLabels = cv::connectedComponentsWithStats(mask, labels, stats, centroids);
    cv::Mat result = cv::Mat::zeros(mask.size(), CV_8UC1);
    for (int i = 1; i < nLabels; i++)
    {
        int area = stats.at<int>(i, cv::CC_STAT_AREA);
        if (area >= minPixels)
        {
            cv::Mat mask_i = (labels == i);
            mask_i.copyTo(result, mask_i);
        }
    }
    // cv::imshow("Result Mask", result);
    return result;
}

cv::Mat addArea(const cv::Mat mask, const int minSize = 50)
{
    cv::Mat labels, stats, centroids;
    cv::Mat resultMask = 255 - mask;
    int nLabels = cv::connectedComponentsWithStats(mask, labels, stats, centroids);
    std::vector<int> labelsToAdd;
    for (int i = 1; i < nLabels; i++)
    {
        int area = stats.at<int>(i, cv::CC_STAT_AREA);
        if (area < minSize)
            labelsToAdd.push_back(i);
    }

    for (int i = 0; i < labelsToAdd.size(); i++)
    {
        cv::Mat componentMask = (labels == labelsToAdd[i]);
        resultMask.setTo(1, componentMask);
    }
    resultMask = 255 - resultMask;
    // cv::imshow("mask", mask);
    return resultMask;
}

cv::Mat Mask(const cv::Mat img, const cv::Scalar mean, const int threshold)
{
    cv::Mat mask_img;
    cv::Mat mask1_img(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int y = 0; y < img.rows; y++)
        for (int x = 0; x < img.cols; x++)
            if (abs(img.at<cv::Vec3b>(cv::Point(x, y))(0) - mean[0]) < threshold && abs(img.at<cv::Vec3b>(cv::Point(x, y))(1) - mean[1]) < threshold && abs(img.at<cv::Vec3b>(cv::Point(x, y))(2) - mean[2]) < threshold)
                mask1_img.at<cv::Vec3b>(cv::Point(x, y)) = {255, 255, 255, 0};
    // cv::imshow("img", mask1_img);
    cv::cvtColor(mask1_img, mask_img, cv::COLOR_BGR2GRAY);
    return mask_img;
}

cv::Mat Segment(const cv::Mat src, const cv::Scalar color, const int colorT, const int removeT, const int addT)
{
    cv::Mat img = src.clone();
    cv::GaussianBlur(img, img, cv::Size(5, 5), 0);
    cv::Mat maskedImg = Mask(img, color, colorT);
    cv::Mat removedNoise = removeArea(maskedImg, removeT);
    cv::Mat filledGaps = addArea(removedNoise, addT);
    return filledGaps;
}