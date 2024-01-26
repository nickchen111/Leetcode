/*
2311. Longest Binary Subsequence Less Than or Equal to K
*/

// Greedy TC:O(n) SC:O(n)
class Solution {
public:
    int longestSubsequence(string s, int k) {
        int n = s.size();
        
        vector<int> count(n);
        int count0 = 0;
        for(int i = 0; i < n; i++){
            count[i] = count0;
            if(s[i] == '0') count0 += 1;
        }
        string target;
        int temp = k;
        for(int i = 0; i < 32; i++){
            int cur = temp&1;
            if(cur) target = "1" + target;
            else target = "0" + target;
            temp >>= 1;
            if(temp == 0) break;
        }

        int m = target.size();

        if(m > n) return n;
        int res = m - 1 + count[n-m];
        
        if(s.substr(n-m,m) <= target) res = max(res, m + count[n-m]);
      
        return res;
    }
};

// Recursion 從後面取 取到就停 TC:O(n*k) SC:O(n) 
class Solution {
public:
    int longestSubsequence(string s, int k) {
        int n = s.size();
        
        vector<int> count(n);
        int count0 = 0;
        for(int i = 0; i < n; i++){
            count[i] = count0;
            if(s[i] == '0') count0 += 1;
        }
        string target;
        int temp = k;
        for(int i = 0; i < 32; i++){
            int cur = temp&1;
            if(cur) target = "1" + target;
            else target = "0" + target;
            temp >>= 1;
            if(temp == 0) break;
        }

        if(target.size() > n) return n;
        int res = target.size() - 1 + count[n-target.size()];
        for(int i = n-1; i >= 0; i--){
            if(check(i,s,target,0)){
                res = max(res, (int)target.size() + count[i]);
                break;
            }
        }
      
        return res;
    }
    bool check(int i, string& s, string& t, int j){
        if(j == t.size()) return true;
        if(i == s.size()) return false;
        
        
        if(t[j] == '1'){
            if(s[i] == '0') return s.size() - i >= t.size() - j;
            else {
                return check(i+1, s, t, j+1);
            }
        }
        else {
            while(s[i] == '1') i++;
            if(i == s.size()) return false;
            return check(i+1, s, t, j+1);
        }
        

    }
};


// 未優化 TC:O(n*k) SC:O(n)
class Solution {
public:
    int longestSubsequence(string s, int k) {
        int n = s.size();
        
        int res = 1;
        vector<int> count(n);
        int count0 = 0;
        for(int i = 0; i < n; i++){
            count[i] = count0;
            if(s[i] == '0') count0 += 1;
        }
        string target;
        int temp = k;
        for(int i = 0; i < 32; i++){
            int cur = temp&1;
            if(cur) target = "1" + target;
            else target = "0" + target;
            temp >>= 1;
            if(temp == 0) break;
        }
        
        if(target.size() > n) return n;

        for(int i = 0; i < n; i++){
            string str;
            if(i + target.size() -1 < n){
                str = s.substr(i,(int)target.size());
                if(str <= target){
                    res = max(res, (int)target.size() + count[i]);
                }
                else res = max(res, (int)target.size() - 1 + count[i]);
            }
        }
      
        return res;
    }
};


/*
要從既有的binary string s中取出一些數字組成的subsequence 他的十進制表達不能超過k
問說最長可以組成多長
從尾巴開始取k長度的字串 在他之前有多少0那就可以加入答案中
s.length = 1000
k = 1~10^9
首先這題一定要先想到貪心的策略 盡量從後面拿到可以小於等於k的二進位表示 然後看他前面有多少0就全取
1. 無腦每次都從字串中拿target個 看他是否小於等於target 再去算他的前導0數量 從中選個最長的
2. 稍微優化 從後面開始取 一旦取到了就停
3. 只取後面的長度 如果他沒有比target小於等於 後面的答案也不會更優 因為已經有個預設的target-1 + 多少個前導0的答案了 再往前也是將前面的0放進來罷了
x x x x x x 
n=6, m = 4
*/
