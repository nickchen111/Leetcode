/*
1415. The k-th Lexicographical String of All Happy Strings of Length n
*/

// 2025.04.13
class Solution {
public:
    string getHappyString(int n, int k) {
        /*
        選擇一個數字 後面每個位置的排列為
        n - i - 1 項 1 << (n - i - 1)
        */
        if (k > 3 * (1 << (n - 1))) return "";
        string ans;
        // cout << "pass";
        for (int i = 0; i < n; i++) {
            // 第一個才有3個可選
            if (ans.empty()) {
                for(int j = 0; j < 3; j++) {
                    int p = 1 << (n - i - 1);
                    if (p >= k) {
                        ans.push_back(j + 'a');
                        break;
                    }
                    k -= p;
                }
            }
            else {
                for(int j = 0; j < 3; j++) {
                    if (j == ans.back() - 'a') continue;
                    int p = 1 << (n - i - 1);
                    if (p >= k) {
                        ans.push_back(j + 'a');
                        break;
                    }
                    k -= p;
                }
            }
        }

        return ans;

    }
};

// Math: TC:O(k) SC:O(k)
class Solution {
    string res;
public:
    string getHappyString(int n, int k) {
        if(k > 3 * pow(2, n-1)) return "";
        solve(n, k-1);

        return res;
    }

    void solve(int m, int k){
        if(m == 0) return;

        int t = k / pow(2, m-1);
        char ch = 'a' + t;
        //避免 a b 是從 a a 轉過來情況 or b b 從 b a 轉過來
        if(res.size() > 0 && res.back() <= ch){
            ch++;
        }
        res.push_back(ch);
        solve(m-1, k - t * pow(2,m-1));
    }
};


// Backtrack TC:O(3*2^(n-1)) SC:O(3*2^(n-1))
class Solution {
    string res;
    int count = 0;
public:
    string getHappyString(int n, int k) {
        string str = "";
        backtrack(n, k, str);

        return res;
    }
    void backtrack(int n, int k, string& str){
        if(str.size() == n){
            count++;
            if(count == k){
                res = str;
            }
            return;
        }

        for(char ch = 'a'; ch <= 'c'; ch++){
            if(str.size() > 0 && str.back() == ch) continue;
            str.push_back(ch);
            backtrack(n, k, str);
            str.pop_back();
        }
        
    }
};

/*
此題說相鄰兩個元素不能重複 要組出按照字典序排序的長度為n 的第k個string為何
1. 單純每個都嘗試的backtrack 3*2^(n-1)次方種
2. 按照題目說法 如果 3*2^(n-1) < k 那就無解 有的話 將 k/ 2^(n-1) = t 會是那一位要往後找的次數 
但是要注意如果前面的字元 比你還小 那你要再多加一位 ex a b -> a c t = 1
ps : k要減一 因為題目算法是1 2 3 ... k 寫的程式是0index算過去

*/
 
