/*
1638. Count Substrings That Differ by One Character
*/

// 雙序列DP: TC:O(n^2) SC:O(n)
class Solution {
    int left[102][102];
    int right[102][102];
public:
    int countSubstrings(string s, string t) {
        int m = s.size();
        int n = t.size();
        s = "#" + s + "#";
        t = "#" + t + "#";
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(s[i] == t[j]){
                    left[i][j] = left[i-1][j-1] + 1;
                }
                else left[i][j] = 0;
            }
        }

        for(int i = m; i >= 1; i--){
            for(int j = n; j >= 1; j--){
                if(s[i] == t[j]){
                    right[i][j] = right[i+1][j+1] + 1;
                }
                else right[i][j] = 0;
            }
        }

        int res = 0;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(s[i] != t[j]){
                    res += (left[i-1][j-1]+1)*(right[i+1][j+1]+1);
                }
            }
        }

        return res;
    }
};

// Brute force TC:O(n^2*26*n) SC:O(n^2)
class Solution {
public:
    int countSubstrings(string s, string t) {
        unordered_map<string,int> map;
        for(int i = 0; i < t.size(); i++){
            for(int j = i; j < t.size(); j++){
                string cur = t.substr(i,j-i+1);
                map[cur] += 1;
            }
        }

        unordered_map<string,int> map2;
        for(int i = 0; i < s.size(); i++){
            for(int j = i; j < s.size(); j++){
                string cur = s.substr(i,j-i+1);
                map2[cur] += 1;
            }
        }
        int res = 0;
        for(auto & p : map2){
            for(int i = 0; i < p.first.size(); i++){
                for(char ch = 'a'; ch <= 'z'; ch++){
                    if(p.first[i] == ch) continue;
                    string str = p.first;
                    str[i] = ch;
                    if(map.find(str) != map.end()){
                        res += map[str]*p.second;
                    }
                }
            }
        }

        return res;
        
    }
};

/*
此題要找說某個string s的substring任意換一個字 可以變成string t的 substring
有多少種選法
當下想到兩個 1. hash set 2. DP
dp[i][j] 可以知道說 1:i 1:j 是否相同 相同的長度為多長
這題的突破點還是在於說要想到雙序列型DP 如果確定了一個不同點 我會想知道他的左邊是否相同 右邊是否相同
[x x  z z i z z z x x] -> left+1 * right+1
[y y  z z j z z z y y]
*/
