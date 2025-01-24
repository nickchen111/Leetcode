/*
3325. Count Substrings With K-Frequency Characters I
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int n = s.size();
        vector<int> cnt(26);
        int valid = 0, i = 0, ans = 0;
        for(int j = 0; j < n; j++) {
            cnt[s[j] - 'a'] += 1;
            if(cnt[s[j] - 'a'] >= k) valid += 1;
            while(valid == 1) {
                ans += (n - j);
                if(cnt[s[i] - 'a'] == k) valid -= 1;
                cnt[s[i++] - 'a'] -= 1;
            }
        }
        return ans;
    }
};

// 第二種寫法
class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int ans = 0, left = 0, cnt[26]{};
        for (char c : s) {
            cnt[c - 'a']++;
            while (cnt[c - 'a'] >= k) {
                cnt[s[left] - 'a']--;
                left++;
            }
            ans += left;
        }
        return ans;
    }
};
