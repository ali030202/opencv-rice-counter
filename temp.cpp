#include<iostream> 
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
using namespace cv;
using namespace std;


/** @function main */
int main(int argc, char** argv)
{
    Mat src, src_gray;

    /// Read the image
    src = imread("circle.bmp");

    if (!src.data)
    {
        return -1;
    }

    /// Convert it to gray
    cvtColor(src, src_gray, CV_BGR2GRAY);

    /// Reduce the noise so we avoid false circle detection
    GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

    vector<Vec3f> circles;

    /// Apply the Hough Transform to find the circles
    HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 100, 0, 0);

    Size dsize = Size(src.cols, src.rows);
    Mat img_output = Mat(dsize, CV_8UC3, Scalar::all(0));

    /// Draw the circles detected
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // circle outline
        circle(img_output, center, radius, Scalar(0, 0, 255),-1,8,0);
    }

    /// Show your results
    imshow("½á¹û", img_output);
    imshow("Ô­Í¼", src);

    waitKey(0);
    return 0;
}