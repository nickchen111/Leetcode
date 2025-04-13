// TC:O(n) SC:O(n)
class Solution {
public:
    string smallestPalindrome(string s) {
        /*
        此題問說 某string 排列組合最小的回文串是啥
        讓我想到構造題 可以去枚舉每種字母 先看長度 如果是奇數 那就是 外圍先放偶數 裡面開始放odd
        如果是偶數 那就是外圍偶數 內圈也要是偶數
        */
        int n = s.size();
        vector<int> cnt(26);
        for(auto &ch : s) {
            cnt[ch - 'a'] += 1;
        }
        string first_half = "";
        for(int i = 0; i < 26; i++) {
            if (cnt[i]) {
                first_half += string(cnt[i] / 2, i + 'a');
                cnt[i] -= cnt[i] - (cnt[i] % 2);
            }
        }
        string middle = "";
        if (n % 2 == 1) {
            for(int i = 0; i < 26; i++) {
                if (cnt[i]) {
                    middle = string(1, i + 'a');
                    cnt[i] -= 1;
                    break;
                }
            }
        }
        
        string second_half = first_half;
        reverse(second_half.begin(), second_half.end());
        
        return first_half + middle + second_half;
        
    }
};
