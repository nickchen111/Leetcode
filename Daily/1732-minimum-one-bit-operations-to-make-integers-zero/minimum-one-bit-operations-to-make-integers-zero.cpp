class Solution {
    unordered_map<string,int> memo1;
    unordered_map<string,int> memo2;
public:
    int minimumOneBitOperations(int n) {
        string s;
        while(n != 0){
            int cur = (n&1);
            s = s + to_string(cur);
            n /= 2;
        }
        if(s.size() == 0) s += "0";
        reverse(s.begin(), s.end());
        
       

        return DFS(s);
    }

    //將他都改成0
    int DFS(string n){
        if(n == "0") return 0;
        if(n == "1") return 1;
        if(memo1.find(n) != memo1.end()) return memo1[n];

        if(n[0] == '0') return DFS(n.substr(1));
        //開頭肯定是1 後面的要怎改 1000這種的
        string m = n.substr(1);
        string p = m;
        p[0] = '1';
        for(int i = 1; i < p.size(); i++){
            p[i] = '0';
        }

        memo1[n] = helper(m) + DFS(p) + 1;

        return memo1[n];
    }

    //幫助將1 後面那串都改成10000這種的
    int helper(string n){
        if(n == "0") return 1;//翻轉成1
        if(n == "1") return 0;
        if(memo2.find(n) != memo2.end()) return memo2[n];

        if(n[0] == '1') memo2[n] = DFS(n.substr(1));
        else {
            //有個開頭是0 希望將他翻成1 首先後面要都是10000這種的
            string m = n.substr(1);
            string p = m;
            p[0] = '1';
            for(int i = 1; i < p.size(); i++){
                p[i] = '0';
            } 
            memo2[n] = helper(m) + 1 + DFS(p);
        }

        return memo2[n];
    }
};

/*
101011 -> 000000
需要先將次高位變成1 其他變成0 hmmmm 那麼後面幾位要如何做才能都變成0
就開始有感覺是一個recursion問題
1011 -> 0000 
首先可以將最低位直接變成 0 我們想變成 1100 
011 -> 100 
011 -> 010 這時候我就可以改了 110
110 -> 100 -> 111 -> 101 -> 100這樣轉
n總共會有9位
*/