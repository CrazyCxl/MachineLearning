#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <iostream>
#include <vector>

using namespace std;

class LogisticRegression
{
public:
    LogisticRegression();
    bool train(const string &file_str);
    bool train(const vector<vector<double>> &x_s,const vector<double> &Y);

    vector<bool> predict(const vector<vector<double> > &X_t);
    void setMinLimit(double value){minData = value;}
    void setBaseStep(double value){baseStep = value;}
private:
    bool gradientDescent(const vector<vector<double>> &x_s,const vector<double> &Y);
    bool stepIsTooLarge(double a,double b);
    void changeValue(double &x,bool up);
    bool stepIsTooSmall(double a,double b);
    int getNum(double num,int filt = 10);

    double costFunc(const vector<vector<double> > &x_s, const vector<double> &Y); //代价函数
    double decisionFunc(const vector<double> &X);                               //决策函数
    double logisticFunc(double z);                                              //逻辑函数
    double hypothesisFunc(const vector<double> &X);                             //假设函数

    inline void changeAlphaByDtheta(size_t i, const vector<double> &d_theta);
    inline void changeAlphaByCost(size_t i, double cost);

    double minData = 1e-5;//1*(10的-5次方)即0.00001

    vector<double> thetas;
    vector<double> d_thetas_save;
    vector<double> alpha;

    double baseStep = 0.01;
    double minCosted = -1; //波谷记录
    double costSave  = -1; //波谷记录
};

#endif // LINEARREGRESSION_H
