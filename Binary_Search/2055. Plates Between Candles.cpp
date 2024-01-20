/*
2055. Plates Between Candles
*/

// State Machine: TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> presum(n);
        vector<int> prevPos(n,-1);
        vector<int> nextPos(n,n);
        int sum = 0;
        int pos = -1;
        for(int i = 0; i < n; i++){
            if(s[i] == '|') pos = i;
            if(s[i] == '*') sum += 1;
            prevPos[i] = pos;
            presum[i] = sum;
        }

        pos = n;
        for(int i = n-1; i >= 0; i--){
            if(s[i] == '|') pos = i;
            nextPos[i] = pos;
        }

        vector<int> res(queries.size(),0);
        if(prevPos.size() == 0){
            return res;
        }

        
        for(int i = 0; i < queries.size(); i++){
            int a = queries[i][0];
            int b = queries[i][1];
            int x = nextPos[a], y = prevPos[b];
            if(x <= y){
                res[i] = presum[y] - presum[x];
            }
            
        } 

        return res;

    }
};


// Binary Search : TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        vector<int> pos;
        int n = s.size();
        vector<int> presum(n);
        int sum = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '|') pos.push_back(i);
            if(s[i] == '*') sum += 1;
            presum[i] = sum;
        }

        vector<int> res(queries.size(),0);
        if(pos.size() == 0){
            return res;
        }
        for(int i = 0; i < queries.size(); i++){
            int a = queries[i][0];
            int b = queries[i][1];
           
            auto iter1 = lower_bound(pos.begin(), pos.end(), a);
            auto iter2 = upper_bound(pos.begin(), pos.end(), b);
            iter2 = prev(iter2);
            if(iter2 - iter1 >= 1){
                res[i] = presum[*iter2] - presum[*iter1];
            } 
        
        } 

        return res;

    }
};

/*
給你一組字串用*表示盤子 | 表示蠟燭 
問說query範圍內有多少個盤子被蠟燭包圍
先計算蠟燭的位置 每次query直接二分判斷當下被包圍的蠟燭數量
或者這就是狀態機考題 可以直接先紀錄好位置 O(1)時間找出每次query左右蠟燭
*/
