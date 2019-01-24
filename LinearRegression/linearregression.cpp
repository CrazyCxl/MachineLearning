#include "linearregression.h"
#include <fstream>
#include <string>

LinearRegression::LinearRegression()
{

}

bool LinearRegression::train(const string &file_str)
{
    ifstream file(file_str);
    if(file.is_open()){
        vector<double> X,Y;
        while (!file.eof()){
            string line_str;
            char buff[50] = {0};
            file.getline(buff,50);
            line_str = string(buff);

            if(buff[0] < 48 || buff[0]>57) // is not number
                continue;

            size_t index = line_str.find_first_of(',');
            string line_x = line_str.substr(0,index);
            string line_y = line_str.substr(index+1,line_str.size() - index);
            cout << "load x:"<<line_x.c_str()<<" y:"<<line_y.c_str()<<endl;
            X.push_back(stod(line_x));
            Y.push_back(stod(line_y));
        }
        train(X,Y);
    }else{
        return false;
    }

    return true;
}

bool LinearRegression::train(const vector<double> X, const vector<double> Y)
{
    if(X.size() != Y.size())
        return false;

    gradientDescent(X,Y);
    cout<<"over gradient descent theta1:"<<theta1<<" theta2:"<<theta2<<endl;
    return true;
}

vector<double> LinearRegression::predict(vector<double> X_t)
{
    vector<double> Y_t;
    for(auto x = X_t.begin();x != X_t.end();x++){
        Y_t.push_back(theta1 + theta2*(*x));
    }
    return Y_t;
}

void LinearRegression::gradientDescent(const vector<double> &X,const vector<double> &Y)
{
    double d_theta1 = 0,d_theta2 = 0;

    for(size_t i=0;i<X.size();++i){
        d_theta1 += theta1 + theta2*X[i] - Y[i];
        d_theta2 += (theta1 + theta2*X[i] - Y[i])*X[i];
    }

    d_theta1 = d_theta1/X.size();
    d_theta2 = d_theta2/X.size();

    bool is_continue = false;

    if(fabs(d_theta1) > minDTheta){
        theta1 = theta1 - step*d_theta1;
        is_continue = true;
    }

    if(fabs(d_theta2) > minDTheta){
        theta2 = theta2 - step*d_theta2;
        is_continue = true;
    }

    if(is_continue){
        cout<<"countinue gradient descent theta1:"<<theta1<<" theta2:"<<theta2
           <<" d_theta1:"<<d_theta1<<" d_theta2:"<<d_theta2<<endl;
        gradientDescent(X,Y);
    }
}
