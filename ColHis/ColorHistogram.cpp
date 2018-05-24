//
// Created by naxin on 18-5-24.
//

#include "ColorHistogram.h"

//unit dimension means to split the 256 to n parts
//the final dimension is (unitDimension)**3
ColorHistogram::ColorHistogram(int unitDi) {
    unitDimension = unitDi;
}

ColorHistogram::~ColorHistogram() {

}

void ColorHistogram::readImage(string imageName) {
    image = imread(imageName, 1);
    return;
}

vector<int> ColorHistogram::getCHFeature() {
    if ((256 % unitDimension) != 0){
        throw runtime_error("unit dimension number should be in 2**i, i in [1,8]");
    }

    int dimension = unitDimension * unitDimension * unitDimension;
    vector<int> feature(dimension,0);

    int segmentLength = 256 / unitDimension;

    int b,g,r;
    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++){
            b = image.at<Vec3b>(i,j)[0];
            g = image.at<Vec3b>(i,j)[1];
            r = image.at<Vec3b>(i,j)[2];
            feature[(b/segmentLength) + ((g / segmentLength) * unitDimension) +
                    ((r / segmentLength) * unitDimension * unitDimension)]++;
        }
    return feature;
}