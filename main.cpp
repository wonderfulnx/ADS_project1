#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "HogDescriptor.h"
#include <fstream>

using namespace std;
using namespace cv;

int main() {
    string filename;
    //cin >> filename;
    filename = "/home/naxin/Documents/THU/ADS/Tests/images.txt";
    ifstream infile(filename);
    HogDescriptor hog(9,16,350);

    int max = 0;
    string max_name;
    int index = 0;
    while (!infile.eof()){
        string temp;
        getline(infile, temp);
        if (temp.empty()) continue;
        hog.readImage(temp);
        auto s = hog.getHogFeature();

        cout << "done " << index << ": ";

        int tempSize = 0;
        for_each(s.begin(), s.end(), [&](int a){
            tempSize += a;
            cout << a << " ";
        });
        cout << endl;
        cout << tempSize << endl;

        index++;
    }

//    string filename;
//    filename = "/home/naxin/Documents/THU/ADS/DS&Alg-Project1-Release/data/image/n07897438_3120.JPEG";
//
//    HogDescriptor hog(9,16,350);
//
//    hog.readImage(filename);
//    auto s = hog.getHogFeature();
//    int tempSize = 0;
//    for_each(s.begin(), s.end(), [&](int a){
//        tempSize += a;
//        cout << a << " ";
//    });
//    cout << endl;
//    cout << tempSize << endl;


    return 0;
}


//    string filename;
//    Mat imageMat;
//    imageMat = imread("/home/naxin/Desktop/n01613177_3.JPEG", 1);//图像大小98 * 130
//    cout << imageMat.size[0] << " " << imageMat.size[1] << endl;
//    if (!imageMat.data) {
//        cout << "No image data" << endl;
//        return -1;
//    }
//    HOGDescriptor *hog = new HOGDescriptor(cvSize(64, 64), cvSize(32, 32), cvSize(8, 8), cvSize(16, 16), 9);
//    vector<float> descriptors;
//    hog->compute(imageMat, descriptors, Size(16, 16), Size(0, 0));
//    cout << "descriptors.size = " << descriptors.size() << endl;//输出hog特征描绘子的维度
