auto preprocessor = [&](string &s) -> vector<int> { // lsp
    vector<int> preprocessor(string& s){
    int n = s.size();
    vector<int> dp(n);
    
    for(int i = 1; i < n; i++){
        int j = dp[i-1];
        while(j > 0 && s[i] != s[j]) j = dp[j-1];
        dp[i] = j + (s[i] == s[j]);
    }

    return dp;
};
auto kmp = [&](string& s, string& t) -> vector<int> {
    int n = s.size();
    vector<int> dp(n);
    dp[0] = (s[0] == t[0]);
    for(int i = 1; i < n; i++){
        int j = dp[i-1];
        while(j > 0 && s[i] != t[j]) j = lsp[j-1];
        dp[i] = j + (s[i] == t[j]);
    }
    return dp;
};
