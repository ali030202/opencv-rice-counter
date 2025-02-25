#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//定义高斯滤波函数
void myfilter(int filter_size, Mat& image_input, Mat& image_output);
int main()
{
    Mat image, image_gray, image_output, image_output2;   //定义输入图像，灰度图像，输出图像
    image = imread("salt-0.1.bmp");  //读取图像；
    if (image.empty())
    {
        cout << "读取错误" << endl;
        return -1;
    }
    imshow("原图", image);
    cvtColor(image, image_gray, COLOR_BGR2GRAY);
    //opencv自带高斯滤波函数
    int a = 7;
    GaussianBlur(image_gray, image_output, Size(a, a), 2, 2);
    imshow("opnecv自带函数", image_output);

    //自编函数
    myfilter(a, image_gray, image_output2);
    imshow("自编函数", image_output2);

    waitKey(0);  //暂停，保持图像显示，等待按键结束
    return 0;
}
void myfilter(int filter_size, Mat& image_input, Mat& image_output) //图像边缘未处理
{
    image_output = image_input.clone();
    int k = (filter_size - 1) / 2;
    for (int i = k; i < (image_input.rows - k); i++)
    {
        for (int j = k; j < (image_input.cols - k); j++)
        {
            double sum = 0.0;
            double sum1 = 0.0;
            double sigma = 7; //可调
            double g;
            for (int m = -k; m < k + 1; m++)
            {
                for (int n = -k; n < k + 1; n++)
                {
                    g = exp(-(m * m + n * n) / (2 * sigma * sigma));
                    sum = sum + g * image_input.at<uchar>(i + m, j + n);
                    sum1 = sum1 + g;
                }
            }
            image_output.at<uchar>(i, j) = (int)round(sum / sum1);

        }
    }
}