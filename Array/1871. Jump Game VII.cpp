/*
1871. Jump Game VII
*/

//diff TC:O(n) SC:O(n)
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        if(s.back() == '1') return false;
        vector<int> diff(n+1);//因為減一的diff會在跳到極限的地方下一位減一 所以可能會越界 需要加一

        diff[0+minJump] = 1;
        diff[0+maxJump+1] = -1;
        int reach = 0;
        for(int i = 1; i <n; i++){
            reach+=diff[i];
            if(reach == 0) continue;
            if(s[i] == '1') continue;//代表不能以他們為點再出發

            if(i+minJump<=n) diff[i+minJump] +=1;
            if(i+maxJump+1<=n) diff[i+maxJump+1] -=1;
        } 
        return reach;
    }
};

//BFS+visited+little tip to enhance time complexity
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        if(s.back() == '1') return false;
        vector<bool> visited(n,0);
        visited[0] = true;
        queue<int> q;
        q.push(0);
        //BFS
        int cur_max = 0;
        while(!q.empty()){
            int cur = q.front();
            if(cur == n-1) return true;
            q.pop();
            for(int i = max(cur_max,cur+minJump); i<=min(cur+maxJump,n-1); i++){
                if(s[i] != '1' && visited[i] == false){
                    q.push(i);
                    visited[i] = true;
                }
                cur_max = min(cur+maxJump,n);
            }
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
*/
