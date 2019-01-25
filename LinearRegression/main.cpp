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

    linearRegression.setStep(1e-11);
    if(linearRegression.train("../../../resource/dataset/50_Startups.csv")){
        vector<double> Y = linearRegression.predict({{0,0,15505.73,117382.3,35534.17,69758.98},
                                                     {1,0,5420.05,51743.15,0,35673.41}});
        cout << "result:";
        for (auto y = Y.begin();y!=Y.end();y++) {
            cout <<" "<<*y;
        }
        cout<<endl;
    }
    return 0;
}
