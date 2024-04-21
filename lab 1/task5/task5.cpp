#include "headers.h"
#include "black_white.h"

int main(int argc, char **argv)
{
    unsigned int imgSize = 256;
    cv::imshow(" Vertical ", gradient(imgSize, true));
    cv::imshow(" Horizontal ", gradient(imgSize, true));
    cv::waitKey(0);

    imgSize = 300;
    imshow("Chessboard-20", chessbord(imgSize, 20));
    imshow("Chessboard-50", chessbord(imgSize, 50));
    cv::waitKey(0);
    return 0;
}