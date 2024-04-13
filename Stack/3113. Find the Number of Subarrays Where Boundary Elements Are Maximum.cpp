/*
3113. Find the Number of Subarrays Where Boundary Elements Are Maximum
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long numberOfSubarrays(vector<int>& nums) {
        int n = nums.size();
        
        
        vector<int> nextGreater(n,n);
        stack<int> stack; // 遞減序列
        for(int i = 0; i < n; i++){
            while(!stack.empty() && nums[stack.top()] < nums[i]){
                nextGreater[stack.top()] = i;
                stack.pop();
            }
            stack.push(i);
        }
        
        
        unordered_map<int,vector<int>> map;
        for(int i = 0; i < n; i++){
            map[nums[i]].push_back(i);
        }
        
        LL res = 0;
        
        for(auto p : map){
            int m = p.second.size();
            if(m == 1) continue;
            
            int j = 0;
            // x x x x big x x 
            for(int i = 0; i < m; i++){
                int next = nextGreater[p.second[i]];
                while(j < m && nextGreater[p.second[j]] == next){
                    j++;
                }
                res += (LL)(j-i)*(j-i-1)/2;
                i = j-1;
            }
        }
        
        
        res += n;
        return res;
    }
};

/*
問說有多少個subarray 他的第一個跟最後一個數字 就是該subarray的最大值
每一個起點我會想知道 我後面有沒有跟我相同的數值 以及比我更大的數值在哪
前面跟我相同的我肯定不要
[145,145,147,148,145,149,147,147,145,147] -> 14 not 16
不確定我後面的是否都符合條件:)
在每個index以前有包含某個val的次數為多少 
可以想到用map把每一個數字的index記錄起來 然後每次從第一個的nextGreater開始比較 看他後面的index是否被包含到 是的話就繼續往後 不是就stop 之後換走到的那個index繼續看他的nextGreater涵蓋了誰
*/
