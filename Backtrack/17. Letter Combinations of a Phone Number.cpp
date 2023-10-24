/*
17. Letter Combinations of a Phone Number
*/

// 10/16 TC:O(4^n) n 是输入数字串的长度 SC:O(4^n)
class Solution {
    vector<string> d2s = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    vector<string> res;
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        string temp = "";
        backtrack(digits,temp,0);
        return res;
    }

    void backtrack(string& digits, string& temp,int cur){
        if(temp.size() == digits.size()){
            res.push_back(temp);
            return;
        }

        for(int i = cur; i<digits.size(); i++){
            for(char c:d2s[digits[i]-'0']){
                temp.push_back(c);
                backtrack(digits,temp,i+1);
                temp.pop_back();
            }
        }
    }
};


//tc: o(4^n)  因為 0 <= digits.length <= 4 所以n很小頂多4  sc: o(4^n + n) 4^n裝答案 n為遞迴stack裝的高度
class Solution {
    vector<string> ans;
    string track;
    vector<string> d2s = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return {};
        }

        //很明顯要用dfs backtrack whatever 且似乎沒辦法優化
        backtrack(digits, 0);

        return ans;
    }
    void backtrack(string& digits, int start){
        // ending condtion
        if(track.size() == digits.size()){
            ans.push_back(track);
            return;
        }

        for(int i = start; i<digits.size(); i++){//就是按照順序去選digit裡的東西
            for(char c: d2s[digits[start]-'0']){
                track.push_back(c);
                backtrack(digits, i+1);
                track.pop_back();
            }
        }

    }
};


//此題想求電話號碼上有各種字元 給你任意電話號碼 組合出他們的排列組合 
//寫的時候卡住 因為多一層轉換不知該用哪種格式好 且要連結到每層遞迴時 那一層的index可以當成是digits 的index 然後利用自己列的表去轉

//dfs time: o(4^n) 因為每個最多都是4個數字  space: o(4^n + n) +n是因為有遞迴 最慘的情況下call stack 
class Solution1 {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        vector<vector<char>> d(10);
        d[0] = {' '};
        d[1] = {};
        d[2] = {'a','b','c'};
        d[3] = {'d','e','f'};
        d[4] = {'g','h','i'};
        d[5] = {'j','k','l'};
        d[6] = {'m','n','o'};
        d[7] = {'p','q','r','s'};
        d[8] = {'t','u','v'};
        d[9] = {'w','x','y','z'};
        vector<string> ans;
        string cur;
        dfs(digits, d, ans, 0, cur);

        return ans;
    }
private:
    void dfs(string digits, vector<vector<char>> d, vector<string>& ans, int l, string& cur){
        if(l == digits.size()){
            ans.push_back(cur);
            return;
        }
        for(auto c:d[digits[l] - '0']){
            cur.push_back(c);
            dfs(digits, d, ans, l+1, cur);
            cur.pop_back();
        }
    }
};
/*
解題思路
1. 將給的string轉成數組存起來
2. 利用dfs的方式將答案建立起來 先run 第0層 大小不符合給的digit size就繼續遞歸下去

*/

//bfs 想做的事 一個vector 為第i個 一個vector為i+1個 不斷把i+1個放入第i個上 
//如果新增了限制會變得很難用 time: o(4^n) 因為每個最多都是4個數字  space: o(2* 4^n) 因為建立了兩個數組 
class Solution2 {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        vector<vector<char>> d(10);
        d[0] = {' '};
        d[1] = {};
        d[2] = {'a','b','c'};
        d[3] = {'d','e','f'};
        d[4] = {'g','h','i'};
        d[5] = {'j','k','l'};
        d[6] = {'m','n','o'};
        d[7] = {'p','q','r','s'};
        d[8] = {'t','u','v'};
        d[9] = {'w','x','y','z'};
        vector<string> ans;
        ans.push_back("");//寫成這樣才不會被算進答案裡
        for(auto digit:digits){ //有幾個數字就跑幾次
            vector<string> temp; //也可以放到外面去  會一直保存先前的data所以如果要這樣寫 就要先將ans給clear掉 之後swap temp才能重新出發呵呵
            for(auto s:ans){
                for(char c:d[digit - '0']){
                    temp.push_back(s+c);
                }
            }
            ans.swap(temp);

        }
        return ans;
    }
};

/*
解題思路
1. 將給的string轉成數組存起來
2. 做bfs 創立一個空間專門for return ans的 一個給他下一個項目
3. 把下一個項目的data丟進解答裡 用回圈的方式得到所有可能的排列組合

*/
