/*
1849. Splitting a String Into Descending Consecutive Values
*/

// TC:O(2^n) SC:O(2^n)
class Solution {
    int n;
public:
    bool splitString(string s) {
        n = s.size();
        vector<long long> temp;
        return Backtrack(s, 0, temp);
    }
    bool Backtrack(string& s, int cur, vector<long long>& temp){

        
        if(cur == n && temp.size() > 1) return true;

        for(int i = cur; i < n; i++){
            string str = s.substr(cur, i - cur + 1);
            long long num = stoll(str);
            if(num > 1e10) break;
            if(temp.empty() || temp.back() - num == 1){
                temp.push_back(num);
                if(Backtrack(s, i + 1, temp)) return true;
                temp.pop_back();
            }
        }

        return false;
    }
   
};

// Concise 
class Solution {
    int n;
public:
    bool splitString(string s) {
        n = s.size();
        for(int len = 1; len < n; len++){
            string str = s.substr(0,len);
            long long num1 = stoll(str);
            if(num1 >= 1e10) break;
            if(Backtrack(s, len, num1)) return true;
        }
        return false;
    }
    bool Backtrack(string& s, int cur, long long num1){

        
        if(cur == n) return true;

        for(int len = 1; len+cur <= n; len++){
            long long num2 = stoll(s.substr(cur,len));
            if(num2 >= 1e10) break;
            if(num1 - num2 == 1 && Backtrack(s, len+cur, num2)) return true;
        }

        return false;
    }
   
};


/*
切割字串成 遞減序列 並且兩個相鄰差1
Backtrack
10^20 
剪枝小技巧 超過１0個就不用再試了
*/
