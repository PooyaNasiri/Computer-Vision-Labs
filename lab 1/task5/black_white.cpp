#include "black_white.h"

cv::Mat gradient(int imgSize, bool vertical)
{
    cv::Mat gr(imgSize, imgSize, CV_8UC1, cv::Scalar(0));
    for (int i = 0; i < gr.rows; i++)
        for (int j = 0; j < gr.cols; j++)
            gr.at<int8_t>(i, j) = vertical ? i : j;
    return gr;
}

cv::Mat chessbord(int imgSize, int blockSize)
{
    cv::Mat cb(imgSize, imgSize, CV_8UC1, cv::Scalar(0));
    for (int i = 0; i < imgSize; i = i + blockSize)
        for (int j = (i % (blockSize * 2) == 0) ? 0 : blockSize; j < imgSize; j = j + blockSize + blockSize)
            cb(cv::Rect(i, j, blockSize, blockSize)).setTo(cv::Scalar::all(255));
    return cb;
}