/*
1611. Minimum One Bit Operations to Make Integers Zero
*/

// TC:O(n) SC:O(n)
class Solution {
    unordered_map<string,int> memo;
    unordered_map<string,int> memo2;
public:
    int minimumOneBitOperations(int n) {
        string str = bitset<32>(n).to_string();

        return DFS(str);
    }
    int DFS(string n){
        if(n == "0") return 0;
        if(n == "1") return 1;
        if(memo.find(n) != memo.end()) return memo[n];

        if(n[0] == '0') return DFS(n.substr(1));

        string m = n.substr(1);
        string p = m;
        p[0] = '1';
        for(int i = 1; i<p.size(); i++){
            p[i] = '0';
        }
        memo[n] = helper(m)+1+DFS(p);

        return memo[n];
    }
    int helper(string n){
        if(n == "0") return 1;//翻轉成1
        if(n == "1") return 0;
        if(memo2.find(n) != memo2.end()) return memo2[n];

        if(n[0] == '1') memo2[n] = DFS(n.substr(1)); 
        else {
            string m = n.substr(1);
            string p = m;
            p[0] = '1';
            for(int i = 1; i < p.size(); i++){
                p[i] = '0';
            }
            memo2[n] = helper(m)+1+DFS(p);
        }

        return memo2[n];
    }
};

/*
此題就是先按照題目規則開始推一次
101010 -> 1 (10000) -> 0 (10000) -> 0 00000
       helper(xxxxx). + 1.       + dfs(xxxx) 主函式本身
helper: the operation to convert xxxx to 1000 
1.if leading is 1:dfs(xxx)
2. 0 (xxx)-> 0(100) -> 1 (000)
          helper(xxx)+1+dfs(xxx)
*/
