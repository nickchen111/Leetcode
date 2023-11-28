/*
715. Range Module
*/


// TC:O(lgn) SC:O(n)
class RangeModule {
    map<int,int> map;
public:
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        int leftBoundary = left;
        auto iter1 = map.lower_bound(left);
        if(iter1 != map.begin() && prev(iter1)->second >= left){
            iter1 = prev(iter1);
            leftBoundary = iter1->first;
        }

        int rightBoundary = right;
        auto iter2 = map.upper_bound(right);
        if(iter2 != map.begin() && prev(iter2)->second >= right){
            rightBoundary = prev(iter2)->second;
        }
        //這個用法可學一下
        map.erase(iter1,iter2);//左閉右開的可以刪掉iter1~iter2之前的東西
        map[leftBoundary]=rightBoundary;
    }
    
    bool queryRange(int left, int right) {
        //要找第一個小於等於left區間
        auto iter = map.upper_bound(left);
        return (iter != map.begin() && prev(iter)->second >= right);
    }
    
    void removeRange(int left, int right) {
        auto iter1 = map.lower_bound(left);
        int h1 = 0, t1 = 0; //紀錄之後可能要加入的前面段
        if(iter1 != map.begin() && prev(iter1)->second > left){
            iter1 = prev(iter1);
            h1 = iter1->first;
            t1 = left;
        }

        auto iter2 = map.upper_bound(right);
        int h2 = 0, t2 = 0;
        if(iter2 != map.begin() && prev(iter2)->second > right){
            h2 = right;
            t2 = prev(iter2)->second;
        }

        map.erase(iter1,iter2);
        if(h1 != 0){
            map[h1] = t1;
        }
        if(t2 != 0){
            map[h2] = t2;
        }

    }
};

/*
此題想要你維護一堆區間 在query的時候傳回是否有這段連續區間包住query的區間
left right -> 用 map<int,int> map; 就夠了 
addRange: 就是考慮是否加入的區間可以幫助更新不連續的區間 去找他可能的最左邊以及最右邊 by lower_bound upper_bound
remove: 如果有非交集到的地方要再加回去
*/

