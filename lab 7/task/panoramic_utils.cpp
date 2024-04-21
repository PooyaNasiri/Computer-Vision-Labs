#include "headers.h"
#include "panoramic_utils.h"

cv::Mat cylindricalProj(const cv::Mat &image, const double angle)
{
    cv::Mat tmp, result;
    cv::cvtColor(image, tmp, cv::COLOR_BGR2GRAY);
    result = tmp.clone();
    double alpha(angle / 180 * CV_PI);
    double d((image.cols / 2.0) / tan(alpha));
    double r(d / cos(alpha));
    double d_by_r(d / r);
    int half_height_image(image.rows / 2);
    int half_width_image(image.cols / 2);
    for (int x = -half_width_image + 1, x_end = half_width_image; x < x_end; ++x)
        for (int y = -half_height_image + 1, y_end = half_height_image; y < y_end; ++y)
        {
            double x1(d * tan(x / r));
            double y1(y * d_by_r / cos(x / r));
            if (x1 < half_width_image &&
                x1 > -half_width_image + 1 &&
                y1 < half_height_image &&
                y1 > -half_height_image + 1)
                result.at<uchar>(y + half_height_image, x + half_width_image) = tmp.at<uchar>(round(y1 + half_height_image), round(x1 + half_width_image));
        }
    return result;
}

cv::Mat computeTranslation(const std::vector<cv::KeyPoint> &keypoints1, const std::vector<cv::KeyPoint> &keypoints2, const std::vector<cv::DMatch> &matches, const double ransacThreshold)
{
    std::vector<cv::Point2f> points1, points2;
    for (const auto &match : matches)
    {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }
    cv::Mat mask;
    cv::Mat H = cv::findHomography(points1, points2, cv::RANSAC, ransacThreshold, mask);
    std::vector<cv::Point2f> inlierPoints1, inlierPoints2;
    for (size_t i = 0; i < mask.rows; ++i)
    {
        if (mask.at<uchar>(i))
        {
            inlierPoints1.push_back(points1[i]);
            inlierPoints2.push_back(points2[i]);
        }
    }
    double totalTx = 0.0, totalTy = 0.0;
    for (size_t i = 0; i < inlierPoints1.size(); ++i)
    {
        double tx = inlierPoints2[i].x - inlierPoints1[i].x;
        double ty = inlierPoints2[i].y - inlierPoints1[i].y;
        totalTx += tx;
        totalTy += ty;
    }
    double avgTx = totalTx / inlierPoints1.size();
    double avgTy = totalTy / inlierPoints1.size();
    cv::Mat translationMatrix = (cv::Mat_<double>(3, 3) << 1, 0, avgTx, 0, 1, avgTy, 0, 0, 1);
    return translationMatrix;
}

cv::Mat imageMatcher(cv::Ptr<cv::Feature2D> detector, int matcherType, cv::Mat img1, cv::Mat img2, float threshold = 0.5)
{
    cv::Mat resultImage;
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat des1, des2;
    detector->detectAndCompute(img1, cv::noArray(), kp1, des1);
    detector->detectAndCompute(img2, cv::noArray(), kp2, des2);
    cv::BFMatcher matcher(matcherType);
    std::vector<std::vector<cv::DMatch>> matches;
    matcher.knnMatch(des1, des2, matches, 5);
    std::vector<cv::DMatch> good_matches;
    for (size_t i = 0; i < matches.size(); ++i)
        if (matches[i][0].distance < threshold * matches[i][1].distance)
            good_matches.push_back(matches[i][0]);
    cv::Mat translation = computeTranslation(kp1, kp2, good_matches, threshold);
    return translation;
}

cv::Mat mergeImages(const std::vector<cv::Mat> images, const std::vector<cv::Mat> translations)
{
    // compute the height of the panorama, which is the height of the tallest image
    int panoramaHeight = 0;
    int padding = 5;
    for (const auto &image : images)
        panoramaHeight = std::max(panoramaHeight, image.rows);

    // compute the width of the panorama, which is the sum of the widths of the images
    int panoramaWidth = images.back().cols + translations.back().at<double>(0, 2);
    for (int i = 0; i < translations.size(); i++)
        panoramaWidth -= translations[i].at<double>(0, 2) + padding;

    // create the panorama
    cv::Mat mergedPanorama(panoramaHeight, panoramaWidth, CV_8UC1, cv::Scalar(0));

    // copy the first image to the leftmost part of the panorama separately
    cv::Mat translatedImage;
    cv::warpPerspective(images[0], translatedImage, translations[0], cv::Size(panoramaWidth, panoramaHeight));
    translatedImage.copyTo(mergedPanorama(cv::Rect(0, 0, translatedImage.cols, translatedImage.rows)));
    int x = 0;
    for (int i = 1; i < images.size(); i++)
    {
        cv::warpPerspective(images[i], translatedImage, translations[i - 1], cv::Size(images[i].cols + translations[i - 1].at<double>(0, 2), panoramaHeight));
        x -= translations[i - 1].at<double>(0, 2) + padding;
        translatedImage.copyTo(mergedPanorama(cv::Rect(x, 0, translatedImage.cols, translatedImage.rows)));
    }

    return mergedPanorama;
}