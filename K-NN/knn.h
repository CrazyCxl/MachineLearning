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

    vector<bool> predict(const vector<vector<double> > &X_t);
private:
    KDTree<double> kdtree;
};

#endif // LINEARREGRESSION_H
