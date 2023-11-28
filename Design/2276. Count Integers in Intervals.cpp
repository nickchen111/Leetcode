/*
2276. Count Integers in Intervals
*/

// TC:O(lgn) SC:O(n)
class CountIntervals {
    map<int,int> map;
    int res = 0;
public:
    CountIntervals() {
        
    }
    
    void add(int left, int right) {
        unordered_set<int> tbd;//放一個容器裝要刪掉的
        int leftBoundary = left;
        auto iter = map.lower_bound(left);
        if(iter != map.begin() && prev(iter)->second >= left){
            iter = prev(iter);
            leftBoundary = min(left,iter->first);
            tbd.insert(iter->first);
        }

        int rightBoundary = right;
        iter = map.lower_bound(left);
        if(iter != map.begin()){
            rightBoundary = max(right,prev(iter)->second);
        }

        while(iter != map.end() && iter->first <= rightBoundary){
            tbd.insert(iter->first);
            rightBoundary = max(rightBoundary,iter->second);
            iter = next(iter);
        }

        for(int x:tbd){
            res-=map[x]-x+1;
            map.erase(x);
        }

        map[leftBoundary] = rightBoundary;
        res+=(rightBoundary-leftBoundary+1);

    }
    
    int count() {
        return res;
    }
};

/*
此題跟713題很像 唯一需要注意的是713的概念去做會遺漏一個case
-------------------- 找到的區間
  ------- 欲加入的區間 
  這樣他在leftboundary時會找對沒錯 但rightboundary只會是他本人
*/
