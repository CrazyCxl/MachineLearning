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
        Y_t.insert(Y_t.begin(),static_cast<int>(*y));
    }

    kdtree.feed(x_s,Y_t);

//    while(gradientDescent(X,Y));
//    cout<<"over gradient descent theta";
//    for(size_t i = 0 ;i<thetas.size(); i++){
//        cout<<" "<<thetas[i];
//    }
//    cout<<endl;
    return true;
}

vector<bool> KNeighborsClassifier::predict(const vector<vector<double>> &X_t)
{
    vector<bool> Y_t;
    vector<vector<double>> X = X_t;
    for (size_t i =0;i<X.size();i++) {
        X[i].insert(X[i].begin(),1);
//        if(decisionFunc(X[i]) > 0){
//            Y_t.push_back(true);
//        }else{
//            Y_t.push_back(false);
//        }
    }
    return Y_t;
}
