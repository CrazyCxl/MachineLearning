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

    vector<double> predict(const vector<vector<double> > &X_t);
    void setMinDTheta(double value){minDTheta = value;}
    void setBaseStep(double value){baseStep = value;}
private:
    bool gradientDescent(const vector<vector<double>> &x_s,const vector<double> &Y);
    bool stepIsTooLarge(double a,double b);
    void changeValue(double &x,bool up);
    bool stepIsTooSmall(double a,double b);
    int getNum(double num,int filt = 10);
    double func(const vector<double> &X);

    double minDTheta = 1e-5;//1*(10的-5次方)即0.00001

    vector<double> thetas;
    vector<double> d_thetas;
    vector<double> steps;

    vector<double> x_avgs;
    vector<double> x_mins;
    vector<double> x_maxs;
    double baseStep = 0.01;
};

#endif // LINEARREGRESSION_H
