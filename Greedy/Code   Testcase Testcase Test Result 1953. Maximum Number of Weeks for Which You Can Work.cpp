/*
1953. Maximum Number of Weeks for Which You Can Work
*/

// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long numberOfWeeks(vector<int>& milestones) {
        LL res = 0;
        LL total = accumulate(milestones.begin(),milestones.end(), 0LL);
        LL maxVal = *max_element(milestones.begin(), milestones.end());
        if(maxVal <= total/2){
            res = total;
        }
        else {
            res += (total-maxVal)*2;
            res += 1;
        }

        return res;
        
    }
};

/*
0-n-1個專案要做 給你一個數組表示這些專案的number of milestones
每個星期只可以做一個專案裡的一個milestone 並且你每週都必須工作
你不能連續兩週做相同專案

這題數據規模太大一定要用貪心 此題的貪心是沒辦法給你idle的所以看最大的那個數字有沒有超過一半如果有代表他一定做不完
如果沒有就代表所有工作都做得完
*/ 
