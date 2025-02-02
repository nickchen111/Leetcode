// TC:O(26 * n) SC:O(26 * n)
class Solution {
public:
    string minCostGoodCaption(string s) {
        int n = s.size();
        if (n < 3) return "";

        vector<vector<int>> memo(n, vector<int>(26, -1));
        // vector<vector<int>> nxt(n, vector<int>(26, 26));

        auto dfs = [&](auto && dfs, int i, int j) -> int {
            if (i == n) return 0;
            if (memo[i][j] != -1) return memo[i][j];

            int cost1 = abs(s[i] - 'a' - j) + dfs(dfs, i + 1, j);
            int cost2 = INT_MAX, best_k = 26;

            if (i <= n - 6) {
                for (int k = 0; k < 26; k++) {
                    int tmp = dfs(dfs, i + 3, k) +
                              abs(s[i] - 'a' - j) +
                              abs(s[i + 1] - 'a' - j) +
                              abs(s[i + 2] - 'a' - j);
                    if (tmp < cost2) {
                        cost2 = tmp;
                        best_k = k;
                    }
                }
            }

            if((cost2 == cost1 && best_k > j) || cost2 > cost1){
                memo[i][j] = cost1;
                // nxt[i][j] = j;
            }
            else {
                memo[i][j] = cost2;
                // nxt[i][j] = best_k;
            }
            return memo[i][j];
        };

        int min_j = 0, min_cost = INT_MAX;
        for (int j = 0; j < 26; j++) {
            int cost = dfs(dfs, 0, j);
            if (cost < min_cost) {
                min_cost = cost;
                min_j = j;
            }
        }
        string ans;
        auto print_ans = [&](auto &&print_ans, int i, int j) -> void {
            if(i == n) return;
            int bestCost = dfs(dfs, i, j);
            int cand1 = 26, cand2 = 26;
            if(i <= n - 6) {
                int base = abs(s[i] - 'a' - j) + abs(s[i + 1] - 'a' - j) + abs(s[i + 2] - 'a' - j);
                for(int k = 0; k < 26; k++) {
                    if(bestCost == dfs(dfs, i + 3, k) + base) {
                        cand1 = k;
                        break;
                    }
                }
            }
            if(bestCost == dfs(dfs, i + 1, j) + abs(s[i] - 'a' - j)) {
                cand2 = j;
            }
            if(cand1 < cand2) {
                ans += string(3, j + 'a');
                print_ans(print_ans, i + 3, cand1);
            }
            else {
                ans.push_back(j + 'a');
                print_ans(print_ans, i + 1, j);
            }
            
        };
        print_ans(print_ans, 0, min_j);
        return ans;
        // string ans(n, ' ');
        // int i = 0, j = min_j;
        // while (i < n) {
        //     ans[i] = 'a' + j;
        //     int k = nxt[i][j];
        //     if (k == j) {
        //         i++;
        //     } else {
        //         ans[i + 1] = ans[i];
        //         ans[i + 2] = ans[i];
        //         i += 3;
        //         j = k;
        //     }
        // }
        

        return ans;
    }
};


/*
可以將字母往前or往後 問說最少做幾次符合所謂每個字母連續出現三次 並且要回傳字典序最小的答案 感覺是輸出具體方案的dp

這裡遇到的問題就是如果一個字母在string中已經出現連續三次 那麼其他分散的字母就可以不理他 他已達成任務
如果要從已知的字母判斷當下該構造什麼字就太複雜了 所以直接枚舉26個字母 
再來就是判斷之後的字是否要跟當前一樣，如果相同就往後移一格，不同的話就枚舉0-25 
難點在於要如何輸出具體方案 這裡如果寫一個print_ans 也可以但其實也可以直接在dfs過程中紀錄每個狀態指向的下個字母最方便
第二個難點是要想到枚舉的第二個狀態機參數要是當前要改的字母 不要跟之前的有關，跟之前的有關程式碼會比較難寫
"owsjeo"
"ylrtdmm"
"piuoeeo"
"oweaxihc"
*/
