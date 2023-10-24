// 241. Different Ways to Add Parentheses

// DC: TC:O(2^n) SC:O(2^n)
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> res;
        vector<int> val1;
        vector<int> val2;

        for(int i = 0; i < expression.size(); i++){
            if(expression[i] != '+' && expression[i] != '-' && expression[i] != '*') continue;

            val1 = diffWaysToCompute(expression.substr(0, i));
            val2 = diffWaysToCompute(expression.substr(i+1));

            for(int x: val1){
                for(int y:val2){
                    if(expression[i] == '+') res.push_back(x+y);
                    else if(expression[i] == '-') res.push_back(x-y);
                    else if(expression[i] == '*') res.push_back(x*y);
                }
            }
        }
        //代表recursion到只有數字的階段 
        if(res.empty()) res.push_back(stoi(expression));

        return res;
    }
};

//DP: TC:O(n^3) SC:O(n^2)
class Solution {
    vector<int> nums;
    vector<char> ops;
    vector<int> memo[21][21];//從i到j可以產生的結果有哪些 
public:
    vector<int> diffWaysToCompute(string expression) {
        //先對字串進行分類裡面必定是n 個 數字 n-1個運算符
        for(int i = 0; i<expression.size(); i++){
            int j = i;
            while(j < expression.size() && isdigit(expression[j])){
                j++;
            }
            nums.push_back(stoi(expression.substr(i,j-i)));
            if(j < expression.size()) ops.push_back(expression[j]);
            i = j;
        }

        // how to start coding 
        int n = nums.size();
        helper(0,n-1);//定義為可以算出給定的區間內括號各種可能結果有哪些

        return memo[0][n-1];
    }

    void helper(int a, int b){
        //base case
        if(a == b){
            memo[a][b] = {nums[a]};
            return;
        }

        if(!memo[a][b].empty()) return;

        //去分析有運算符的狀況所以只會到b-1
        for(int i = a; i<b; i++){
            helper(a,i);
            helper(i+1,b);

            for(int x:memo[a][i]){
                for(int y:memo[i+1][b]){
                    if(ops[i] == '+') memo[a][b].push_back(x+y);
                    else if(ops[i] == '-') memo[a][b].push_back(x-y);
                    else if(ops[i] == '*') memo[a][b].push_back(x*y);
                }
            }
        }
    }
};


/*
此題的核心思想是用merge sort的概念去思考
2*3-4*5
(2)*(3-4*5)->可以再進一步分 
(2*3)-(4*5)->也可以進一步再分
分到都只剩一個數字以後再根據運算符來治
有三種寫法
1.從上往下看的遞歸 DP
2.從下往上看的區間型dp:想像最後一步化簡是在什麼樣的情況下 
也就可以把問題簡化大問題變小問題
3. DC 
*/
