/*
2953. Count Complete Substrings
*/

// TC:O(k*26*n) k 為字符種類數 SC:O(26*n)
class Solution {
public:
    int countCompleteSubstrings(string word, int k) {
        int n = word.size();
        int res = 0;
        
        for(int i = 0; i < n;){
            int j = i + 1;
            while(j < n && abs(word[j] - word[j-1]) <= 2){
                j++;
            }
            res += helper(word.substr(i, j-i), k);
            i = j;
        }

        return res;
    }
    int helper(string s, int k){
        set<char> set(s.begin(), s.end());
    
        // 種類
        int count = 0;
        for(int T = 1; T <= set.size(); T++){
            int len = T*k;
            vector<int> freq(26,0);
            int j = 0;
            for(int i = 0; i+len-1 < s.size(); i++){
                while(j <= i+len-1){
                    freq[s[j]-'a']+=1;
                    j++;
                }

                if(check(freq,k)) count += 1;
                freq[s[i]-'a'] -= 1;
            }
        }

        return count;
    }
    bool check(vector<int>& freq, int k){
        for(int i = 0; i < 26; i++){
            if(freq[i] != 0 && freq[i] != k) return false;
        }

        return true;
    }
};


// TC:O(26*26*n) SC:O(26*n)
class Solution {
    int GetC(char c){
        return c-'a';
    }
    int solve(string& s, int k){
        int n = s.size();
        vector<vector<int>> count(n, vector<int>(26,0));//紀錄在每個長度的時候每個字出現的次數
        int res = 0;
        for(int i = 0; i < n; i++){
            for(int c = 0; c < 26; c++){
                count[i][c] = (i ? count[i-1][c]:0);
            }
            
            count[i][GetC(s[i])]+=1;
            //計算可能會有的字母種類就可以得知要求的長度
            for(int numc = 1; numc <= 26; numc++){
                int j = i-numc*k+1;
                if(j < 0) break;
                bool flag = 1;
                for(int c = 0; c < 26; c++){
                    int countc = count[i][c]- (j > 0 ? count[j-1][c]:0);
                    if(countc != 0 && countc != k){
                        flag = 0;
                        break;
                    }
                }
                if(flag) res++;
            }
        }
        
        return res;
    }
public:
    int countCompleteSubstrings(string word, int k) {
        int n = word.size();
        int i = 0;
        vector<string> candidate;
        while(i < n){
            string cur;
            int j = i;
            cur.push_back(word[i]);
            while( j+1 < n && abs(GetC(word[j+1])-GetC(word[j])) <= 2){
                j++;
                cur.push_back(word[j]);
            }
            
            candidate.push_back(cur);
            i = j+1;
        }
        
        int res = 0;
        for(auto &s:candidate){
            res+=solve(s,k);
        }
        
        return res;
    }
};

/*
此題兩個限制
1.每個字元在此subarray中都只能出現k次
2. 每個相鄰字元不得超過2 
第二個限制很簡單解決 只要 分割字串把有可能的個別處理即可 
第一個限制就單獨寫一個函式處理 首先會想到既然限定大家的次數那麼字串長度就可以預測的到 每個字出現k次總共1~26個字... 那就一個一個去比較並且藉由前綴和概念快速
得知這串子串中是否有次數不等於k的a~z的字元(需每個看過一次)
12/21:
此題更快解法
直接用固定長度的滑窗 要多長取決於 字的種類*K
*/
