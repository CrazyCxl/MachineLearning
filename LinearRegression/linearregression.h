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
    bool train(const vector<double> &X,const vector<double> &Y);
    bool train(const vector<vector<double>> &x_s,const vector<double> &Y);
    void setStep(const double &step){this->step = step;}

    vector<double> predict(const vector<vector<double> > &X_t);
private:
    bool gradientDescent(const vector<vector<double>> &x_s,const vector<double> &Y);
    double func(const vector<double> &X);

    double step = 0.01;
    double minDTheta = 1e-5;//1*(10的-5次方)即0.00001

    vector<double> thetas;
};

#endif // LINEARREGRESSION_H
