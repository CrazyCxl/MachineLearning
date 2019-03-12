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
        int n = -1;//ά��

        bool    visited = false;
        double  distance = -1;

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

    private:
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
        //����P ������ֵ��ÿ���ڵ���з�����������Ҳ����˵�����Panchor�ǰ��� xr=a �����з֣����� Pr<a��������֦������������֮������֦��
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
        //���ﵽһ���ײ��ڵ�ʱ��������Ϊ���ʹ���
        void whenIntoDown(vector<Point<T>> &J,size_t k,Point<T> *p_anchor,Point<T> *p_target)
        {
            p_anchor->visited = true;
            checkWhetherReplace(J,k,p_anchor,p_target);
            climb(J,k,p_anchor,p_target);
        }

        //��ȡ������
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

        //��� J �ﲻ��k ���㣬�򽫵�ǰ�ڵ�������������J��
        //��� J �Ѿ���k���㲢�ҵ�ǰ�ڵ�������� P �ľ���С�� J ����ľ��룬���õ�ǰ�����滻�� J ���� P ��Զ�ĵ㡣
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
        //������
        void climb(vector<Point<T>> &J,size_t k,Point<T> *p_anchor,Point<T> *p_target)
        {
            if(p_anchor == topPoint){
                return;
            }
            while (p_anchor->visited) {
                p_anchor = p_anchor->top;
            }

            p_anchor->visited = true;

            //(1)
            checkWhetherReplace(J,k,p_anchor,p_target);

            //(2)
            //����Ŀ������з��ߵľ���
            double l_t_ah = p_anchor->X[p_anchor->n] - p_target->X[p_anchor->n];
            size_t index = 0;
            double max_distance = getMaxDistance(J,index);

            if(abs(l_t_ah) < max_distance || J.size() < k){
                tryfindAdjacentAnchor(J,k,
                                      l_t_ah > 0 ?p_anchor->right:p_anchor->left,
                                      p_target);
            }

            if(abs(l_t_ah) >= max_distance){
                //keep climb
                climb(J,k,p_anchor,p_target);
            }
        }

        void init(const vector<Point<T>> &points_t,Point<T> *parent, int n,bool is_left = true)
        {
            Point<T> *p =NULL;

            //����Nά������
            vector<Point<T>> points_tmp;
            points_tmp.push_back(points_t.at(0));

            for(size_t i=1;i<points_t.size();i++){
                bool inserted = false;
                for(size_t j=0;j<points_tmp.size();j++){
                    if( points_t[i].X.at(n) > points_tmp[j].X.at(n)){
                        points_tmp.push_back(points_t[i]);
                        inserted = true;
                        break;
                    }
                }
                if(!inserted){
                    points_tmp.insert(points_tmp.begin(),points_t[i]);
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
