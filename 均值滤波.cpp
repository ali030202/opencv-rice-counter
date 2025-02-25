#include <iostream>
#include <opencv2/opencv.hpp>
/*
demoMyResize 图像旋转缩放
编程实现图像旋转缩放，并与opencv自带resize进行对比
*/
using namespace std;
using namespace cv;
// ConsoleApplication3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// 均值滤波对话框值滤波
void MeanFilter(Mat& src, Mat& dst, Size wsize) {
    // 判断原图像是否为空
    if (src.empty()) {
        return;
    }
    //判断矩阵的行列数为奇数
    if (wsize.height % 2 == 0 || wsize.width % 2 == 0) {
        fprintf(stderr, "Please enter odd size!");
        exit(-1);
    }
    int hh = (wsize.height - 1) / 2;
    int hw = (wsize.width - 1) / 2;
    Mat Newsrc;
    copyMakeBorder(src, Newsrc, hh, hh, hw, hw, BORDER_REFLECT_101);//以边缘为轴，对称
    dst = Mat::zeros(src.size(), src.type());

    //第二种方法：指针方法
    // 三通道彩色图片处理
    if (Newsrc.channels() == 3) {
        //int q = 0;//test
        // 定义每个通道的核的总数和平均值,并置0
        int sumR = 0, sumG = 0, sumB = 0;
        int averageR = 0, averageG = 0, averageB = 0;
        for (int i = hh; i < src.rows + hh; i++)
            for (int j = hw; j < src.cols + hw; j++) {

                for (int r = i - hh; r <= i + hh; r++) {
                    Vec3b* data_New = Newsrc.ptr<Vec3b>(r);
                    // 求核的总数
                    for (int k = j - hh; k <= j + hh; k++) {
                        sumR += data_New[k][0];
                        sumG += data_New[k][1];
                        sumB += data_New[k][2];
                    }
                }
                // 求平均数
                averageR = sumR / (wsize.area());
                averageG = sumG / (wsize.area());
                averageB = sumB / (wsize.area());
                // 写入目标图像
                Vec3b* dataDst = dst.ptr<Vec3b>(i - hh);
                dataDst[j - hw][0] = averageR;
                dataDst[j - hw][1] = averageG;
                dataDst[j - hw][2] = averageB;

                // 总和和平均数置0
                sumR = 0; sumG = 0; sumB = 0;
                averageR = 0; averageG = 0; averageB = 0;
            }
    }

}
int main()
{
    Mat src = imread("salt-0.1.bmp");
    if (src.empty()) {
        return -1;
    }
    imshow("原图", src);
    Mat dst2 = Mat::zeros(src.size(), src.type());
    MeanFilter(src, dst2, Size(5, 5));
    imshow("自己写的", dst2);
    Mat dst1 = Mat::zeros(src.size(), src.type());
    blur(src, dst1, Size(5, 5));
    imshow("opencv自带的", dst1);
    waitKey(0);

    return 0;

}