#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

namespace KDTreeSpace {
    template <typename T>
    class Point{
    public:
        Point(){}
        Point(Point p,int n,Point *parent =NULL){
            this->X = p.X;
            this->y = p.y;
            this->id = p.id;
            this->n=n;
            this->top = parent;
        }

        static size_t containsYsize(vector<Point<T>> points,int y_value)
        {
            size_t y_size = 0;
            for (auto p = points.begin();p!=points.end();p++) {
                if((*p).y == y_value){
                    y_size++;
                }
            }
            return y_size;
        }
        vector<T> X;
        int y = -1;
        int n = -1;//维度

        bool    visited = false;
        double  distance = -1;

        Point *top   = NULL;
        Point *left  = NULL;
        Point *right = NULL;

        int id = -1;
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
                p.id = i;
                points_tmp.push_back(p);
            }
            init(points_tmp,topPoint,0);
        }

        vector<Point<T>> findAdjacentK(const vector<T> &X,size_t k)
        {
            vector<Point<T>> J;
            if(topPoint == NULL){
                return J;
            }

            Point<T> point_target;
            point_target.X = X;
            tryfindAdjacentAnchor(J,k,topPoint,&point_target);
            clearTempData(topPoint);
            return J;
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

        //graphviz可视化
        void toDot(const char *file_path)
        {
            ofstream file(file_path);
            if(file.is_open()){
                file<< "digraph\n{\nnode [shape = Mrecord];\n";
                writeDot(file,topPoint);
                file<<"}";
                file.close();
            }
        }

    private:
        void writeDot(ofstream &stream,Point<T> *p)
        {
            if(p == NULL){
                return;
            }
            stream <<"p"<< p<<" [label = \"<f0> ("<<p->id<<")"<<p->X[0];
            for(size_t i = 1; i < p->X.size();i++)
            {
                stream <<"| <f"<<i<<"> "<<p->X[i];
            }
            stream <<"\"];\n";

            if(p->top){
                stream<<"p"<<p->top<<":f"<<p->top->n<<" -> p"<<p<<";\n";
            }
            writeDot(stream,p->left);
            writeDot(stream,p->right);
        }

        void clearTempData(Point<T> *p_anchor)
        {
            if(p_anchor != NULL) {
                p_anchor->distance = -1;
                p_anchor->visited = false;
                clearTempData(p_anchor->left);
                clearTempData(p_anchor->right);
            }
        }
        //step1
        //根据P 的坐标值和每个节点的切分向下搜索（也就是说，如果Panchor是按照 xr=a 进行切分，并且 Pr<a，则向左枝进行搜索，反之则走右枝）
        void tryfindAdjacentAnchor(vector<Point<T>> &J,size_t k,Point<T> *p_anchor,Point<T> *p_target)
        {
            while (true) {
                if(p_anchor->X[p_anchor->n] > p_target->X[p_anchor->n]){
                    if(p_anchor->left != NULL){
                        p_anchor = p_anchor->left;
                    }else{
                        break;
                    }
                }else{
                    if(p_anchor->right != NULL){
                        p_anchor = p_anchor->right;
                    }else {
                        break;
                    }
                }
            }

            whenIntoDown(J,k,p_anchor,p_target);
        }

        //step2
        //当达到一个底部节点时，将其标记为访问过。
        void whenIntoDown(vector<Point<T>> &J,size_t k,Point<T> *p_anchor,Point<T> *p_target)
        {
            p_anchor->visited = true;
            checkWhetherReplace(J,k,p_anchor,p_target);
            climb(J,k,p_anchor,p_target);
        }

        //获取最大距离
        double getMaxDistance(const vector<Point<T>> &J,size_t &index)
        {
            double distance = 0;
            for (size_t i = 0;i<J.size();i++) {
                if(J[i].distance > distance){
                    distance = J[i].distance;
                    index = i;
                }
            }
            return distance;
        }

        //如果 J 里不足k 个点，则将当前节点的特征坐标加入J。
        //如果 J 已经有k个点并且当前节点的特征与 P 的距离小于 J 里最长的距离，则用当前特征替换掉 J 中离 P 最远的点。
        void checkWhetherReplace(vector<Point<T>> &J,size_t k,Point<T> *p_anchor,Point<T> *p_target)
        {
            double distance = 0;
            for(size_t i = 0;i<p_anchor->X.size();i++){
                distance += pow(p_anchor->X[i] - p_target->X[i],2);
            }

            p_anchor->distance = sqrt(distance);

            if(J.size() < k){
                J.push_back(*p_anchor);
            }else{
                size_t i = 0;
                double max_distance = getMaxDistance(J,i);
                if(max_distance > p_anchor->distance){
                    J[i] = *p_anchor;
                }
            }
        }

        //step3
        //向上爬
        void climb(vector<Point<T>> &J,size_t k,Point<T> *p_anchor,Point<T> *p_target)
        {
            while (p_anchor->visited) {
                if(p_anchor == topPoint){
                    return;
                }
                p_anchor = p_anchor->top;
            }

            p_anchor->visited = true;

            //(1)
            checkWhetherReplace(J,k,p_anchor,p_target);

            //(2)
            //计算目标点与切分线的距离
            double l_t_ah = p_target->X[p_anchor->n] - p_anchor->X[p_anchor->n];
            size_t index = 0;
            double max_distance = getMaxDistance(J,index);

            Point<T> *child_anchor = p_anchor->left->visited?p_anchor->right:p_anchor->left;
            if( (abs(l_t_ah) >= max_distance && J.size() >= k)||child_anchor == NULL ){
                //keep climb
                climb(J,k,p_anchor,p_target);
            }else{
                tryfindAdjacentAnchor(J,k,
                                      child_anchor,
                                      p_target);
            }
        }

        void init(const vector<Point<T>> &points_t,Point<T> *parent, int n,bool is_left = true)
        {
            Point<T> *p =NULL;

            //按照N维来排升序
            vector<Point<T>> points_tmp(points_t);

            for(size_t i=0;i<points_tmp.size()-1;i++){
                for(size_t j=i+1;j<points_tmp.size();j++){
                    if( points_tmp[j].X.at(n) < points_tmp[i].X.at(n)){
                        Point<T> p_tmp = points_tmp[j];
                        points_tmp[j] = points_tmp[i];
                        points_tmp[i] = p_tmp;
                    }
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

            if(anchor_index > 0){
                vector<Point<T>> left;
                copy(points_tmp.begin(),points_tmp.begin()+anchor_index,back_inserter(left));
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
