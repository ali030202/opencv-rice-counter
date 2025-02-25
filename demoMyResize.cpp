#include <iostream>
#include <opencv2/opencv.hpp>
/*
demoMyResize 图像旋转缩放
编程实现图像旋转缩放，并与opencv自带resize进行对比
*/
using namespace std;
using namespace cv;

int main() {
    // 读取原始图像
    Mat img = imread("img_A.png");

    // Display original and transformed images
    imshow("Original Image", img);

    // 缩放图像（不使用resize函数）
    double scale_factor = 0.9;
    // 创建一个与原始图像大小相应的空白图像
    Mat scaled_img = Mat::zeros(cvRound(img.rows * scale_factor), cvRound(img.cols * scale_factor), img.type());
    // 遍历新图像的像素
    for (int i = 0; i < scaled_img.rows; i++) {
        for (int j = 0; j < scaled_img.cols; j++) {
            // 计算原始图像中对应像素的坐标
            int x = cvRound(i / scale_factor); // 按比例计算行坐标
            int y = cvRound(j / scale_factor); // 按比例计算列坐标
            // 如果计算出的坐标在原始图像范围内，则将原始图像中的像素赋值给新图像
            if (x >= 0 && x < img.rows && y >= 0 && y < img.cols) {
                scaled_img.at<Vec3b>(i, j) = img.at<Vec3b>(x, y); // 赋值像素值
            }
        }
    }
    // 计算旋转后的图像大小
    double angle = 45.0;
    double radians = angle * CV_PI / 180.0; // 角度转弧度
    double cos_theta = cos(radians); // 计算旋转角的余弦值
    double sin_theta = sin(radians); // 计算旋转角的正弦值
    int new_width = cvRound(img.cols * scale_factor); // 缩放后的图像宽度
    int new_height = cvRound(img.rows * scale_factor); // 缩放后的图像高度
    int new_width_rotated = cvRound(abs(new_width * cos_theta) + abs(new_height * sin_theta)); // 旋转后的宽度
    int new_height_rotated = cvRound(abs(new_height * cos_theta) + abs(new_width * sin_theta)); // 旋转后的高度
    // 计算旋转矩阵
    Point2f center(scaled_img.cols / 2.0, scaled_img.rows / 2.0); // 计算缩放后图像的中心点
    Mat rot_mat = getRotationMatrix2D(center, angle, 1.0); // 获取旋转矩阵
    // 执行旋转（不使用resize函数）
    Mat rotated_img = Mat::zeros(new_height_rotated, new_width_rotated, scaled_img.type()); // 创建旋转后的图像
    warpAffine(scaled_img, rotated_img, rot_mat, rotated_img.size()); // 执行旋转
    // 显示结果（不使用resize函数）
    imshow("Rotated and Scaled Image (No Resize)", rotated_img);
    // 使用resize函数进行缩放和旋转
    Mat resized_img;
    resize(img, resized_img, Size(), scale_factor, scale_factor); // 缩放图像
    Mat rotated_resized_img;
    Size new_size_rotated_resized(resized_img.cols, resized_img.rows); // 新的大小
    warpAffine(resized_img, rotated_resized_img, rot_mat, new_size_rotated_resized); // 执行旋转
    // 显示结果（使用resize函数）
    imshow("Rotated and Scaled Image (With Resize)", rotated_resized_img);
    waitKey(0);
    return 0;
}
