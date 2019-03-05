#include "logisticregression.h"
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <sstream>

LogisticRegression::LogisticRegression()
{

}

bool LogisticRegression::train(const string &file_str)
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

//            cout << "load x:"<<line_x.c_str()<<" y:"<<line_y.c_str()<<endl;
            vector<double> X;
            std::istringstream split(line_str);
            std::string each;
            while (std::getline(split, each, ',')){
                X.push_back(stod(each));
            }

            Y.push_back(*(X.end()-1));
            X.erase(X.end()-1);
            X.insert(X.begin(),1.0);
            Xs.push_back(X);
        }
        train(Xs,Y);
    }else{
        return false;
    }

    return true;
}

bool LogisticRegression::train(const vector<vector<double> > &x_s, const vector<double> &Y)
{
    thetas.clear();
    alpha.clear();

    if(x_s.size() != Y.size() || x_s.size() == 0){
        return false;
    }

    thetas = vector<double>(x_s[0].size(),1);

    alpha = vector<double>(thetas.size(),baseStep);

    vector<vector<double>> X = x_s;

    while(gradientDescent(X,Y));
    cout<<"over gradient descent theta";
    for(size_t i = 0 ;i<thetas.size(); i++){
        cout<<" "<<thetas[i];
    }
    cout<<endl;
    return true;
}

vector<bool> LogisticRegression::predict(const vector<vector<double>> &X_t)
{
    vector<bool> Y_t;
    vector<vector<double>> X = X_t;
    for (size_t i =0;i<X.size();i++) {
        X[i].insert(X[i].begin(),1);
        if(decisionFunc(X[i]) > 0){
            Y_t.push_back(true);
        }else{
            Y_t.push_back(false);
        }
    }
    return Y_t;
}

bool LogisticRegression::gradientDescent(const vector<vector<double> > &x_s,const vector<double> &Y)
{
    vector<double> d_thetas_t(thetas.size(),0);

    for(size_t i=0;i<x_s.size();++i){
        for(size_t j=0;j<x_s[i].size();++j){
            double hy = hypothesisFunc(x_s[i]) - Y[i];
            d_thetas_t[j] += hy*x_s[i][j];
        }
    }

    bool is_continue = false;

    double cost = costFunc(x_s,Y);

    for(size_t i=0;i<d_thetas_t.size();++i){
        d_thetas_t[i] = d_thetas_t[i]/d_thetas_t.size();

        changeAlphaByDtheta(i,d_thetas_t);

        if(fabs(d_thetas_t[i]) > minData){
            is_continue = true;
        }

        if(is_continue){
            double diff = alpha[i]*d_thetas_t[i];
            thetas[i] = thetas[i] - diff;
        }
    }

//    if(!is_continue && cost > minData){
//        is_continue = true;
//    }

    if(is_continue){
        cout<<"continue gradient descent cost:"<<cost;
        for(size_t i = 0 ;i<thetas.size(); i++){
            cout<<" theta:"<<thetas[i]<<" d_theta:"<<d_thetas_t[i]
                  << " alpha:"<<alpha[i]<<" # ";
        }
        cout<<endl;
    }

    d_thetas_save = d_thetas_t;
    costSave = cost;
    return is_continue;
}

bool LogisticRegression::stepIsTooLarge(double a, double b)
{
    a = fabs(a);
    b = fabs(b);
    double diff = fabs(a-b);

    if(diff > b || diff > a)
        return true;

    a = getNum(a,100) +getNum(a)*10;
    b = getNum(b,100) +getNum(b)*10;
    return (a-b)>1;
}

void LogisticRegression::changeValue(double &x, bool up)
{
    if(up){
        x += x/3;
    }else{
        x -= x/3;
    }
}

bool LogisticRegression::stepIsTooSmall(double a, double b)
{
    a = fabs(a);
    b = fabs(b);

    a = getNum(a,1000) + getNum(a,100)*10 +getNum(a)*100;
    b = getNum(b,1000) + getNum(b,100)*10 +getNum(b)*100;
    return (a - b) < 1;
}

int LogisticRegression::getNum(double num, int filt)
{
    int f = 0;

    if(num == 0.0){
        return 0;
    }

    while (num < filt/10){
        num *= 10;
    }

    while (num > filt){
        num /= 10;
    }

    f = static_cast<int>(num)%10;
    return f;
}

double LogisticRegression::costFunc(const vector<vector<double>> &x_s, const vector<double> &Y)
{
    double c = 0;
    for(size_t i =0 ;i<x_s.size();i++){
        if(Y[i] > 0.5){
            //y = 1
            c += -log(hypothesisFunc(x_s[i]));
        }else{
            //y = 0
            c += -log(1-hypothesisFunc(x_s[i]));
        }
    }
    c = c/x_s.size();
    return c;
}

double LogisticRegression::decisionFunc(const vector<double> &X)
{
    if(X.size() != thetas.size()){
        std::cout<<"decision func but size is error!"<<std::endl;
        exit(-1);
    }

    double y = 0;
    for(size_t i = 0;i<X.size();++i){
        y +=  thetas[i]*X[i];
    }

    return y;
}

double LogisticRegression::logisticFunc(double z)
{
    double result = 1+exp(-z);
    return 1/result;
}

double LogisticRegression::hypothesisFunc(const vector<double> &X)
{
    double result = decisionFunc(X);
    result = logisticFunc(result);
    return result;
}

void LogisticRegression::changeAlphaByDtheta(size_t i,const vector<double> &d_theta)
{
    if(d_thetas_save.size() > 0 && fabs(d_thetas_save[i]) > minData){
        double diff = fabs(d_thetas_save[i]) - fabs(d_theta[i]);
        if(diff < -1e-15 ){
            if(d_thetas_save[i] * d_theta[i] > 0){
                changeValue(alpha[i],true);
            }else{
                changeValue(alpha[i],false);
            }
        }else{
            if(stepIsTooLarge(d_thetas_save[i],d_theta[i])){
                changeValue(alpha[i],false);
            }
            else if(stepIsTooSmall(d_thetas_save[i],d_theta[i])){
                changeValue(alpha[i],true);
            }
        }
    }
}

void LogisticRegression::changeAlphaByCost(size_t i, double cost)
{
    if(stepIsTooLarge(costSave,cost)){
        changeValue(alpha[i],false);
    }
    else if(stepIsTooSmall(costSave,cost)){
        changeValue(alpha[i],true);
    }
}
