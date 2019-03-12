#include <iostream>
#include "knn.h"

int main(int,char *[])
{
    KNeighborsClassifier kneighborsClassifier;

    if(kneighborsClassifier.train("../../../resource/dataset/Social_Network_Ads.csv")){
        vector<bool> Y = kneighborsClassifier.predict({{47,49000},{45,41000},{19,18000}},5);
        cout << "result:";
        for (auto y = Y.begin();y!=Y.end();y++) {
            cout <<" "<<*y;
        }
        cout<<endl;
    }
    return 0;
}
