//
// Created by naxin on 18-5-23.
//

#include "HogDescriptor.h"
#include <math.h>

HogDescriptor::HogDescriptor(int bolckNum, int cellWid, int maxDimen) {
    cell_block_num = bolckNum;
    cell_width = cellWid;
    maxDimension = maxDimen;
}

HogDescriptor::~HogDescriptor() {

}

void HogDescriptor::readImage(string imageName) {
    image = imread(imageName, 1);
    int maxSize = (maxDimension*cell_width*cell_width)/cell_block_num;
    if (image.rows * image.cols > maxSize){
        Mat tempImage;

        double t = pow((double)maxSize/(image.rows * image.cols), 0.5);
        resize(image, tempImage, Size(image.cols * t, image.rows * t),0,0,INTER_LINEAR);
        image = tempImage;

    }
    return;
}

vector<int> HogDescriptor::getHogFeature(){
    makeGray();
    gammaTrans(2);

    int cell_i_num = image.rows/cell_width;
    int cell_j_num = image.cols/cell_width;
    vector<int> hogFeature(maxDimension,0);

    //vector<int> hogFeature(cell_i_num*cell_j_num*cell_block_num);

    int m = 0;
    int* cell_feature = new int[cell_block_num];

    for (int i = 0; i < cell_i_num; i++)
        for (int j = 0; j < cell_j_num; j++) {
            cellBin(i * cell_width,j * cell_width,cell_width,cell_block_num,cell_feature);
            for (int k = 0; k < cell_block_num; k++) {
                hogFeature[m] = cell_feature[k];
                if (m > hogFeature.size())
                    throw runtime_error("size not fit");
                m++;
            }
        }

    delete cell_feature;

    //cout << endl << "feature size is:" << endl << hogFeature.size() << endl;
    Normalize(10000, hogFeature);

    return hogFeature;
}

//use the opencv function to make the image gray
void HogDescriptor::makeGray() {
    Mat imageGray;
    cvtColor(image,imageGray,CV_RGB2GRAY);
    image = imageGray;
    return;
}

//对图像进行gamma校正
void HogDescriptor::gammaTrans(float gamma) {
    unsigned char* imgSrc = image.data;
    unsigned char gammaTransTable[256];

    for (int i = 0; i < 256; i++){
        gammaTransTable[i] = (unsigned char)(pow(((float)i/255.0), gamma) * 255);
    }

    for (int i = 0; i < image.rows * image.cols; i++)
        imgSrc[i] = gammaTransTable[imgSrc[i]];

    return;
}

//求每一个cell的feature
//cell_i是cell左上角的坐标
void HogDescriptor::cellBin(int cell_i, int cell_j, int cell_width, int cellBlockNum, int* bin) {
    for (int i = 0; i < cellBlockNum; i++)
        bin[i] = 0;

    pair<int, int> gra;
    int unitSize = 180 / cellBlockNum;
    for (int i = cell_i; (i < cell_i + cell_width) && (i < image.rows); i++)
        for (int j = cell_j; (j < cell_j + cell_width) && (j < image.cols); j++){
            gra = gradientOf(i, j);
            bin[gra.second/unitSize] += gra.first;
        }

    return;
}

//获取某个点的梯度
inline pair<int, int> HogDescriptor::gradientOf(int i, int j) {
    if (i == 0 || j == 0 || i == image.rows || j == image.cols)
        return pair<int, int>(0,0);
    int graX , graY;

    graX = image.at<uchar>(i, j + 1) - image.at<uchar>(i, j - 1);
    graY = image.at<uchar>(i + 1, j) - image.at<uchar>(i - 1, j);
    int gra, angle;
    gra = pow(graX * graX + graY * graY, 0.5);

    //get angle
    angle = 0;
    if (graX == 0){
        if (graY > 0)
            angle = 90;
        else if (graY < 0)
            angle = -90;
    }
    else if (graY == 0){
        if (graX > 0)
            angle = 0;
        else if (graX < 0)
            angle = 180;
    }
    else {
        angle = atan(graY/graX)*180/3.14;
    }

    if (angle < 0)
        angle += 180;

    if (angle > 180)
        throw runtime_error("error in angle");
    else if (angle == 180)
        angle = 179;

    return pair<int, int>(gra, angle);
}

void HogDescriptor::Normalize(int targetSize, vector<int> &vec) {
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
