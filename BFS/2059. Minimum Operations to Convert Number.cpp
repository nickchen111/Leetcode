/*
2059. Minimum Operations to Convert Number
*/


// TC:O(n*m) m = range 0~1000 SC:O(n)
class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        int n = nums.size();

        queue<int> q;
        q.push(start);
        vector<int> visited(1001,0);

        int step = -1;
        while(!q.empty()){
            int sz = q.size();
            step += 1;
            while(sz--){
                int cur = q.front();
                q.pop();
                if(cur == goal) return step;
                if(cur > 1000 || cur < 0) continue;
                if(visited[cur]) continue;
                visited[cur] = 1;

                for(auto x : nums){
                    int cand1 = cur + x;
                    int cand2 = cur - x;
                    int cand3 = cur^x;
                    for(auto j : {cand1, cand2, cand3}) q.push(j);
                }
            }
        }

        return -1;
    }
};

// Hash Set
class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        int n = nums.size();

        queue<int> q;
        q.push(start);
        unordered_set<int> visited;

        int step = -1;
        while(!q.empty()){
            int sz = q.size();
            step += 1;
            while(sz--){
                int cur = q.front();
                q.pop();
                if(cur == goal) return step;
                if(cur > 1000 || cur < 0) continue;
                if(visited.find(cur) != visited.end()) continue;
                visited.insert(cur);

                for(auto x : nums){
                    int cand1 = cur + x;
                    int cand2 = cur - x;
                    int cand3 = cur^x;
                    if(visited.find(cand1) == visited.end()) q.push(cand1);
                    if(visited.find(cand2) == visited.end()) q.push(cand2);
                    if(visited.find(cand3) == visited.end()) q.push(cand3);
                }
            }
        }

        return -1;
    }
};

/*
給你一個數字起頭
你可以對數組內的元素做任意次數的
x + nums[i]
x - nums[i]
x ^ nums[i] (bitwise-XOR)
前提是目前數字 >= 0 && <= 1000 問說最少要做幾次可以達到goal
如果不行的話就返回-1
首先題目給的操作很明確 並且問最少次數 讓我想到BFS
n 從 1 ~1000 可以先去重

*/
