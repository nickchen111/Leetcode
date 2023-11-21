/*
2940. Find Building Where Alice and Bob Can Meet
*/

// TC:O(nlgn+n) SC:O(n)
class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int n = heights.size();
        for(int i = 0; i<queries.size(); i++){
            //讓第二個會是比較高的
            sort(queries[i].begin(),queries[i].end());
            //紀錄此query在答案中的idx
            queries[i].push_back(i);
        }
        //將每項query最大的idx中較高的放在前面 優先做 遇到這種有query的題目可以做的處理方式
        auto cmp = [](vector<int>& A, vector<int>&B){
            return A[1] > B[1];
        };
        sort(queries.begin(),queries.end(), cmp);

        //用map是為了後面可以用upper_bound二分查找
        map<int,int> map;//height->index 維護單調遞減
        int j = n-1;
        vector<int> res(queries.size());
        for(auto query:queries){
            int a = query[0], b = query[1], query_idx = query[2];
            while(j >= b){
                while(!map.empty() && heights[j] >= (map.begin()->first)){
                    map.erase(map.begin());
                }
                map[heights[j]] = j;
                j--;
            }
            // corner case 如果這個兩個樓idx相等就不用跳 or a樓低於b樓
            if(a == b || heights[a] < heights[b]){
                res[query_idx] = b;
                continue;
            }
            int m = max(heights[a],heights[b]);
            auto iter = map.upper_bound(m);
            if(iter != map.end()){
                res[query_idx] = iter->second;
            }
            else res[query_idx] = -1;
        }

        return res;
    }
};
/*
小高度可以移動到大高度 只能從左邊移動到右邊
x < y heights[x] > heights[y] y沒必要
所以高度跟index都希望是遞增的
但在加入的當下像是在維護遞減序列     
*/
