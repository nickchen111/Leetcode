/*
1871. Jump Game VII
*/

// iterative -> TLE
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        if(s.back() == '1') return false;
        vector<bool> dp(n);
        dp[0] = true;
        for(int i = minJump; i<=maxJump && i<n; i++){
            if(s[i] == '1') dp[i] = false;
            else dp[i] = true;
        }
        for(int i = 0; i<n; i++){
            if(s[i] == '1') dp[i] = false;
        }

        for(int i = minJump; i<n; i++){
            for(int j = minJump; j<=maxJump; j++){
                if(i-j >=0 && s[i-j] != '1') dp[i] = dp[i-j];
            }
        }

        return dp[n-1];
    }
};

//recursion + memo -> Memory exceed
class Solution {
    int memo[100100];
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        if(s.back() == '1') return false;
        
        //recursion+memo

        return dp(s, minJump, maxJump, 0);
    }
    bool dp(string s, int minJump, int maxJump, int index){
        if(index == s.size()-1) return true;
        if(index >=s.size() || s[index] == '1') return false;
        if(memo[index] != 0) return memo[index]; 
        memo[index] = false;
        for(int i = minJump; i<=maxJump; i++){
            if(dp(s, minJump, maxJump,index+i)) return memo[index] = true;
        }
        return memo[index];//代表他後面走不到直return false;

    }
};

//BFS TC:O(n) SC:O(n)
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        if(s.back() == '1') return false;
        queue<int> q;
        q.push(0);
        int i = 0;
        int cur_max = 0;
        
        //BFS 層級遍歷的概念
        while(!q.empty()){
            i = q.front(); q.pop();
            if(i == n-1) return true;
            for(int j = max(i+minJump,cur_max); j<=min(i+maxJump,n-1); j++){
                if(s[j] != '1') q.push(j);
            }
            cur_max = min(i+maxJump+1, n);
        }

        return false;
    }
};


/*
此題問你給你一個起點 能跳的步數也有限定最小最大值
問你能否跳到最後一個點
i => i+minJump, i+maxJup
ixx{xxx[xx}xxxxxx]
跳到的區間需要標記 但一個一個所需時間太久了 所以想到用diff差分數組 去標記能走到的區間 這樣每次標記只需標他的頭跟尾

此題應該也可以用dp來做
dp[i] 是否可以跳到i這個位置 
取決於dp[i-minJump] 到 i-maxJump
dp[0]從0開始跳是否可以跳到終點
*/
