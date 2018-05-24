//
// Created by naxin on 18-5-24.
//

#ifndef PRO1_3_COLORHISTOGRAM_H
#define PRO1_3_COLORHISTOGRAM_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ColorHistogram {
private:
    Mat image;
    int unitDimension;

public:
    ColorHistogram(int unitDi);
    ~ColorHistogram();

    void readImage(string imageName);
    vector<int> getCHFeature();
};


#endif //PRO1_3_COLORHISTOGRAM_H
