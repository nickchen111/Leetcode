/*
2593. Find Score of an Array After Marking All Elements
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    long long findScore(vector<int>& nums) {
        int n = nums.size();
        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b){
            if(a.first != b.first){
                return a.first > b.first;
            }
            else return a.second > b.second;
        };

        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype (cmp)> pq;
        for(int i = 0; i < n; i++){
            pq.push({nums[i], i});
        }

        vector<bool> visited(n,0); //未來不能選的idx
        long long res = 0;
        while(!pq.empty()){
            int idx = pq.top().second;
            int num = pq.top().first;
            pq.pop();
            if(visited[idx] == 0){
                visited[idx] = 1;
                res += num;
                if(idx-1 >= 0) visited[idx-1] = 1;
                if(idx+1 < n) visited[idx+1] = 1;
            }
        }

        return res;
    }
};

/*
此題模擬一個過程 
1.選最小的數字並且把他前後的數字標記成不能選
2.在選下個數字 一直不斷重複直到沒數字 總和是多少
數字丟進PQ排序大小 如果相同按照idx排序 一個一個丟出來並且用vector visited 判斷是否可加入答案
*/
