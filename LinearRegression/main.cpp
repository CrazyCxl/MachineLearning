#include <iostream>
#include "linearregression.h"

int main(int,char *[])
{
    LinearRegression linearRegression;
    if(linearRegression.train("../../../resource/dataset/studentscores.csv")){
        vector<double> Y = linearRegression.predict({0,5});
        cout << "result:";
        for (auto y = Y.begin();y!=Y.end();y++) {
            cout <<" "<<*y;
        }
        cout<<endl;
    }
    return 0;
}
