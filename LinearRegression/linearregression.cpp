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

    if(x_s.size() != Y.size() || x_s.size() == 0){
        return false;
    }

    thetas = vector<double>(x_s[0].size()+1);

    while(gradientDescent(x_s,Y));
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
    for(auto xs = X_t.begin();xs != X_t.end();xs++){
        Y_t.push_back(func(*xs));
    }
    return Y_t;
}

bool LinearRegression::gradientDescent(const vector<vector<double> > &x_s,const vector<double> &Y)
{
    vector<double> d_thetas(thetas.size());

    for(size_t i=0;i<x_s.size();++i){
        d_thetas[0] += (func(x_s[i]) - Y[i]);
        for(size_t j=0;j<x_s[i].size();++j){
            d_thetas[j+1] += (func(x_s[i]) - Y[i])*x_s[i][j];
        }
    }

    bool is_continue = false;

    for(size_t i=0;i<d_thetas.size();++i){
        d_thetas[i] = d_thetas[i]/x_s.size();
        if(fabs(d_thetas[i]) > minDTheta){
            thetas[i] = thetas[i] - step*d_thetas[i];
            is_continue = true;
        }
    }
    if(is_continue){
        cout<<"continue gradient descent ";
        for(size_t i = 0 ;i<thetas.size(); i++){
            cout<<" θ:"<<thetas[i]<<" dθ:"<<d_thetas[i];
        }
        cout<<endl;
    }
    return is_continue;
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
