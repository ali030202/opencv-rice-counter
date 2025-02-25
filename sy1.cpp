#include <opencv2/opencv.hpp>  
#include <iostream>  
#include <vector>  
using namespace cv; // ʹ��cv�����ռ䣬�Ӷ�����Ҫcv::ǰ׺  
using namespace std; // ʹ��std�����ռ䣬�Ӷ�����Ҫstd::ǰ׺  
int main() {
    // 1. ��ȡͼ��    
    Mat img = imread("rice.tif", IMREAD_GRAYSCALE);
    if (img.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }
    // 2. Ԥ��������ֻչʾ���˲�����ֵ����    
    Mat blurred;
    GaussianBlur(img, blurred, Size(5, 5), 0);
    Mat thresholded;
    adaptiveThreshold(blurred, thresholded, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    imshow("��ֵ", thresholded);  //�ɹ�����  
    // 3. ��̬ѧ����������ֻչʾ�˸�ʴ�����ͣ�    
    Mat eroded, dilated;
    erode(thresholded, eroded, Mat(), Point(-1, -1), 2);
    imshow("��ʴ", eroded);
    dilate(eroded, dilated, Mat(), Point(-1, -1), 2);
    imshow("����", dilated);
    // 4. ��������    
    vector<vector<Point>> contours;
    findContours(dilated, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    imshow("����", dilated);

    // 5. ���������������������    
    int riceCount = 0;
    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area > 110) { // ����ʵ��ͼ�������ֵ    
            riceCount++;
        }
    }

    // 6. ������    
    cout << "Number of rices: " << riceCount << endl;

    // ��ʾͼ�񣨿�ѡ��    
    imshow("Original Image", img);
    imshow("Processed Image", dilated);
    waitKey(0);
    destroyAllWindows();

    return 0;
}