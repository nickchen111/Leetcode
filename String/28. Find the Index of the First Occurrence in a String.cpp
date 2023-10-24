/*
28. Find the Index of the First Occurrence in a String
*/


// 使用函式做法 TC:O(n+m)，其中 n 是主字符串的長度，m 是子字符串的長度。 SC:O(1)
class Solution {
public:
    int strStr(string haystack, string needle) {
        int ans = haystack.find(needle); 
        if(ans != string::npos){
            return ans;
        }
        else return -1;
    }
};


// Rabin-Karp TC:O(n) SC:O(n)
class Solution {
public:
    int strStr(string haystack, string needle) {
        unordered_map<string, int> map;
        int res = -1;
        int n = haystack.size();
        int m = needle.size();
        
        for(int i = 0; i<=n-m; i++){
            string temp = haystack.substr(i,m);
            map[temp]= i;
            if(temp == needle){
                res = map[temp];
                break;
            }
        }

        return res;
    }
};

//Two pointer TC:O(n*m) SC:O(1)
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle == "") return 0;
        int n = haystack.size();
        int m = needle.size();
        int i = 0;
        int j = 0;
        while(i < n && j < m){
            if(haystack[i] == needle[j]){
                i++;
                j++;
                if(j == m) return i-m;
            }
            else{
                i = i-j+1;//such that it goes backwards till whatever length has been matched 
                j = 0; // and checks from next index and start checking from pattern's beginning
            }
        }
        return -1;
    }
};

//KMP TC:O(m+n) SC:O(m+n)
class Solution {
public:
    int strStr(string haystack, string needle) {
        string s = haystack;
        string p = needle;
        int n = s.size();
        int m = p.size();
        vector<int> suffix = preprocess(p);
        vector<int> dp(n,0);
        dp[0] = (s[0] == p[0]);
        if(m==1 && dp[0] == 1) return 0;
        if(m==0) return 0;
        if(n==0) return -1;

        for(int i = 1; i<n; i++){
            int j = dp[i-1];
            while(j>0 && s[i] != p[j]){
                j = suffix[j-1];
            }
            dp[i] = j+(s[i] == p[j]);
            if(dp[i] == p.size()) return i-p.size()+1;
        }

        return -1;

    }

    //這裡就是1392的預處理
    vector<int> preprocess(string s){
        int n = s.size();
        vector<int> suffix(n,0);
        suffix[0] = 0;
        for(int i = 1; i<n; i++){
            int j = suffix[i-1];
            while(j > 0 && s[i] != s[j]){
                j = suffix[j-1];
            }
            suffix[i] = j+(s[i] == s[j]);
        }

        return suffix;
    }
};


/*
四種做法
1. 引用string find 函式
在 C++ 的 std::string 中，find 函数通常返回 std::string::npos 表示未找到匹配项。
而對於其他容器（例如 std::vector）的 find 函数，通常返回 end()，表示未找到。
所以，string::npos 不等於 end()，而是一個特殊的無效索引值。對於字符串，這通常是 std::string::size_type 的最大值。

2. rabin-karp

3. KMP

4. two pointer
*/
