#include <iostream>
#include "linearregression.h"

int main(int,char *[])
{
    LinearRegression linearRegression;
//    if(linearRegression.train("../../../resource/dataset/studentscores.csv")){
//        vector<double> Y = linearRegression.predict({{0},{5}});
//        cout << "result:";
//        for (auto y = Y.begin();y!=Y.end();y++) {
//            cout <<" "<<*y;
//        }
//        cout<<endl;
//    }

    linearRegression.setBaseStep(1e-11);
    if(linearRegression.train("../../../resource/dataset/50_Startups.csv")){
        vector<double> Y = linearRegression.predict({{0,0,15505.73,117382.3,35534.17},
                                                     {1,0,542.005,51743.15,0}});
        cout << "result:";
        for (auto y = Y.begin();y!=Y.end();y++) {
            cout <<" "<<*y;
        }
        cout<<endl;
    }
    return 0;
}
