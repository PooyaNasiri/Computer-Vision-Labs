#ifndef PANORAMIC_UTILS_H
#define PANORAMIC_UTILS_H
#include "headers.h"
cv::Mat cylindricalProj(const cv::Mat &image, const double angle);
cv::Mat computeTranslation(const std::vector<cv::KeyPoint> &keypoints1, const std::vector<cv::KeyPoint> &keypoints2, const std::vector<cv::DMatch> &matches, const double ransacThreshold);
cv::Mat imageMatcher(cv::Ptr<cv::Feature2D> detector, int matcherType, cv::Mat img1, cv::Mat img2, float threshold);
cv::Mat mergeImages(const std::vector<cv::Mat> images, const std::vector<cv::Mat> translations);
#endif // PANORAMIC_UTILS_H