#include "headers.h"
#include "circle.h"

cv::Mat DetectYellow(cv::Mat img)
{
    cv::Mat hsv;
    cvtColor(img, hsv, cv::COLOR_BGR2HSV);
    cv::Mat mask;
    inRange(hsv, cv::Scalar(20, 110, 100), cv::Scalar(80, 190, 255), mask);
    cv::Mat yellow_pixels;
    bitwise_and(img, img, yellow_pixels, mask);
    return yellow_pixels;
}
cv::Mat DetectCircle(cv::Mat img, int CircleSize)
{
    cv::Mat gray;
    cv::Mat circ = cv::Mat::zeros(img.size(), CV_8UC1);
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 16, 10, 16, 1, CircleSize);
    for (size_t i = 0; i < circles.size(); i++)
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(circ, center, radius, cv::Scalar(255, 255, 255), -1, cv::LINE_AA);
    }
    return circ;
}
cv::Mat DrawCircle(cv::Mat img, cv::Mat src)
{
    cv::Mat circleImage = src.clone();
    circleImage.setTo(cv::Scalar(0, 255, 0), img);
    return circleImage;
}