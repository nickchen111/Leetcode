/*
1461. Check If a String Contains All Binary Codes of Size K
*/

// TC:O(n*k) SC:O(n*k)
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        unordered_set<string> set;
        int n = s.size();
        for(int i = 0; i < n-k+1; i++){
            string str = s.substr(i,k);
            set.insert(str);
        }
        
        //將長度為k的字串0 1所有可能性列出
        //010 000 100 101 110 001 011 111 ... -> 2^k ... 換個念想 只要裡面有2^k次方種那也不用遍歷了哪
        int goal = pow(2,k);
        if(set.size() != goal) return false;
        else return true;
    }
};

/*
此題題意即給你一k值 可以組成各種以他為長度的bit 問是否s 裡面包含所有以他組成的所有可能性
多個字符串的比較~ Bit
用一Hash Set 存放所有k拆出來的可能性
*/
