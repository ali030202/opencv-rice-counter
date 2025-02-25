#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//�����˹�˲�����
void myfilter(int filter_size, Mat& image_input, Mat& image_output);
int main()
{
    Mat image, image_gray, image_output, image_output2;   //��������ͼ�񣬻Ҷ�ͼ�����ͼ��
    image = imread("salt-0.1.bmp");  //��ȡͼ��
    if (image.empty())
    {
        cout << "��ȡ����" << endl;
        return -1;
    }
    imshow("ԭͼ", image);
    cvtColor(image, image_gray, COLOR_BGR2GRAY);
    //opencv�Դ���˹�˲�����
    int a = 7;
    GaussianBlur(image_gray, image_output, Size(a, a), 2, 2);
    imshow("opnecv�Դ�����", image_output);

    //�Աຯ��
    myfilter(a, image_gray, image_output2);
    imshow("�Աຯ��", image_output2);

    waitKey(0);  //��ͣ������ͼ����ʾ���ȴ���������
    return 0;
}
void myfilter(int filter_size, Mat& image_input, Mat& image_output) //ͼ���Եδ����
{
    image_output = image_input.clone();
    int k = (filter_size - 1) / 2;
    for (int i = k; i < (image_input.rows - k); i++)
    {
        for (int j = k; j < (image_input.cols - k); j++)
        {
            double sum = 0.0;
            double sum1 = 0.0;
            double sigma = 7; //�ɵ�
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