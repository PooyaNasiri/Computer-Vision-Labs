#ifndef IMAGEMATCHER_H
#define IMAGEMATCHER_H
#include "headers.h"
float GetAngle(std::vector<cv::KeyPoint>, std::vector<cv::KeyPoint>, std::vector<cv::DMatch>);
cv::Mat ImageMatcher(cv::Ptr<cv::Feature2D>, int, cv::Mat, cv::Mat, float &, float &, float);
#endif // !SEGMENTER_H