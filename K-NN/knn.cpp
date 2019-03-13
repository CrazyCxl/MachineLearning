#include "knn.h"
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <sstream>

KNeighborsClassifier::KNeighborsClassifier()
{

}

bool KNeighborsClassifier::train(const string &file_str)
{
    ifstream file(file_str);
    if(file.is_open()){
        vector<vector<double>> Xs;
        vector<double> Y;
        while (!file.eof()){
            string line_str;
            char buff[1024] = {0};
            file.getline(buff,1024);
            line_str = string(buff);

            if(buff[0] < 48 || buff[0]>57) // is not number
                continue;

            vector<double> X;
            std::istringstream split(line_str);
            std::string each;
            while (std::getline(split, each, ',')){
                X.push_back(stod(each));
            }

            Y.push_back(*(X.end()-1));
            X.erase(X.end()-1);
            Xs.push_back(X);
        }
        featureScaling(Xs);
        train(Xs,Y);
    }else{
        return false;
    }

    return true;
}

bool KNeighborsClassifier::train(const vector<vector<double> > &x_s, const vector<double> &Y)
{
    if(x_s.size() != Y.size() || x_s.size() == 0){
        return false;
    }

    vector<int> Y_t;
    for (auto y = Y.begin();y != Y.end();y++) {
        Y_t.push_back(static_cast<int>(*y));
    }

    kdtree.feed(x_s,Y_t);
    kdtree.toDot("./kdtree.dot");

    return true;
}

vector<bool> KNeighborsClassifier::predict(const vector<vector<double>> &X_t, size_t k)
{
    vector<vector<double>> x_s = X_t;
    for (size_t i = 0;i<x_s.size();i++) {
        for(size_t j = 0;j<x_s[0].size();j++) {
            x_s[i][j] = (x_s[i][j] - xAvg[j])/xVariance[j];
        }
    }

    vector<bool> Y_t;
    for (size_t i =0;i<X_t.size();i++) {
        vector<Point<double>> points = kdtree.findAdjacentK(x_s[i],k);
        size_t true_size = KDTreeSpace::Point<double>::containsYsize(points,1);
        if(points.size() - true_size < true_size){
            Y_t.push_back(true);
        }else{
            Y_t.push_back(false);
        }
    }
    return Y_t;
}

void KNeighborsClassifier::featureScaling(vector<vector<double> > &x_s)
{
    xAvg.clear();
    xVariance.clear();

    for (size_t j = 0;j<x_s[0].size();j++) {
        double avg = x_s[0][j],varaince = 0;
        for(size_t i = 1;i<x_s.size();i++) {
            avg += x_s[i][j];
        }
        avg = avg / x_s.size();
        for(size_t i = 0;i<x_s.size();i++) {
            varaince += pow(x_s[i][j]-avg,2);
        }
        varaince = sqrt(varaince/x_s.size());
        xAvg.push_back(avg);
        xVariance.push_back(varaince);
    }

    for (size_t i = 0;i<x_s.size();i++) {
        for(size_t j = 0;j<x_s[0].size();j++) {
            x_s[i][j] = (x_s[i][j] - xAvg[j])/xVariance[j];
        }
    }
}
