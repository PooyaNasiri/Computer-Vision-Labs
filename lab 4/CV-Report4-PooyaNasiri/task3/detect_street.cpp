#include "headers.h"
#include "detect_street.h"

cv::Mat DrawLine(cv::Mat img, cv::Vec2f line)
{
    cv::Point pt1, pt2;
    double a = cos(line[1]), b = sin(line[1]);
    double x0 = a * line[0], y0 = b * line[0];
    pt1.x = cvRound(x0 + 1000 * (-b)), pt1.y = cvRound(y0 + 1000 * (a)), pt2.x = cvRound(x0 - 1000 * (-b)), pt2.y = cvRound(y0 - 1000 * (a));
    cv::line(img, pt1, pt2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    return img;
}
cv::Vec2f StreeLines(int degree, std::vector<cv::Vec2f> lines)
{
    cv::Vec2f line;
    int max_rho = 0;
    for (size_t i = 0; i < lines.size(); i++)
        if (std::abs(lines[i][1] * 180 / CV_PI - degree) < 10)
            if (std::abs(lines[i][0]) > max_rho)
                line[0] = lines[i][0], line[1] = lines[i][1], max_rho = lines[i][0];
    return line;
}

double GetX(cv::Vec2f line1, int y)
{
    return (y - (line1[0] / sin(line1[1]))) / (-cos(line1[1]) / sin(line1[1]));
}

cv::Point GetIntersection(cv::Vec2f line1, cv::Vec2f line2)
{
    return cv::Point((line1[0] * sin(line2[1]) - line2[0] * sin(line1[1])) / (cos(line1[1]) * sin(line2[1]) - cos(line2[1]) * sin(line1[1])), (cos(line1[1]) * line2[0] - cos(line2[1]) * line1[0]) / (cos(line1[1]) * sin(line2[1]) - cos(line2[1]) * sin(line1[1])));
}

cv::Mat DetectStreet(cv::Mat src, cv::Mat canny)
{
    cv::Mat lines_image = src.clone(), finalImage = src.clone();
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(canny, lines, 1, CV_PI / 1800, 100, 0, 0);
    cv::Vec2f line_L = StreeLines(130, lines);
    cv::Vec2f Line_R = StreeLines(45, lines);
    lines_image = DrawLine(lines_image, line_L);
    lines_image = DrawLine(lines_image, Line_R);
    cv::imshow("4) Lines", lines_image);
    std::vector<cv::Point> points = {GetIntersection(line_L, Line_R), cv::Point(GetX(line_L, src.rows), src.rows), cv::Point(GetX(Line_R, src.rows), src.rows)};
    cv::fillConvexPoly(finalImage, points, cv::Scalar(0, 0, 255));
    return finalImage;
}