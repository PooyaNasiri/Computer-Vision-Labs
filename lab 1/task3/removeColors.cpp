#include "removeColors.h"

void RemoveColors(cv::Mat img)
{
    if (img.channels() == 3)
    {
        cv::Mat img1, img2, img3;
        std::vector<cv::Mat> channels(3);
        split(img, channels);
        channels[0] = 0;
        merge(channels, img1);
        cv::imshow(" No Blue ", img1);

        split(img, channels);
        channels[1] = 0;
        merge(channels, img2);
        cv::imshow(" No Green ", img2);

        split(img, channels);
        channels[2] = 0;
        merge(channels, img3);
        cv::imshow(" No Red ", img3);
    }
}