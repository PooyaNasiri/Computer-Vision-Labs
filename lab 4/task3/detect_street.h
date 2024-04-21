#include "headers.h"

cv::Mat DrawLine(cv::Mat , cv::Vec2f );
cv::Vec2f StreeLines(int , std::vector<cv::Vec2f> );
double GetX(cv::Vec2f , int );
cv::Point GetIntersection(cv::Vec2f , cv::Vec2f );
cv::Mat DetectStreet(cv::Mat , cv::Mat );