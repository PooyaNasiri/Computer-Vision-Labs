#include "headers.h"
#include "imageMatcher.h"

    float GetAngle(std::vector<cv::KeyPoint> p1, std::vector<cv::KeyPoint> p2, std::vector<cv::DMatch> matches)
    {
        std::vector<cv::Point2f> pts1, pts2;
        for (size_t i = 0; i < matches.size(); ++i)
        {
            pts1.push_back(p1[matches[i].queryIdx].pt);
            pts2.push_back(p2[matches[i].trainIdx].pt);
        }
        if (pts1.size() < 4 || pts2.size() < 4)
            return 360;
        cv::Mat H = findHomography(pts1, pts2, cv::RANSAC);
        return atan2(H.at<double>(1, 0), H.at<double>(0, 0)) * 180 / CV_PI;
    }

    cv::Mat ImageMatcher(cv::Ptr<cv::Feature2D> detector, int matcherType, cv::Mat img1, cv::Mat img2, float &similarity, float &angle, float threshold = 0.75)
    {
        cv::Mat resultImage;
        std::vector<cv::KeyPoint> kp1, kp2;
        cv::Mat des1, des2;
        detector->detectAndCompute(img1, cv::noArray(), kp1, des1);
        detector->detectAndCompute(img2, cv::noArray(), kp2, des2);
        cv::BFMatcher matcher(matcherType);
        std::vector<std::vector<cv::DMatch>> matches;
        matcher.knnMatch(des1, des2, matches, 5);
        std::cout << "Matches: " << matches.size() << std::endl;
        std::vector<cv::DMatch> good_matches;
        for (size_t i = 0; i < matches.size(); ++i)
            if (matches[i][0].distance < threshold * matches[i][1].distance)
                good_matches.push_back(matches[i][0]);
        std::cout << "Good matches: " << good_matches.size() << std::endl;
        std::vector<std::vector<cv::DMatch>> matches_vec;
        matches_vec.push_back(good_matches);
        cv::drawMatches(img1, kp1, img2, kp2, matches_vec, resultImage);
        angle = GetAngle(kp1, kp2, good_matches);
        similarity = good_matches.size() * 100.0 / matches.size();
        return resultImage;
    }
