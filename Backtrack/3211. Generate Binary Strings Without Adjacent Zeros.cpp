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
