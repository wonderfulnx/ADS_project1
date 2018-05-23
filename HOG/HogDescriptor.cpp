//
// Created by naxin on 18-5-23.
//

#include "HogDescriptor.h"
#include <math.h>

HogDescriptor::HogDescriptor() {
    
}

HogDescriptor::~HogDescriptor() {

}

void HogDescriptor::readImage(string imageName) {
    image = imread(imageName, 1);
    return;
}

vector<int> HogDescriptor::getHogFeature(){
    makeGray();
    gammaTrans(2);
    //getGradient();

    int cell_width = 8;
    int cell_block_num = 9;
    int cell_i_num = image.rows/cell_width;
    int cell_j_num = image.cols/cell_width;
    vector<int> hogFeatrure(cell_i_num*cell_j_num*cell_block_num);

    int m = 0;
    int* cell_feature = new int[cell_block_num];

    for (int i = 0; i < cell_i_num; i++)
        for (int j = 0; j < cell_j_num; j++) {
            cellBin(i,j,cell_width,cell_block_num,cell_feature);
            for (int k = 0; k < cell_block_num; k++) {
                hogFeatrure[m] = cell_feature[k];
                m++;
            }
        }

    for (int i = 0; i < cell_i_num*cell_j_num*cell_block_num; i++) {
        if ((i % (2 * 2 * 9)) == 0)
            cout << endl << "--------------------------" << endl;
        else if (i % 9 == 0)
            cout << endl;
        cout << hogFeatrure[i] << " ";
    }
    cout << "feature size is:" << endl << hogFeatrure.size() << endl;

    return hogFeatrure;
}

//use the opencv function to make the image gray
void HogDescriptor::makeGray() {
    Mat imageGray;
    cvtColor(image,imageGray,CV_RGB2GRAY);
    image = imageGray;
    return;
}

void HogDescriptor::gammaTrans(float gamma) {
    unsigned char* imgSrc = image.data;
//    Mat imageGamma(image.rows, image.cols, image.type());
//    unsigned char* imgDst = imageGamma.data;
    unsigned char gammaTransTable[256];

    for (int i = 0; i < 256; i++){
        gammaTransTable[i] = (unsigned char)(pow(((float)i/255.0), gamma) * 255);
    }

    for (int i = 0; i < image.rows * image.cols; i++)
        imgSrc[i] = gammaTransTable[imgSrc[i]];

//    imshow("orgin", image);
//    imshow("gamma", imageGamma);

    return;
}

void HogDescriptor::getGradient() {
    unsigned char* imgSrc = image.data;
    Mat imagegre(image.rows, image.cols, image.type());

    //make the edge 0
    for (int i = 0; i < image.rows; i++) {
        imagegre.at<uchar>(i, 0) = 0;
        imagegre.at<uchar>(i, image.cols - 1) = 0;
    }
    for (int j = 0; j < image.cols; j++) {
        imagegre.at<uchar>(0, j) = 0;
        imagegre.at<uchar>(image.rows - 1, j) = 0;
    }

    int GreX, GreY;

    //compute the gradient
    for (int i = 1; i < image.rows; i++)
        for (int j = 1; j < image.cols; j++){
            GreX = image.at<uchar>(i, j + 1) - image.at<uchar>(i, j - 1);
            GreY = image.at<uchar>(i + 1, j) - image.at<uchar>(i - 1, j);

        }

    return;
}

void HogDescriptor::cellBin(int cell_i, int cell_j, int cell_width, int cellBlockNum, int* bin) {
    for (int i = 0; i < cellBlockNum; i++)
        bin[i] = 0;

    pair<int, int> gra;
    for (int i = cell_i; i < cell_i + cell_width && i < image.rows; i++)
        for (int j = cell_j; j < cell_j + cell_width && j < image.cols; j++){
            gra = gradientOf(i, j);
            bin[gra.second/20] += gra.first;
        }

    return;
}

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

