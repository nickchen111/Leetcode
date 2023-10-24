/*
1449. Form Largest Integer With Digits That Add up to Target
*/

//完全背包問題 TC:O(target*9) SC:O(target)
class Solution {
    string dp[5001];
public:
    string largestNumber(vector<int>& cost, int target) {
        int n = cost.size();
        cost.insert(cost.begin(), 0);
        
        //base case 因為有可能cap 太小根本沒人可選 所以都先初始化成無意義的字串
        for(int cap = 1; cap<=target; cap++){
            dp[cap]="#";
        }

        for(int cap = 1; cap<=target; cap++){
            for(int i = 1; i<=9; i++){//背包最後放入的選項
                if(cap < cost[i]) continue;//放不進去
                if(dp[cap-cost[i]] == "#") continue; //不一定有解 也可能太小了
                string temp = dp[cap-cost[i]] + to_string(i);
                //比較這次算出的字串長度是否比之前大 or一樣大但是字首項目比較大
                if(temp.size() > dp[cap].size() || temp.size() == dp[cap].size() && temp > dp[cap])
                    dp[cap] = temp;
            }
        }

        if(dp[target] == "#") return "0";
        else return dp[target];
    }
};

/*
此題為完全背包問題
外層遍歷sum 內層遍歷選項 
突破口在於內層遍歷的那項為背包最後放入的東西 我不在乎前面放了幾個東西或者重複了幾次 
這樣就可以成功包含完全背包問題的概念了 最後按照題意更新dp
*/
