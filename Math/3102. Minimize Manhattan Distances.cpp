/*
3102. Minimize Manhattan Distances
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) {
        vector<multiset<int>> arr(4);
        for(auto p : points){
            arr[0].insert(p[0] + p[1]);
            arr[1].insert(p[0] - p[1]);
            arr[2].insert(-p[0] + p[1]);
            arr[3].insert(-p[0] - p[1]);
        }
        
        int ret = INT_MAX;
        for(auto p : points){
            arr[0].erase(arr[0].find(p[0]+p[1]));
            arr[1].erase(arr[1].find(p[0]-p[1]));
            arr[2].erase(arr[2].find(-p[0]+p[1]));
            arr[3].erase(arr[3].find(-p[0]-p[1]));
            
            int res = 0;
            res = max(res, *prev(arr[0].end()) - *arr[0].begin());
            res = max(res, *prev(arr[1].end()) - *arr[1].begin());
            res = max(res, *prev(arr[2].end()) - *arr[2].begin());
            res = max(res, *prev(arr[3].end()) - *arr[3].begin());
            
            ret = min(ret, res);
            arr[0].insert(p[0] + p[1]);
            arr[1].insert(p[0] - p[1]);
            arr[2].insert(-p[0] + p[1]);
            arr[3].insert(-p[0] - p[1]);
        }
        
        return ret;
        
        
    }
};

/*
此題跟LC上1131題類似 沒有這個知識點的話這題確實是做不出來 要求若干個點集的最大曼哈頓距離 要用的方式就是模擬絕對值得所有情況 然後從這些情況中自身所對應的最大值減去最小值的差
從中挑選出最大的那項 這是1131的做法 
這題新增了可以刪除任意一點 那麼就遍歷一下當下的點都當作是要刪除的點 用vector<multiset<int>> arr(4) 去從中去掉跟新增
然後去挑每次過程中的最小的最大值即可
*/
