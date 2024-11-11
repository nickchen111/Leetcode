/*
1449. Form Largest Integer With Digits That Add up to Target
*/

// 遞推 + 遞歸
class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        int n = cost.size();
        // TC:O(n*target) SC:(target)
        vector<int> dp(target+1, INT_MIN/2); 
        dp[0] = 0;
        for(int i = 0; i < n; i++) {
            for(int j = cost[i]; j <= target; j++) {
                dp[j] = max(dp[j], dp[j - cost[i]] + 1);
            }
        }

        if(dp[target] < 0) return "0";
        
        int sum = target;
        string res;
        for(int i = n-1; i >=0; i--) {
            while(sum - cost[i] >= 0 && dp[sum] == dp[sum - cost[i]] + 1) {
                res += i+1 + '0';
                sum -= cost[i];
            }
            if(sum == 0) break;
        }

        return res;
        
        /*
        遞歸 TC:O(n*target) SC:(target)
        vector<int> memo(target+1, -1); 
        function<int(int sum)> dfs0 = [&](int sum) -> int {
            if(sum == 0) return 0;
            if(sum < 0) return INT_MIN/2;
            if(memo[sum] != -1) return memo[sum];
            int res = INT_MIN/2;
            for(auto c : cost) {
                res = max(res, dfs0(sum - c) + 1);
            }

            return memo[sum] = res;
        };
        dfs0(target);
        if(memo[target] < 0) return "0";

        string res;
        function<void(int sum)> dfs = [&] (int sum) -> void {
            for(int i = n-1; i >= 0; i--) {
                if(dfs0(sum - cost[i]) + 1 == memo[sum]) {
                    dfs(sum - cost[i]);
                    res += i+1 + '0';
                    return;
                }
            }

            return;
        };
        dfs(target);
        reverse(res.begin(), res.end());
        
        return res == "" ? "0" : res;
        */
    }
};

// 最佳解 TC:O(target*9) SC:O(target) 背包DP + 貪心
class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        cost.insert(cost.begin(), 0);
        vector<int> dp(target+1, INT_MIN/2); // 能夠拼成target的最大長度是多少
        dp[0] = 0;
        for(int i = 1; i <= 9; i++) {
            int num = cost[i];
            for(int j = num; j <= target; j++) {
                dp[j] = max(dp[j], dp[j-num] + 1);
            }
        }
        if(dp[target] < 0) return "0";
        
        string res;
        int j = target;
        // dp[target] 代表他的長度 
        for(int i = 9; i >= 1; i--) {
            int num = cost[i];
            while(j-num >= 0 && dp[j] == dp[j-num] + 1) {
                res += (i+'0');
                j = j-num;
            }
        }

        return res;
    }
};

//完全背包問題 次佳解:TC:O(target*9*m) m為字符串比較的平均長度 SC:O(target)
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
