//
// Created by naxin on 18-5-24.
//

#ifndef PRO1_2_COLORMOMENT_H
#define PRO1_2_COLORMOMENT_H

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ColorMoment {
private:
    Mat image;

public:
    ColorMoment();

    ~ColorMoment();

    void readImage(string imageName);
    vector<double> getCMFeature();

private:
    //计算第i个通道的n阶矩
    double cal1moment(int k);
    double cal2moment(double miu, int k);
    double cal3moment(double miu, int k);
};


#endif //PRO1_2_COLORMOMENT_H
