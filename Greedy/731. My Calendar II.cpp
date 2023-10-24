/*
731. My Calendar II
*/

//sort by starting points TC:O(n^2) SC:O(n)
class MyCalendarTwo {
    multiset<pair<int, int>> set;//start,end
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        vector<pair<int,int>> temp;
        for(auto x:set){
            if(!(start >= x.second || end <= x.first)){
                temp.push_back(x);//用反證的方式確定新加入的點跟目前遍歷到的區間有重疊
            }
            if(end < x.first) break; //因為multiset已經排好序 如果新加入點的end都比我下一個要遍歷的頭還要前面那就不用遍歷下去了
        }

        //判斷舊的區間是否有重疊
        for(int i = 1; i < temp.size(); i++){
            if(temp[i].first < temp[i-1].second) return false;
        }
        set.insert({start,end});
        return true;
    }
};

/*
此題想求給你加入一個區間 問你加入此區間後跟之前的區間是否會有三個重疊的區間
想法是先加入新的區間進去 比較一下哪些區間跟新加入的重疊 把他們按照starting points排序
然後去比較這些區間是否互相重疊 有重疊的話就代表肯定有三個重疊之處
-----
      -----
------- 
*/
