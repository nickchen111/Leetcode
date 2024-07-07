/*
3211. Generate Binary Strings Without Adjacent Zeros
*/

// TC:O(2^n) SC:O(n)
class Solution {
    vector<string> res;
    vector<char> track;
public:
    vector<string> validStrings(int n) {
        track.push_back('1');
        backtrack(n, 1, true);
        track.pop_back();
        track.push_back('0');
        backtrack(n, 1, false);
        
        return res;
    }
    
    void backtrack(int n, int num, bool check){
        if(n == num){
            string t;
            for(auto x : track){
                t += x;
            }
            res.push_back(t);
            return;
        }
        
        if(check){
            track.push_back('1');
            backtrack(n, num+1, true);
            track.pop_back();
            track.push_back('0');
            backtrack(n, num+1, false);
            track.pop_back();
        }
        else {
            track.push_back('1');
            backtrack(n, num+1, true);
            track.pop_back();
        }
    }
};

// Bit TC:O(n*2^n or 2^n) 因為n*1.618^n費氏數列)大致可以當成2^n SC:O(1)
class Solution {
    using LL = long long;
public:
    vector<string> validStrings(int n) {
        vector<string> res;
        LL mask = (1<<n)-1; //用這個將超過n的位數中 數字的前導0去掉
        for(LL i = 0; i < (1<<n); i++){
            LL x = mask ^ i; // i 取反, 保留二進制的n位數
            if(((x>>1)&x) == 0){
                string cur;
                int num = i;
                while(num != 0){
                    if(num & 1) cur = '1' + cur;
                    else cur = '0' + cur;
                    num /= 2;
                }
                if(cur.size() < n){
                    cur = '0' + cur;
                }
                res.push_back(cur);
            }
        } 

        return res;
    }
};
