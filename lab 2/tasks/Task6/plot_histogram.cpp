#include "headers.h"
#include "plot_histogram.h"

void plot_histogram(cv::Mat image, int bins)
{
    int histSize = bins-1;
    float range[] = {0, bins};
    const float *histRange = {range};
    bool uniform = true, accumulate = false;
    cv::Mat input_hist;
    cv::calcHist(&image, 1, 0, cv::Mat(), input_hist, 1, &histSize, &histRange, uniform, accumulate);
    int hist_w = 600, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
    normalize(input_hist, input_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    for (int i = 1; i < histSize; i++)
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(input_hist.at<float>(i - 1))),
             cv::Point(bin_w * i, hist_h - cvRound(input_hist.at<float>(i))), cv::Scalar(128, 128, 128), 2, cv::LINE_AA);
    cv::imshow("Histogram", histImage);
}