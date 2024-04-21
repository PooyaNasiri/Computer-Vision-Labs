#ifndef SEGMENTER_H
#define SEGMENTER_H
#include "headers.h"
cv::Mat removeArea(const cv::Mat, const int);
cv::Mat addArea(const cv::Mat, const int);
cv::Mat Mask(const cv::Mat, const cv::Scalar, const int);
cv::Mat Segment(const cv::Mat, const cv::Scalar, const int, const int, const int);
#endif // !SEGMENTER_H