/*
3306. Count of Substrings Containing Every Vowel and K Consonants II
*/

// 2025.01.26 function越長越合法兩次滑窗寫法 & 三指針one pass寫法 TC:O(n) SC:O(26)
class Solution {
    using LL = long long;
    unordered_map<char, int> ch2num = {{'a',1},{'e',2},{'i',3},{'o',4},{'u',5}}; // 越長越合法
    const int VOWEL = ch2num.size();
    // 輔音的部分就是恰好型滑窗 也是符合越長越合法 也就是有兩個越長越合法的條件
public:
    long long countOfSubstrings(string s, int k) {
        int n = s.size();
        auto atLeastK = [&](int goal) -> LL {
            LL valid_v = 0, valid_c = 0, i = 0, ans = 0;
            unordered_map<char, LL> mp;
            for(LL j = 0; j < n; j++) {
                if(ch2num[s[j]] != 0) {
                    if(mp[s[j]] == 0)
                        valid_v += 1;
                }
                else valid_c += 1; 
                mp[s[j]] += 1;
                while(valid_c >= goal && valid_v == VOWEL) {
                    if(ch2num[s[i]] != 0) {
                        if(mp[s[i]] == 1) valid_v -= 1;
                    }
                    else valid_c -= 1;
                    mp[s[i++]] -= 1;
                }
                ans += i;
            }
            return ans;
        };
        return atLeastK(k) - atLeastK(k+1);
    }
};

class Solution {
    using LL = long long;
    unordered_map<char, int> ch2num = {{'a',1},{'e',2},{'i',3},{'o',4},{'u',5}}; // 越長越合法
    const int VOWEL = ch2num.size();
    // 輔音的部分就是恰好型滑窗 也是符合越長越合法 也就是有兩個越長越合法的條件
public:
    long long countOfSubstrings(string s, int k) {
        int n = s.size();
        LL i1 = 0, i2 = 0, ans = 0, valid_v1 = 0, valid_v2 = 0, valid_c1 = 0, valid_c2 = 0;
        unordered_map<char, LL> mp1, mp2;
        for(LL j = 0; j < n; j++) {
            if(ch2num[s[j]]) {
                if(mp1[s[j]] == 0) valid_v1 += 1;
                if(mp2[s[j]] == 0) valid_v2 += 1;
            }
            else {
                valid_c1 += 1;
                valid_c2 += 1;
            }
            mp1[s[j]] += 1;
            mp2[s[j]] += 1;

            while(valid_v1 == VOWEL && valid_c1 >= k) {
                if(ch2num[s[i1]]) {
                    if(mp1[s[i1]] == 1) valid_v1 -= 1;
                }
                else valid_c1 -= 1;
                mp1[s[i1++]] -= 1;
            }
            while(valid_v2 == VOWEL && valid_c2 >= k+1) {
                if(ch2num[s[i2]]) {
                    if(mp2[s[i2]] == 1) valid_v2 -= 1;
                }
                else valid_c2 -= 1;
                mp2[s[i2++]] -= 1;
            }
            ans += (i1-i2);
        }
        return ans;
    }
};


// TC:O(n) SC:O(26)
class Solution {
    using LL = long long;
    unordered_set<char> set = {'a', 'e', 'i', 'o', 'u'};
public:
    long long countOfSubstrings(string s, int k) {
        return atLeastK(s, k) - atLeastK(s,k+1);
   }
    LL atLeastK(string& s, int k){
        int n = s.size();
        unordered_map<char, int> map;
        int count = 0;
        int vowel = 0;
        int i = 0;
        LL res = 0;
        for(int j = 0; j < n; j++){
            if(set.find(s[j]) != set.end()){
                map[s[j]] += 1;
                if(map[s[j]] == 1) vowel += 1;
            }
            else count += 1;
            
            while(count >= k && vowel == 5){
                res += (LL)(n-j);
                if(set.find(s[i]) != set.end()){
                    map[s[i]] -= 1;
                    if(map[s[i]] == 0) vowel -= 1;
                }
                else count -= 1;
                i++;
            }
        }
        
        return res;
    }
    
};

/*
至少一個aeiou 並且其餘的要剛好k個
去剛好走到k個子音判斷是否有aeiou 以及後面有幾個aeiou
*/
