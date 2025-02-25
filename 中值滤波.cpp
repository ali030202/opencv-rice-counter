#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void myfilter(int filter_size, Mat& image_input, Mat& image_output);
int mysort(Mat& sortarray, int filter_size);
int main()
{
    Mat image, image_gray, image_output, image_output2;   //定义输入图像，灰度图像，输出图像
    image = imread("salt-0.05.bmp");  //读取图像；
    if (image.empty())
    {
        cout << "读取错误" << endl;
        return -1;
    }
    imshow("image", image);
    cvtColor(image, image_gray, COLOR_BGR2GRAY);
    //opencv自带滤波函数
    int a = 7;
    medianBlur(image_gray, image_output, a);
    imshow("opencv自带函数", image_output);
    //自编函数
    myfilter(a, image_gray, image_output2);
    imshow("自编函数", image_output2);
    waitKey(0);  //暂停，保持图像显示，等待按键结束
    return 0;
}
void myfilter(int filter_size, Mat& image_input, Mat& image_output) //图像边缘未处理
{
    image_output = image_input.clone();
    Mat sortarray(1, filter_size * filter_size, CV_8U);
    int k = (filter_size - 1) / 2;

    for (int i = k; i < (image_input.rows - k); i++)
    {
        for (int j = k; j < (image_input.cols - k); j++)
        {
            int h = 0;
            for (int m = -k; m < k + 1; m++)
            {
                for (int n = -k; n < k + 1; n++)
                {
                    sortarray.at<uchar>(h) = image_input.at<uchar>(i + m, j + n);
                    h++;
                }
            }

            image_output.at<uchar>(i, j) = mysort(sortarray, filter_size * filter_size);

        }
    }
}
int mysort(Mat& sortarray, int filter_size)  //找中值
{
    int exchange;
    int m;
    for (int i = 1; i <= filter_size - 1; i++)
    {
        for (int j = 1; j <= filter_size - i; j++)
        {
            if (sortarray.at<uchar>(j - 1) > sortarray.at<uchar>(j))
            {
                exchange = sortarray.at<uchar>(j - 1);
                sortarray.at<uchar>(j - 1) = sortarray.at<uchar>(j);
                sortarray.at<uchar>(j) = exchange;
            }
        }

    }
    return m = sortarray.at<uchar>((filter_size + 1) / 2);
}