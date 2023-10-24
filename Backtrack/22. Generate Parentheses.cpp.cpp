/*
22. Generate Parentheses
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:
Input: n = 1
Output: ["()"]

Constraints:
1 <= n <= 8
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;


//最好的寫法 backtrack輕輕鬆鬆
class Solution {
    vector<string> result;
    string cur;
public:
    vector<string> generateParenthesis(int n) {
        if(n == 0) return{};
        string cur;
        backtrack(n, n); //剛開始都有n個左括弧 右括弧可以用

        return result;
    }
    void backtrack(int left, int right){
        //思考不合法的狀態有哪些
        if(right < left) return;//右括弧用的比左括弧還多
        if(right < 0  || left < 0) return; //當然不可能用超過
        
        if(left == 0 && right == 0){ //剛好都用完了
            result.push_back(cur);
            return;
        }

        //加左括號的情況
        cur.push_back('(');
        backtrack(left-1, right);
        cur.pop_back();

        //加入右括號的情況
        cur.push_back(')');
        backtrack(left, right-1);
        cur.pop_back();
    }
};

//這一題的思路重點在於遞迴先比較1.左誇胡是否比又誇湖多 當他跑完後沒了才遞迴回來去判斷 2.左誇胡是否比總體數量少 if yes就去＋＋然後跑下個迴圈 

//用自已的做法做不出來
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> temp;
        temp.push_back("(");
        vector<string> result;
        int count = 1; // 遇到( +1, ) -1;
        unordered_map<int, char> str;
        unordered_set<int> set;
        for(int i = 0; i < 2*n; i+=2){
            str[i] = '(';
            str[i+1] = ')';
        }
        dfs(n, 1,set, str,temp,result);

        return result;
    }
    void dfs(int n,int count,unordered_set<int>& set, unordered_map<int, char>& str, vector<string>& temp, vector<string>& result){
        if(temp.size() == 2*n){
            string valid;
            for(auto x:temp){
                valid +=x;
            }
            result.push_back(valid);
            return;
        }
        if(count < 0) return;
        for(int i = 1; i < 2*n; i++){
            if(count < 0) return;
            if(set.find(i) != set.end()) continue;
            if(set.find(i) == set.end()){
            if(str[i] == '(') {
                count++;
                temp.push_back("(");
                set.insert(i);
                dfs(n, count,set, str,temp,result);
                count--;
                temp.pop_back();
                set.erase(i);
            }

            if(str[i] == ')' && count > 0){
                count--;
                temp.push_back(")");
                set.insert(i);
                dfs(n, count,set, str,temp,result);
                count++;
                temp.pop_back();
                set.erase(i);
            }
            else continue;
            }
        }
    }
};

//桑心啦
class Solution1 {
public:
    vector<string> generateParenthesis(int n) {
        int left, right;
        vector<string> result;
        string cur;
        backtrack(n, 0, 0, "", result);

        return result;
    }
    void backtrack(int n, int left, int right, string cur, vector<string>& result){
        if(cur.size() == n*2){
            result.push_back(cur);
        }
        if(left > right) backtrack(n, left, right+1, cur + ")", result);
        if(left < n) backtrack(n, left+1, right, cur + "(", result); 
    }
};


int main(){
    int n =3;
    Solution1 a;
    vector<string> result = a.generateParenthesis(n);
        for (auto str : result) {
        cout << str << endl;
    }
}
