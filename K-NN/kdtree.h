#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>

using namespace std;

namespace KDTreeSpace {
    template <typename T>
    class Point{
    public:
        Point(){}
        Point(Point p,int n,Point *parent =NULL){
            this->X = p.X;
            this->y = p.y;
            this->n=n;
            this->top = parent;
        }

        vector<T> X;
        int y = -1;
        int n = -1;//维度

        bool isChecked = false;

        Point *top   = NULL;
        Point *left  = NULL;
        Point *right = NULL;
    };

    template <typename T>
    class KDTree
    {
    public:
        KDTree(){}

        void feed(const vector<vector<T>> &points_t, const vector<int> &Y)
        {
            clear();
            if(points_t.size() <= 0)
                return;

            if(points_t.size() != Y.size())
                abort();

            vector<Point<T>> points_tmp;
            for (size_t i =0;i<points_t.size();i++) {
                Point<T> p;
                p.X = points_t.at(i);
                p.y = Y.at(i);
                points_tmp.push_back(p);
            }
            init(points_tmp,topPoint,0);
            clear();
        }

        void clear(){
            Point<T> *anchor = topPoint;
            while (topPoint != NULL) {
                while(anchor->left != NULL){
                    anchor = anchor->left;
                }
                while(anchor->right != NULL){
                    anchor = anchor->right;
                }

                if(anchor->top == NULL){
                    delete anchor;
                    break;
                }

                anchor = anchor->top;
                if(anchor->right != NULL){
                    delete anchor->right;
                    anchor->right =NULL;
                }else{
                    delete anchor->left;
                    anchor->left =NULL;
                }
            }
            topPoint = NULL;
        }
    private:
        void init(const vector<Point<T>> &points_t,Point<T> *parent, int n,bool is_left = true)
        {
            Point<T> *p =NULL;

            //按照N维来排序
            vector<Point<T>> points_tmp;
            points_tmp.push_back(points_t.at(0));

            for(size_t i=1;i<points_t.size();i++){
                bool inserted = false;
                for(size_t j=0;j<points_tmp.size();j++){
                    if( points_t[i].X.at(n) > points_tmp[j].X.at(n)){
                        points_tmp.insert(points_tmp.begin()+j,points_t[i]);
                        inserted = true;
                        break;
                    }
                }
                if(!inserted){
                    points_tmp.insert(points_tmp.end(),points_t[i]);
                }
            }

            size_t anchor_index = points_tmp.size()/2;
            p = new Point<T>(points_tmp[anchor_index],n,parent);

            if(parent == NULL){
                topPoint = p;
            }else{
                if(is_left){
                    parent->left = p;
                }else{
                    parent->right = p;
                }
            }

            if(points_tmp.size() == 1){
                return;
            }

            if(anchor_index > 0){
                anchor_index = anchor_index == 1?2:anchor_index;
                vector<Point<T>> left;
                copy(points_tmp.begin(),points_tmp.begin()+anchor_index-1,back_inserter(left));
                init(left,p,(n+1)%p->X.size(),true);
            }

            if(anchor_index < (points_tmp.size() - 1)){
                vector<Point<T>> right;
                copy(points_tmp.begin()+anchor_index+1,points_tmp.end(),back_inserter(right));
                init(right,p,(n+1)%p->X.size(),false);
            }
        }

        Point<T> *topPoint = NULL;
    };
}

#endif // KDTREE_H
