#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <iostream>
#include <vector>

using namespace std;

class LinearRegression
{
public:
    LinearRegression();
    bool train(const string &file_str);
    bool train(const vector<double> X,const vector<double> Y);
    void setStep(const int &step){this->step = step;}

    vector<double> predict(vector<double> X_t);
private:
    void gradientDescent(const vector<double> &X,const vector<double> &Y);

    double step = 0.01;
    double minDTheta = 1e-5;

    double theta1 = 0,theta2 = 0;
};

#endif // LINEARREGRESSION_H
