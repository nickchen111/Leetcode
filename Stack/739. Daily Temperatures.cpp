/*
739. Daily Temperatures
*/

//從前遍歷到後 比較順邏輯
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> s;//維護單調遞減的溫度 index
        int n = temperatures.size();
        vector<int> res(n,0);
        for(int i = 0; i<n; i++){
            while(!s.empty() && temperatures[s.top()] < temperatures[i]){
                res[s.top()] = i-s.top();
                s.pop();
            }
            s.push(i);
        }
        return res;
    }
};

//從後遍歷到前
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size(); 
        stack<int> s; //存放的是索引
        vector<int> ans(n);

        for(int i = n-1; i >= 0; i--){
            while(!s.empty() && temperatures[s.top()] <= temperatures[i]){
                s.pop();
            }

            ans[i] = s.empty() ? 0:(s.top()-i);
            s.push(i);
        }

        return ans;
    }
};

/*
解題思路：
此題也是一求後面有無更大元素的題目 只不過這次要的是索引差 by stack
tc: o(n) sc: o(n) 
*/
