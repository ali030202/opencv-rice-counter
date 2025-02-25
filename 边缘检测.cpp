#include<iostream> 
#include <vector>
#include <opencv2\imgproc\types_c.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
/// ȫ�ֱ���
Mat src, src_gray;
Mat dst, detected_edges;
int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio1 = 3;
int kernel_size = 3;
void CannyThreshold(int, void*)
{
	/// ʹ�� 3x3�ں˽���
	blur(src_gray, detected_edges, Size(3, 3));
	/// ����Canny����
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio1, kernel_size);
	/// ʹ�� Canny���������Ե��Ϊ������ʾԭͼ��
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);
	imshow("img", dst);
}
/** @���� main */
int main()
{
	/// װ��ͼ��
	src =imread("circle.bmp");imshow("img1", src);
	if (!src.data)
	{printf("����");}
	/// ������srcͬ���ͺʹ�С�ľ���(dst)
	dst.create(src.size(), src.type());
	/// ԭͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor(src, src_gray, CV_BGR2GRAY);
	/// ������ʾ����
	namedWindow("img", WINDOW_AUTOSIZE);
	/// ��ʾͼ��
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
	/// �ȴ��û���Ӧ
	waitKey(0);

}