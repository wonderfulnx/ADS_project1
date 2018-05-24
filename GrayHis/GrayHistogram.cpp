//
// Created by naxin on 18-5-25.
//

#include "GrayHistogram.h"

GrayHistogram::GrayHistogram() {

}

GrayHistogram::~GrayHistogram() {

}

void GrayHistogram::readImage(string imageName) {
    image = imread(imageName, 1);
    return;
}

vector<int> GrayHistogram::getGHFeature() {
    Mat imageGray;
    cvtColor(image,imageGray,CV_RGB2GRAY);

    vector<int> feature(256,0);

    unsigned char* imgGray = imageGray.data;
    for (int i = 0; i < imageGray.rows * imageGray.cols; i++){
        if (imgGray[i] >= 256)
            throw runtime_error("error in gray num");
        feature[imgGray[i]]++;
    }

    Normalize(10000, feature);
    return feature;
}

void GrayHistogram::Normalize(int targetSize, vector<int> &vec) {
    int currentSize = 0;
    for_each(vec.begin(), vec.end(), [&](int item){
        currentSize += item;
        if (currentSize < 0){
            throw runtime_error("over flow!");
        }
    });

    for (int i = 0; i < vec.size(); i++){
        vec[i] = vec[i]*targetSize/currentSize;
    }

    return;
}
