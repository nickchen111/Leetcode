/*
2842. Count K-Subsequences of a String With Maximum Beauty
*/

// TC:O(2^n) SC:O(2^n)
class Solution {
    unordered_map<char,int> map;
    long long res = 0;
    int maxSum = 0;
    int k;
    vector<int> count;
    long long M = 1e9+7;
public:
    int countKSubsequencesWithMaxBeauty(string s, int k) {
        this->k = k;
        sort(s.begin(),s.end());
        for(auto a:s){
            map[a]+=1;
        }
        for(auto num:map){
            count.push_back(num.second);
        }
        sort(count.rbegin(),count.rend());
        if(count.size() < k) return 0;
        for(int i = 0; i<k; i++){
            maxSum += count[i];
        }
        
        backtrack(0,0,1,0);
        return res;
    }
    void backtrack(int cur, int sum, long long ret, int picked){
        if(picked > k) return;
        if(picked == k && sum == maxSum){
            res = (res+ret)%M;
            return;
        }
        //優化剪枝
        if(sum + accumulate(count.begin()+cur,count.end(),0) < maxSum) return;

        for(int i = cur; i<count.size(); i++){
            backtrack(i+1,sum+count[i], (ret*count[i])%M,picked+1);
        }
    }
};
