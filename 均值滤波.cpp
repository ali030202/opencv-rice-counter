#include <iostream>
#include <opencv2/opencv.hpp>
/*
demoMyResize ͼ����ת����
���ʵ��ͼ����ת���ţ�����opencv�Դ�resize���жԱ�
*/
using namespace std;
using namespace cv;
// ConsoleApplication3.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// ��ֵ�˲��Ի���ֵ�˲�
void MeanFilter(Mat& src, Mat& dst, Size wsize) {
    // �ж�ԭͼ���Ƿ�Ϊ��
    if (src.empty()) {
        return;
    }
    //�жϾ����������Ϊ����
    if (wsize.height % 2 == 0 || wsize.width % 2 == 0) {
        fprintf(stderr, "Please enter odd size!");
        exit(-1);
    }
    int hh = (wsize.height - 1) / 2;
    int hw = (wsize.width - 1) / 2;
    Mat Newsrc;
    copyMakeBorder(src, Newsrc, hh, hh, hw, hw, BORDER_REFLECT_101);//�Ա�ԵΪ�ᣬ�Գ�
    dst = Mat::zeros(src.size(), src.type());

    //�ڶ��ַ�����ָ�뷽��
    // ��ͨ����ɫͼƬ����
    if (Newsrc.channels() == 3) {
        //int q = 0;//test
        // ����ÿ��ͨ���ĺ˵�������ƽ��ֵ,����0
        int sumR = 0, sumG = 0, sumB = 0;
        int averageR = 0, averageG = 0, averageB = 0;
        for (int i = hh; i < src.rows + hh; i++)
            for (int j = hw; j < src.cols + hw; j++) {

                for (int r = i - hh; r <= i + hh; r++) {
                    Vec3b* data_New = Newsrc.ptr<Vec3b>(r);
                    // ��˵�����
                    for (int k = j - hh; k <= j + hh; k++) {
                        sumR += data_New[k][0];
                        sumG += data_New[k][1];
                        sumB += data_New[k][2];
                    }
                }
                // ��ƽ����
                averageR = sumR / (wsize.area());
                averageG = sumG / (wsize.area());
                averageB = sumB / (wsize.area());
                // д��Ŀ��ͼ��
                Vec3b* dataDst = dst.ptr<Vec3b>(i - hh);
                dataDst[j - hw][0] = averageR;
                dataDst[j - hw][1] = averageG;
                dataDst[j - hw][2] = averageB;

                // �ܺͺ�ƽ������0
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
    imshow("ԭͼ", src);
    Mat dst2 = Mat::zeros(src.size(), src.type());
    MeanFilter(src, dst2, Size(5, 5));
    imshow("�Լ�д��", dst2);
    Mat dst1 = Mat::zeros(src.size(), src.type());
    blur(src, dst1, Size(5, 5));
    imshow("opencv�Դ���", dst1);
    waitKey(0);

    return 0;

}