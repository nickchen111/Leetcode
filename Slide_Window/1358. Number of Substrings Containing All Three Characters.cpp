/*
1358. Number of Substrings Containing All Three Characters
*/

// TC:O(n) SC:O(3)
class Solution {
public:
    int numberOfSubstrings(string s) {
       
        int count = 0;  
        int n = s.size();
        unordered_map<char,int> window;
        int res = 0;
        int i = 0; int j = 0;
        while(j < s.size()){
            char c = s[j];
            window[c]+=1;
            j++;
            if(window[c] == 1) count++;

            while(count == 3){
                //像這種問有幾種subarray .. substring的答案不要傻傻的加一 而是去計算整個區間 
                res+=(n-j+1);
                char d = s[i];
                window[d]-=1;
                i++;
                if(window[d] == 0) count-=1;
            }
        }

        return res;
    }
};

/*

[x x x x x x x x ]
   i     j.       n
*/
