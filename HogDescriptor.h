//
// Created by naxin on 18-5-23.
//

#ifndef PRO_1_1_HOGDESCRIPTOR_H
#define PRO_1_1_HOGDESCRIPTOR_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

class HogDescriptor {
private:
    Mat image;

public:
    HogDescriptor();
    ~HogDescriptor();

    void readImage(string imageName);
    vector<int> getHogFeature();

private:
    void makeGray();
    void gammaTrans(float gamma);
    void getGradient();

    void cellBin(int cell_i, int cell_j, int cell_width, int cellBlockNum, int* bin);

    inline pair<int, int> gradientOf(int i, int j);
};


#endif //PRO_1_1_HOGDESCRIPTOR_H
