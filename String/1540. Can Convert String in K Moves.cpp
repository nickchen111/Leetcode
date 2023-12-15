/*
1540. Can Convert String in K Moves
*/

// TC:O(n) SC:O(26)
class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        int m = s.size();
        int n = t.size();
        if(m != n) return false;
        vector<int> count(26);
        for(int i = 0; i < n; i++){
            count[(t[i] - s[i] + 26) % 26] += 1;
        }

        int res = 0;
        for(int i = 1; i <= 25; i++){
            if(count[i] >= 1){
                res = max(res, i + 26*(count[i]-1));
            }
        }

        return res <= k;
    }
};

//不用vector數組紀錄 直接比較k即可 否則-> Memory Exceed k太大無法handle 
class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        unordered_map<int,int> map;
        int m = s.size();
        int n = t.size();
        if(m != n) return false;
        
        for(int i = 0; i < n; i++){
            if(s[i] != t[i]){
                int cur = (t[i] - s[i]+26) % 26;
                map[cur] += 1;
                bool flag = 0;
                int count = map[cur]-1;  
                //需轉的次數
                if(cur+26*(map[cur]-1) <= k){
                    flag = 1;
                }
                
                else return false;
            }
        }

        return true;
    }
};


/*
此題是說給妳1~k個move 每個move可以將某個字增加那個move的數字
ex 第一個move a + 1 = b 問說能否將s字串轉成t字串
b + 25  = a;
a
*/
