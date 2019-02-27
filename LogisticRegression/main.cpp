#include <iostream>
#include "logisticregression.h"

int main(int,char *[])
{
    LogisticRegression logisticregression;

    logisticregression.setBaseStep(1e-11);
    if(logisticregression.train("../../../resource/dataset/Social_Network_Ads.csv")){
        vector<bool> Y = logisticregression.predict({{19,18000},
                                                     {45,41000},{47,50000}});
        cout << "result:";
        for (auto y = Y.begin();y!=Y.end();y++) {
            cout <<" "<<*y;
        }
        cout<<endl;
    }
    return 0;
}
