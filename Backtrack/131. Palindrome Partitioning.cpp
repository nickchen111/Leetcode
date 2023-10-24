/*
131. Palindrome Partitioning
*/


//用雙指針去判斷回文串 一兩個還行 但有很多要判斷速度會慢
class Solution {
    //這樣每次都要判斷一次是否回文串 時間複雜度會比較高
    vector<vector<string>> ans;
    vector<string> track;
public:
    vector<vector<string>> partition(string s) {
        backtrack(s, 0);

        return ans;
    }
    void backtrack(string& s, int start){
        if(start == s.length()){
            ans.push_back(track);
            return;
        }
        for(int i = start; i < s.size(); i++){
            if(!isValid(s, start, i)) continue;
            //如果符合的話加進去解答的track然後繼續切割
            track.push_back(s.substr(start, i-start+1));// substring會包含自己開始算喔
            backtrack(s, i+1);
            track.pop_back();//撤銷 for loop會在試更多切法
        }
    }
    
    //判斷是否為回文串
    bool isValid(string& s, int lo, int hi){
        while(lo < hi){
            if(s[lo] != s[hi]) return false;
            lo++;
            hi--;
        }
        return true;
    }
};



//有點類似用dp預先處理 這樣在run的時候就不用每次都乘上回文判斷的n了
class Solution {
    //改成用dp數組去紀錄回文串狀態 就可以直接取用
    int dp[16][16];
    vector<vector<string>> ans;
    vector<string> track;
public:
    vector<vector<string>> partition(string s) {
        //dp建立回文串判斷數組
        for(int i = 0; i<s.size(); i++){
            dp[i][i] = 1;
        }
        for(int i = 0; i<s.size()-1; i++){
            if(s[i] == s[i+1]){
                dp[i][i+1] = 1;
            }
        }
        for(int len = 3; len <= s.size(); len++){
            for(int i = 0; i+len-1 < s.size(); i++){// 頭的index
                int j = i+len-1;//尾巴的index
                if(s[i] == s[j] && dp[i+1][j-1]){
                    dp[i][j] = true;
                }
                else dp[i][j] = false;
            }
        }

        backtrack(s, 0);

        return ans;
    }
    void backtrack(string& s, int start){

        if(start == s.length()){
            ans.push_back(track);
            return;
        }
        for(int i = start; i < s.size(); i++){
            if(dp[start][i]){
                track.push_back(s.substr(start, i-start+1));
                backtrack(s, i+1);
                track.pop_back();
            } 
        }
    }
    

};

/*
此題需要遍歷所有的情況 可以用回溯來做

第一個解法（使用回溯法）：

時間複雜度：
在最壞情況下，字符串s的所有可能分割方式都將被嘗試，因此時間複雜度是指數級別的，即O(2^n)，其中n是字符串s的長度。
在每次回溯中，都要調用isValid函數來檢查子串是否是回文串，這需要O(n)的時間。因此，總體時間複雜度是O(2^n * n)。

空間複雜度：
空間複雜度主要來自回溯過程中的遞歸調用堆棧和track數組。在最壞情況下，回溯的遞歸深度將達到n，因此空間複雜度是O(n)。
此外，ans數組和track數組都將存儲結果，它們的總大小也是O(n)級別的。
因此，總體空間複雜度是O(n)。

第二個解法（使用動態規劃）：

時間複雜度：
在此解法中，首先使用動態規劃來填充dp數組，以檢測字符串s的所有回文子串。這個過程需要O(n^2)的時間，其中n是字符串s的長度。
接下來，使用回溯法來生成所有回文分割方式，回溯過程的時間複雜度取決於回文分割的數量。在最壞情況下，所有可能的回文分割方式都將被嘗試，這仍然需要O(2^n)的時間。
總體時間複雜度是O(n^2 + 2^n)。在實際情況下，這個解法的效率優於第一個解法。

空間複雜度：
空間複雜度主要來自dp數組、回溯過程中的遞歸調用堆棧、ans數組和track數組。dp數組佔用O(n^2)的空間，回溯過程中的遞歸堆棧佔用O(n)的空間，ans和track數組的總大小也是O(n)級別的。
總體空間複雜度是O(n^2)。
總結來說，第二個解法在時間複雜度和空間複雜度方面都相對優於第一個解法，特別是在處理大型輸入時。這是因為第二個解法使用動態規劃來預處理回文子串，從而減少了回溯過程中的冗余計算。
*/
