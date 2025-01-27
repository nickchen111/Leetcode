/*
438. Find All Anagrams in a String
*/

// 2025.01.27 定長 與 不定長
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // 定長寫法
        int n = s.size(), m = p.size(), valid = 0, i = 0, target = 0;
        vector<int> cnt1(26), cnt2(26), ans;
        for(auto &ch : p) {
            if(++cnt2[ch - 'a'] == 1) target += 1;
        }
        for(int j = 0; j < n; j++) {
            if(++cnt1[s[j] - 'a'] == cnt2[s[j] - 'a']) valid += 1;
            else if((cnt1[s[j] - 'a'] == cnt2[s[j] - 'a'] + 1) && cnt2[s[j] - 'a']) valid -= 1;
            if(j - i + 1 == m) {
                if(valid == target) ans.push_back(i);
                if((cnt1[s[i] - 'a'] == cnt2[s[i] - 'a'] + 1) && cnt2[s[i] - 'a']) valid += 1;
                else if(cnt1[s[i] - 'a'] == cnt2[s[i] - 'a'] && cnt2[s[i] - 'a']) valid -= 1;
                cnt1[s[i++] - 'a'] -= 1;
            }
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // 不定長
        vector<int> cnt(26), ans;
        for(auto &ch : p) cnt[ch - 'a'] += 1;
        int i = 0, n = s.size(), m = p.size();
        for(int j = 0; j < n; j++) {
            cnt[s[j] - 'a'] -= 1;
            while(cnt[s[j] - 'a'] < 0) {
                cnt[s[i++] - 'a'] += 1;
            }
            if(j - i + 1 == m) ans.push_back(i);
        }
        return ans;
    }
};


//slide window TC:O(n) SC:O(k)
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size();
        int m = p.size();
        unordered_map<char,int> need,window;
        for(auto s:p){
            need[s]+=1;
        }
        vector<int> res;
        int left = 0; int right = 0; int valid = 0;
        while(right< n){
            char d = s[right];
            right++;
            if(need.count(d)){
                window[d]+=1;
                if(window[d] == need[d]) valid+=1;
            }

            while(right-left == m){
                if(valid == need.size()) res.push_back(left);
                char c = s[left];
                left++;
                if(need.count(c)){
                    if(window[c] == need[c])
                        valid-=1;
                    window[c]-=1;
                }
            }
        }

        return res;
    }
};

/*
此題是想問說如果一字串中包含一個字串的異位詞anagram 請返回他的起始索引位置
仍然是需要一個valid 去紀錄ok的結果 跟need 紀錄需要什麼
1.用模板先想出何時該擴大何時該縮小
2.什麼位置可以將答案更新
*/
