/*
3035. Maximum Palindromes After Operations
*/

// TC:O(nlgn+n*m) SC:O(n)
class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        vector<int> count(26,0);
        for(auto str : words){
            for(auto ch : str){
                count[ch-'a'] += 1;
            }
        }

        int chance = 0;
        for(auto num : count){
            chance += num/2;
        }

        auto cmp = [](const string& a, const string& b){
            return a.size() < b.size();
        };

        sort(words.begin(), words.end(), cmp);
        int res = 0;
        for(auto str : words){
            int m = str.size()/2;
            chance -= m;
            if(chance >= 0) res += 1;
            else break;
        }
        
        return res;
    }
};

/*
這題說可以讓你任意交換數組中字串的字元 任意次 問說交換後的結果可以組成多少個回文串
1. 可以很明顯想到要將所有字元出現頻率做統計 2. 但是要想到先填入較短的字串長度是重點 假設你剩四個a 還有一些1個的字元
現在有4長度的空格跟6長度的空格 這時候就要先填入4長度
在實作過程中其實只需在乎左半邊的數量
*/
