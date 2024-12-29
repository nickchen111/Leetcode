/*
3403. Find the Lexicographically Largest String From the Box I
*/

// 字符串哈希 TC: O(nlgmaxLen) SC:O(n) 
class Solution {
    using LL = long long;
public:
    string answerString(string word, int numFriends) {
        if (numFriends == 1) return word;
        int n = word.size();
        const LL MOD = 1e9 + 7;
        
        // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        // const int base = uniform_int_distribution<>(8e8, 9e8)(rng); // 随幾 base，防止 hack
        
        const LL base = 499; 
        vector<LL> hash(n+1);
        vector<LL> power(n+1);
        power[0] = 1;
        for(int i = 0; i < n; i++){
            power[i+1] = (power[i]*base) % MOD;
            hash[i+1] = (hash[i]*base + (LL) word[i]) % MOD;
        }

        // 計算區間hash的數值 區間是1-index
        auto sub_hash = [&](int l, int r){
            return ((hash[r] - hash[l] * power[r-l]) % MOD + MOD) % MOD;
        };

        int len = n - numFriends + 1;
        int pos = -1;
        int cur_len = 0;
        char ch = 'a';
        for(auto &c : word) ch = max(ch, c);
        for (int i = 0; i < n; i++) {
            if(pos == -1 && word[i] == ch) {
                pos = i;
                cur_len = len;
            }
            else if(word[i] == ch){
                // x x x x x x 
                int left = 0, right = min(len, n - i);
                while(left < right) {
                    int mid = left + (right - left) /2;
                    // pos = 2, len = 3 x x x x x x 
                    if(sub_hash(pos, pos + mid + 1) == sub_hash(i, i + mid + 1)) {
                        left = mid + 1;
                    }
                    else right = mid;
                }
                if(word[pos + left] < word[i + left]) {
                    // cout << word[pos + left] << ' ' << word[i + left] << ' ' << left << ' ' << i << endl;
                    pos = i;
                    cur_len = min(len, n-i);
                }
            }
        }
        
        return word.substr(pos, cur_len);
    }
};


// TC:O(n*maxLen + nlgn) SC:O(n)
class Solution {
public:
    string answerString(string word, int numFriends) {
        if (numFriends == 1) return word;
        int n = word.size();
        int len = n - numFriends + 1;
        string res;
        for (int i = 0; i < n; i ++) {
            string ss = "";
            for (int j = i; j < n && j - i + 1 <= len; j ++) ss += word[j];
            if(res.empty()) {
                res = ss;
            }
            else {
                int p1 = 0, p2 = 0;
                while(p1 < res.size() && p2 < ss.size()) {
                    if(res[p1] == ss[p2]) {
                        p1 ++, p2++;
                    }
                    else if(res[p1] > ss[p2]) {
                        break;
                    }
                    else {
                        res = ss;
                    }
                }
                if(p2 < ss.size() && p1 == res.size()) {
                    res = p2;
                }
            }
        }
        
        return res;
    }
};
