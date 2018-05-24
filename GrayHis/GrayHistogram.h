//
// Created by naxin on 18-5-25.
//

#ifndef PRO1_4_GRAYHISTOGRAM_H
#define PRO1_4_GRAYHISTOGRAM_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class GrayHistogram {
private:
    Mat image;

public:
    GrayHistogram();
    ~GrayHistogram();

    void readImage(string imageName);
    vector<int> getGHFeature();

private:
    void Normalize(int targetSize, vector<int>& vec);
};


#endif //PRO1_4_GRAYHISTOGRAM_H
