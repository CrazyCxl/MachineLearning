#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <iostream>
#include <vector>
#include "kdtree.h"

using namespace std;
using namespace KDTreeSpace;

class KNeighborsClassifier
{
public:
    KNeighborsClassifier();
    bool train(const string &file_str);
    bool train(const vector<vector<double>> &x_s,const vector<double> &Y);

    vector<bool> predict(const vector<vector<double> > &X_t,size_t k = 3);
private:
    void featureScaling(vector<vector<double>> &x_s);
    KDTree<double> kdtree;

    vector<double> xAvg;
    vector<double> xVariance;
};

#endif // LINEARREGRESSION_H
