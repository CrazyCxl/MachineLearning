#include "linearregression.h"
#include <fstream>
#include <string>
#include <sstream>

LinearRegression::LinearRegression()
{

}

bool LinearRegression::train(const string &file_str)
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
            Xs.push_back(X);
        }
        train(Xs,Y);
    }else{
        return false;
    }

    return true;
}

bool LinearRegression::train(const vector<double> &X, const vector<double> &Y)
{
    vector<vector<double> > x_s;
    for(auto x = X.begin();x != X.end();x++){
        x_s.push_back({*x});
    }
    return train(x_s,Y);
}

bool LinearRegression::train(const vector<vector<double> > &x_s, const vector<double> &Y)
{
    thetas.clear();
    steps.clear();

    if(x_s.size() != Y.size() || x_s.size() == 0){
        return false;
    }

    thetas = vector<double>(x_s[0].size()+1);

    steps = vector<double>(x_s[0].size()+1,baseStep);

    vector<vector<double>> X = x_s;
    x_maxs.clear();
    x_mins.clear();
    x_avgs.clear();

    while(gradientDescent(X,Y));
    cout<<"over gradient descent theta";
    for(size_t i = 0 ;i<thetas.size(); i++){
        cout<<" "<<thetas[i];
    }
    cout<<endl;
    return true;
}

vector<double> LinearRegression::predict(const vector<vector<double>> &X_t)
{
    vector<double> Y_t;
    vector<vector<double>> X = X_t;
    for(auto xs = X.begin();xs != X.end();xs++){
        Y_t.push_back(func(*xs));
    }
    return Y_t;
}

bool LinearRegression::gradientDescent(const vector<vector<double> > &x_s,const vector<double> &Y)
{
    vector<double> d_thetas_t(thetas.size());

    for(size_t i=0;i<x_s.size();++i){
        d_thetas_t[0] += (func(x_s[i]) - Y[i]);
        for(size_t j=0;j<x_s[i].size();++j){
            d_thetas_t[j+1] += (func(x_s[i]) - Y[i])*x_s[i][j];
        }
    }

    bool is_continue = false;

    for(size_t i=0;i<d_thetas_t.size();++i){
        d_thetas_t[i] = d_thetas_t[i]/x_s.size();

        if(d_thetas.size() > 0 && fabs(d_thetas[i]) > minDTheta){
            double diff = fabs(d_thetas[i]) - fabs(d_thetas_t[i]);
            if(diff < 0 ){
                if(d_thetas[i] * d_thetas_t[i] > 0){
                    changeValue(steps[i],true);
                }else{
                    changeValue(steps[i],false);
                }
            }else{
                if(stepIsTooLarge(d_thetas[i],d_thetas_t[i])){
                    changeValue(steps[i],false);
                }
                else if(stepIsTooSmall(d_thetas[i],d_thetas_t[i])){
                    changeValue(steps[i],true);
                }
            }
        }

        double diff = steps[i]*d_thetas_t[i];
        thetas[i] = thetas[i] - diff;
        if(fabs(d_thetas_t[i]) > minDTheta){
            is_continue = true;
        }
    }
    if(is_continue){
        cout<<"continue gradient descent ";
        for(size_t i = 0 ;i<thetas.size(); i++){
            cout<<" θ:"<<thetas[i]<<" dθ:"<<d_thetas_t[i];
//                  << " s:"<<steps[i];
        }
        cout<<endl;
    }

    d_thetas = d_thetas_t;
    return is_continue;
}

bool LinearRegression::stepIsTooLarge(double a, double b)
{
    a = fabs(a);
    b = fabs(b);

    a = getNum(a,100) +getNum(a)*10;
    b = getNum(b,100) +getNum(b)*10;
    return (a-b)>1;
}

void LinearRegression::changeValue(double &x, bool up)
{
    if(up){
        x += x/3 + x*minDTheta;
    }else{
        x -= x/3 + x*minDTheta;
    }
}

bool LinearRegression::stepIsTooSmall(double a, double b)
{
    a = fabs(a);
    b = fabs(b);

    a = getNum(a,1000) + getNum(a,100)*10 +getNum(a)*100;
    b = getNum(b,1000) + getNum(b,100)*10 +getNum(b)*100;
    return (a - b) < 1;
}

int LinearRegression::getNum(double num, int filt)
{
    int f = 0;
    while (num < filt/10){
        num *= 10;
    }

    while (num > filt){
        num /= 10;
    }

    f = static_cast<int>(num)%10;
    return f;
}

double LinearRegression::func(const vector<double> &X)
{
    if(X.size() != thetas.size() -1){
        cout<<"LinearRegression::func error size!";
        return 0;
    }

    double y = thetas[0];
    for(size_t i = 0;i<X.size();++i){
        y +=  thetas[i+1]*X[i];
    }
    return y;
}
