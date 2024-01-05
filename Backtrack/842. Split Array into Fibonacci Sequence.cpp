/*
842. Split Array into Fibonacci Sequence
*/

// TC:O(2^10) SC:O(n)
class Solution {
    vector<int> track;
public:
    vector<int> splitIntoFibonacci(string num) {
        int n = num.size();
        for(int i = 0; i < min(9,n-2); i++){
            if(i == 0 && num[i] == '0'){
                string prev1 = num.substr(0,1);
                string prev2 = "";
                track.push_back(stoll(prev1));
                
                if(backtrack(num, i+1, prev1, prev2)) return track;
                if(!track.empty()) track.pop_back();
                return {};
            }
            else {
                string prev1 = num.substr(0,i+1); 
                string prev2 = "";
                track.push_back(stoll(prev1));
                if(stoll(prev1) > INT_MAX) return {};
                if(backtrack(num, i+1, prev1, prev2)) return track;
                if(!track.empty()) track.pop_back();
            }
        }

        return {};
    }

    bool backtrack(string& num, int cur, string& prev1, string& prev2){
        if(cur == num.size() && track.size() >= 3) return true;
        
        for(int i = cur; i < num.size(); i++){
            if(i-cur+1 > 10) break;
            if(num[cur] == '0'){
                string str = num.substr(cur,1);
                if(prev2 != ""){
                    long long num1 = stoll(str);
                    long long num2 = stoll(prev1);
                    long long num3 = stoll(prev2);
                    if(num2 + num3 == num1){
                        track.push_back(stoll(str));
                        if(backtrack(num, i + 1, str, prev1)) return true;
                        track.clear();
                        return false;
                    }
                }
                else {
                    track.push_back(stoll(str));
                    if(backtrack(num, i + 1, str, prev1)) return true;
                    track.clear();
                    return false;
                }
            }
            else {
                // 17 5 22
                string str = num.substr(cur,i-cur+1);
                if(prev2 != ""){
                    long long num1 = stoll(str);
                    long long num2 = stoll(prev1);
                    long long num3 = stoll(prev2);
                    if(num1 > INT_MAX) break;
                    if(num2 + num3 == num1){
                        track.push_back(stoll(str));
                        if(backtrack(num, i + 1, str, prev1)) return true;
                        track.pop_back();
                    }
                }
                else {
                    track.push_back(stoll(str));
                    if(backtrack(num, i + 1, str, prev1)) return true;
                    track.pop_back();
                }
            }
        }

        return false;
    }
};

/*
切割字串成費氏數列
f[i] + f[i+1] = f[i+2]
不能有leading zero 
如果沒辦法切割返回{}

*/
