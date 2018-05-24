//
// Created by naxin on 18-5-24.
//

#include "ColorMoment.h"
#include <math.h>

ColorMoment::ColorMoment() {

}

ColorMoment::~ColorMoment() {

}

void ColorMoment::readImage(string imageName) {
    image = imread(imageName, 1);
    return;
}

vector<double> ColorMoment::getCMFeature() {
    vector<double> feature(9,0);

    for (int i = 0; i < 3; i++){
        double miu = cal1moment(i);
        feature[i*3] = miu;
        feature[i*3+1] = cal2moment(miu, i);
        feature[i*3+2] = cal3moment(miu, i);
    }

    return feature;
}

double ColorMoment::cal1moment(int k) {
    double sum = 0;
    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++) {
            sum += image.at<Vec3b>(i,j)[k];
        }
    double result = sum / (image.rows * image.cols);
    return result;
}

double ColorMoment::cal2moment(double miu, int k) {
    double sum = 0;
    double temp;
    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++) {
            temp = image.at<Vec3b>(i,j)[k] - miu;
            sum += temp * temp;
        }
    double result = pow(sum / (image.rows * image.cols),0.5);

    return result;
}

double ColorMoment::cal3moment(double miu, int k) {
    double sum = 0;
    double temp;
    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++) {
            temp = abs(image.at<Vec3b>(i,j)[k] - miu);
            sum += temp * temp * temp;
        }
//    cout << sum << endl;
    double result = pow(sum / (image.rows * image.cols),1.0/3);
    return result;
}
