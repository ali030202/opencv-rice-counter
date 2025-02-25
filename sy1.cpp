#include <opencv2/opencv.hpp>  
#include <iostream>  
#include <vector>  
using namespace cv; // 使用cv命名空间，从而不需要cv::前缀  
using namespace std; // 使用std命名空间，从而不需要std::前缀  
int main() {
    // 1. 读取图像    
    Mat img = imread("rice.tif", IMREAD_GRAYSCALE);
    if (img.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }
    // 2. 预处理（这里只展示了滤波和阈值处理）    
    Mat blurred;
    GaussianBlur(img, blurred, Size(5, 5), 0);
    Mat thresholded;
    adaptiveThreshold(blurred, thresholded, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    imshow("阈值", thresholded);  //成功划分  
    // 3. 形态学操作（这里只展示了腐蚀和膨胀）    
    Mat eroded, dilated;
    erode(thresholded, eroded, Mat(), Point(-1, -1), 2);
    imshow("腐蚀", eroded);
    dilate(eroded, dilated, Mat(), Point(-1, -1), 2);
    imshow("膨胀", dilated);
    // 4. 查找轮廓    
    vector<vector<Point>> contours;
    findContours(dilated, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    imshow("轮廓", dilated);

    // 5. 过滤轮廓并计算大米数量    
    int riceCount = 0;
    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area > 110) { // 根据实际图像调整阈值    
            riceCount++;
        }
    }

    // 6. 输出结果    
    cout << "Number of rices: " << riceCount << endl;

    // 显示图像（可选）    
    imshow("Original Image", img);
    imshow("Processed Image", dilated);
    waitKey(0);
    destroyAllWindows();

    return 0;
}