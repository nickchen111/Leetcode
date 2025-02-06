/*
1839. Longest Substring Of All Vowels in Order
*/

// 2025.02.06 分組循環
class Solution {
public:
    int longestBeautifulSubstring(string word) {
        int n = word.size(), i = 0, ans = 0;
        // unordered_map<char, int> mp = {{'a', 0}, {'e', 1}, {'i', 2}, {'o',3}, {'u', 4}};
        while(i < n) {
            if(word[i] != 'a') {
                i ++;
                continue;
            }
            int start = i;
            int cnt = 1;
            while(i + 1 < n && word[i] <= word[i+1]) {
                cnt += (word[i] != word[i+1]);
                i += 1;
            }
            if(cnt == 5) {
                ans = max(ans, i - start + 1);
            }
            i ++;
        }
        return ans;
    }
};
// Slide Window + Map
class Solution {
public:
    int longestBeautifulSubstring(string word) {
        unordered_map<int,int> map; // alpha -> freq;
        int n = word.size();
        int j = 1;
        int res = 0;
        for(int i = 0; i < n; i++){
            map[word[i]] += 1;
            while(j < n && word[j] >= word[j-1]){
                map[word[j]] += 1;
                if(map.size() == 5) res = max(res, j - i + 1);//這里的j是合法狀態
                j++;
            }
            map.clear();
            i = j-1;
            j++;
        }

        return res;
    }
};

// Slide Window no need map
class Solution {
public:
    int longestBeautifulSubstring(string word) {
        // no map
        int res = 0;
        int count = 1;
        int j = 0;
        for(int i = 1; i < word.size(); i++){
            if(word[i-1] < word[i]) count++;
            else if(word[i-1] > word[i]){
                j = i; count = 1;//從頭開始計算
            }
            
            if(count == 5) res = max(res, i - j + 1);
        }

        return res;
    }
};


// DP TC:O(n*5) SC:O(6)
class Solution {
public:
    int longestBeautifulSubstring(string word) {
        // DP
        int n = word.size();
        unordered_map<char, int> map{{'a',1},{'e',2},{'i',3},{'o',4},{'u',5}};
        vector<int> dp(6, INT_MIN); // 空 a e i o u
        dp[0] = 0;
        int res = 0;
        for(int i = 0; i < n; i++){
            auto dp_tmp = dp;
            for(int j = 1; j < 6; j++){
                if(map[word[i]] == j)
                    dp[j] = max(dp_tmp[j], dp_tmp[j-1]) + 1;
                else dp[j] = INT_MIN; //不可能發生 在j的位置上結果word[i] 還不是j
            }
            res = max(res, dp[5]);
        }

        return res;
    }
};
