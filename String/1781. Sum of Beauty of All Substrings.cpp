/*
1781. Sum of Beauty of All Substrings
*/


// Vector TC:O(n^2*26) SC:O(26)
class Solution {
public:
    int beautySum(string s) {
        int n = s.size();
        int res = 0;

        for(int i = 0; i < n; i++){
            vector<int> count(26,0);
            for(int j = i; j < n; j++){
                count[s[j]-'a'] += 1; 
                //可以開始算是否出現最多次的數字減去頻率最小的數字合法
                int maxFreq = 0;
                int minFreq = INT_MAX;
                for(int k = 0; k < 26; k++){
                    if(count[k] != 0){
                        minFreq = min(minFreq, count[k]);
                        maxFreq = max(maxFreq, count[k]);
                    }  
                }

                res  += (maxFreq - minFreq);
            }
        }

        return res;
    }
};

// Map TC:O(n^2&distinct character) SC:O(distinct Character)
class Solution {
public:
    int beautySum(string s) {
        int n = s.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            unordered_map<char, int> count;
            for(int j = i; j < n; j++){
                count[s[j]] += 1;
                int minFreq = INT_MAX;
                int maxFreq = 0;
                for(auto &p : count){
                    minFreq = min(minFreq, p.second);
                    maxFreq = max(maxFreq, p.second);
                }
                res += (maxFreq - minFreq);
            }
        }

        return res;
    }
};

/*
此題定義了某個substring 總和會是最高頻率的字母減去最低頻率字母
問說所有substring加總為多少
高頻率低頻率問題
n = 500 每到一個substring 遍歷26 判斷誰是最高與最低
vector<int> count(26,0);
n^2^26
map<int,int> map
*/
