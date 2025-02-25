#include<iostream> 
#include <vector>
#include <opencv2\imgproc\types_c.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
/// 全局变量
Mat src, src_gray;
Mat dst, detected_edges;
int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio1 = 3;
int kernel_size = 3;
void CannyThreshold(int, void*)
{
	/// 使用 3x3内核降噪
	blur(src_gray, detected_edges, Size(3, 3));
	/// 运行Canny算子
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio1, kernel_size);
	/// 使用 Canny算子输出边缘作为掩码显示原图像
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);
	imshow("img", dst);
}
/** @函数 main */
int main()
{
	/// 装载图像
	src =imread("circle.bmp");imshow("img1", src);
	if (!src.data)
	{printf("错误");}
	/// 创建与src同类型和大小的矩阵(dst)
	dst.create(src.size(), src.type());
	/// 原图像转换为灰度图像
	cvtColor(src, src_gray, CV_BGR2GRAY);
	/// 创建显示窗口
	namedWindow("img", WINDOW_AUTOSIZE);
	/// 显示图像
	CannyThreshold(0, 0);
	/// Reduce the noise so we avoid false circle detection
	vector<Vec3f> circles;
	/// Apply the Hough Transform to find the circles
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 100, 0, 0);
	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 300, (255, 0, 0), 300);
		// circle outline
		circle(src, center, radius, (0, 0, 255), 8);
	}
	/// Show your results
	namedWindow("Hough Circle Transform Demo", WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);
	/// 等待用户反应
	waitKey(0);

}