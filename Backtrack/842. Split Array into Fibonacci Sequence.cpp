/*
842. Split Array into Fibonacci Sequence
*/

// Fibonacci 4/17
class Solution {
public:
    vector<int> splitIntoFibonacci(string num) {
        int n = num.size();
        
        for(int i = 1; i <= n/2; i++){
            if(i > 10) break;
            long x = stol(num.substr(0,i));
            if(x > INT_MAX) break;
            if(i > 1 && num[0] == '0') break;
            for(int j = 1; j <= n/2; j++){
                if(j > 10) break;
                
                long y = stol(num.substr(i,j));
                if(y > INT_MAX) break;
                if(j > 1 && num[i] == '0') break;

                int nxt = i + j;
                if(nxt == n) break;

                vector<int> res;
                res.push_back(x);
                res.push_back(y);
                long a = x, b = y;
                while(nxt != n){
                    long target = a + b;
                    if(target > INT_MAX) break;
                    string s = to_string(target);
                    int m = s.size();
                    if(m + nxt > n || stol(num.substr(nxt, m)) != target) break;
                    nxt += m;
                    a = b;
                    b = target;
                    res.push_back(target);
                    
                    if(nxt == n) return res;
                }
            }
        }

        return {};
    }
};

/*
長度最多31
代表一個數字最多長度不可以超過10
f1 = f2 = f3
不能有leading zero 除了0本身
回傳可以成功被切割成fibonacci的數組
n = 200
*/


// Fibonacci TC:O(n^2) SC:O(n) n <= 10 
class Solution {
public:
    vector<int> splitIntoFibonacci(string num) {
        int n = num.size();

        for(int i = 1; i <=n/2; i++){
            if(i > 10) break;
            long x = stol(num.substr(0,i));
            if(x > INT_MAX) break;
            if(i > 1 && num[0] == '0') break;

            for(int j = 1; j <= n/2; j++){
                if(j > 10) break;
                long y = stol(num.substr(i,j));
                if(y > INT_MAX) break;
                if(j > 1 && num[i] == '0') continue;

                vector<int> res;
                res.push_back(x);
                res.push_back(y);

                long a = x, b = y, c, pos = i + j;
                bool flag = 1;
                while(flag){
                    c = a + b;
                    if(c > INT_MAX){
                        flag = 0;
                        break;
                    }
                    string z = to_string(c);
                    int len = z.size();
                    if(pos + len > n || num.substr(pos,len) != z){
                        flag = 0;
                        break;
                    }

                    res.push_back(c);
                    a = b;
                    b = c;
                    pos = pos + len;
                }

                if(pos == n && res.size() > 2) return res;
            }
        }

        return {};
    }
};

/*
這題要注意的細節還是挺多的
1.數字長度不超過10
2. 數字長度10但是大小不超過INT_MAX
3. 如果zero開頭長度就只能是1 不合法那就retrun {}
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
