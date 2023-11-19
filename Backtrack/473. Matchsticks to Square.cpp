/*
473. Matchsticks to Square
*/

// TC:O(2^n) SC:O(n)
class Solution {
    int target;
    int k = 4;
    bool flag=0;
    vector<bool> visited;
public:
    bool makesquare(vector<int>& matchsticks) {
        int n = matchsticks.size();
        if(n == 0) return false;
        target = accumulate(matchsticks.begin(),matchsticks.end(),0);
        if(target%4 != 0) return false;
        target/=4;

        visited.resize(n);
        sort(matchsticks.begin(),matchsticks.end());
        backtrack(matchsticks,0,0,0);

        return flag;
    }
    void backtrack(vector<int>& matchsticks, int cur, int sum, int count){
        if(sum == target){
            backtrack(matchsticks,0,0,count+1);
            return;
        }
        if(sum > target) return;
        if(count == k){
            flag = true;
            return;
        }
        if(flag) return;
        if(cur == matchsticks.size()) return;

        for(int i = cur; i<matchsticks.size(); i++){
            if(visited[i] == 1) continue;
            if(i > cur && visited[i-1] == 0 && matchsticks[i] == matchsticks[i-1]) continue;
            visited[i] = 1;
            sum+=matchsticks[i];
            backtrack(matchsticks,i+1,sum,count);
            sum-=matchsticks[i];
            visited[i] = 0;
        }
    }
};
