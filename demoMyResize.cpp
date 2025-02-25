#include <iostream>
#include <opencv2/opencv.hpp>
/*
demoMyResize ͼ����ת����
���ʵ��ͼ����ת���ţ�����opencv�Դ�resize���жԱ�
*/
using namespace std;
using namespace cv;

int main() {
    // ��ȡԭʼͼ��
    Mat img = imread("img_A.png");

    // Display original and transformed images
    imshow("Original Image", img);

    // ����ͼ�񣨲�ʹ��resize������
    double scale_factor = 0.9;
    // ����һ����ԭʼͼ���С��Ӧ�Ŀհ�ͼ��
    Mat scaled_img = Mat::zeros(cvRound(img.rows * scale_factor), cvRound(img.cols * scale_factor), img.type());
    // ������ͼ�������
    for (int i = 0; i < scaled_img.rows; i++) {
        for (int j = 0; j < scaled_img.cols; j++) {
            // ����ԭʼͼ���ж�Ӧ���ص�����
            int x = cvRound(i / scale_factor); // ����������������
            int y = cvRound(j / scale_factor); // ����������������
            // ����������������ԭʼͼ��Χ�ڣ���ԭʼͼ���е����ظ�ֵ����ͼ��
            if (x >= 0 && x < img.rows && y >= 0 && y < img.cols) {
                scaled_img.at<Vec3b>(i, j) = img.at<Vec3b>(x, y); // ��ֵ����ֵ
            }
        }
    }
    // ������ת���ͼ���С
    double angle = 45.0;
    double radians = angle * CV_PI / 180.0; // �Ƕ�ת����
    double cos_theta = cos(radians); // ������ת�ǵ�����ֵ
    double sin_theta = sin(radians); // ������ת�ǵ�����ֵ
    int new_width = cvRound(img.cols * scale_factor); // ���ź��ͼ����
    int new_height = cvRound(img.rows * scale_factor); // ���ź��ͼ��߶�
    int new_width_rotated = cvRound(abs(new_width * cos_theta) + abs(new_height * sin_theta)); // ��ת��Ŀ��
    int new_height_rotated = cvRound(abs(new_height * cos_theta) + abs(new_width * sin_theta)); // ��ת��ĸ߶�
    // ������ת����
    Point2f center(scaled_img.cols / 2.0, scaled_img.rows / 2.0); // �������ź�ͼ������ĵ�
    Mat rot_mat = getRotationMatrix2D(center, angle, 1.0); // ��ȡ��ת����
    // ִ����ת����ʹ��resize������
    Mat rotated_img = Mat::zeros(new_height_rotated, new_width_rotated, scaled_img.type()); // ������ת���ͼ��
    warpAffine(scaled_img, rotated_img, rot_mat, rotated_img.size()); // ִ����ת
    // ��ʾ�������ʹ��resize������
    imshow("Rotated and Scaled Image (No Resize)", rotated_img);
    // ʹ��resize�����������ź���ת
    Mat resized_img;
    resize(img, resized_img, Size(), scale_factor, scale_factor); // ����ͼ��
    Mat rotated_resized_img;
    Size new_size_rotated_resized(resized_img.cols, resized_img.rows); // �µĴ�С
    warpAffine(resized_img, rotated_resized_img, rot_mat, new_size_rotated_resized); // ִ����ת
    // ��ʾ�����ʹ��resize������
    imshow("Rotated and Scaled Image (With Resize)", rotated_resized_img);
    waitKey(0);
    return 0;
}
