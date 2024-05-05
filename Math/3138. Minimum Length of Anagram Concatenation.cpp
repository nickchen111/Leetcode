/*
3138. Minimum Length of Anagram Concatenation
*/

//最佳解 TC:O(26*lgn*lgn + n*26) SC:O(26*n)
class Solution {
    int count[100005][26];
    int n;
public:
    int minAnagramLength(string s) 
    {
        n = s.size();
        s = "#"+s;
        
        for (int i=1; i<=n; i++)
        {
            for (int j=0; j<26; j++)
                count[i][j] = count[i-1][j]+((s[i]-'a')==j);
        }
        
        vector<int>arr;
        // lgn 類似埃氏篩
        for (int i=1; i*i<=n; i++)
        {
            if (n%i!=0) continue;
            if (check(i)) return i;
            if (check(n/i)) arr.push_back(n/i);            
        }
        
        return arr.back();        
    }
    
    bool check(int m)
    {
        for (int i=m; i<=n; i+=m)
        {
            int k = i/m;
            for (int j=0; j<26; j++)
                if (count[i][j]!=count[m][j]*k)
                    return false;
        }
        return true;
    }
};

// 數學證明時間複雜度lgn解 TC:O(nlgn) SC:O(26)
class Solution {
public:
    int minAnagramLength(string s) {
        int n = s.size();
        for(int i = 1; i <= n; i++){
            if(n % i == 0 && check(s,i)){
                return i;
            }
        }

        return n;
    }
    bool check(string& s, int k){
        int n = s.size();
        vector<int> count(26,0);
        for(int i = 0; i < k; i++){
            count[s[i]-'a'] += 1;
        }

        for(int i = k; i < n; i += k){
            vector<int> count2(26,0);
            for(int j = i; j < i + k; j++){
                count2[s[j]-'a'] += 1;
            }
            for(int j = 0; j < 26; j++){
                if(count[j] != count2[j]) return false;
            }
        }

        return true;
    }
};


// TC:O(n) SC:O(26)
class Solution {
public:
    int minAnagramLength(string s) {
        vector<int> count(26,0);
        int n = s.size();
        for(int i = 0; i < n; i++){
            count[s[i]-'a']  += 1;
        }
        
        int res = n;
        int target = 0;
        int idx = -1;
        for(int i = 0; i < n; i++){
            if(count[i] != 0){
                target = count[i];
                idx = i;
                break;
            } 
        }
        for(int i = idx+1; i < 26; i++){
            if(count[i] != 0){
                target = gcd(target, count[i]);
            }
        }
        
        res = n /target;
        
        return res;
    }
};

/*
求出所有用過的字母的最大公因數

*/
