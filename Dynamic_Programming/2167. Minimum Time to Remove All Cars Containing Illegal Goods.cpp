/*
2167. Minimum Time to Remove All Cars Containing Illegal Goods
*/

// TC:O(n) SC:O(1) 想不到的空間優化
class Solution { 
public:
    int minimumTime(string s) {
        int n = s.length(), ans = n, pre = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') pre = min(pre + 2, i + 1);
            ans = min(ans, pre + n - 1 - i);
        }
        return ans;
    }

};


// 把prefix 去掉稍微優化空間 我認為做到這裡就算是很棒惹
class Solution {
public:
    int minimumTime(string s) {
        int n = s.size();

        vector<int> suffix(n+1); // 0 為旁邊有東西 1 為沒東西
       
        for(int i = n-1; i >= 0; i--){
            if(s[i] == '0') {
                suffix[i] = min(suffix[i+1], n - i - 1);
            }
            else {
                suffix[i] = min(suffix[i+1] + 2, n - i);
            }
        }

        int prefix = (s[0] == '0' ? 0 : 1);
        int res = suffix[0];
        for(int i = 1; i < n; i++){
            res = min(res, prefix + suffix[i]);
            prefix = min(prefix+2, i+1);
        }

        return res;
    }

};


// Three pass basic解法 TC:O(n) SC:O(n) 
class Solution {
public:
    int minimumTime(string s) {
        int n = s.size();

        vector<int> suffix(n+1); // 0 為旁邊有東西 1 為沒東西
        vector<int> prefix(n+1);
        for(int i = n-1; i >= 0; i--){
            if(s[i] == '0') {
                suffix[i] = min(suffix[i+1], n - i - 1);
            }
            else {
                suffix[i] = min(suffix[i+1] + 2, n - i);
            }
        }

        prefix[0] = (s[0] == '0' ? 0 : 1);
        for(int i = 1; i < n; i++){
            if(s[i] == '0') {
                prefix[i] = min(prefix[i-1], i);
            }
            else {
                prefix[i] = min(prefix[i-1]+2, i+1);
            }
        }

        int res = suffix[0];
        for(int i = 1; i < n; i++){
            res = min(res, prefix[i-1] + suffix[i]);
        }

        return res;
    }

};


// 較不優雅寫法 起初覺得要去頭去尾 會比較好判斷，結果反而栽了些Test case TC:O(n) SC:O(n)
class Solution {
public:
    int minimumTime(string s) {
        int n = s.size();
        if(n == 1) {
            if(s[0] == '0') return 0;
            else return 1;
        }

        int count = 0;
        int left = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '1') {
                count += 1;
            }
            else {
                left = i;
                break;
            }
        }

        if(count == n) return count;

        int right = n-1;
        for(int i = n-1; i >= left; i--) {
            if(s[i] == '1') count += 1;
            else {
                right = i;
                break;
            }
        }
        
        if(left == right) return count;

        vector<int> suffix(n); // 0 為旁邊有東西 1 為沒東西
        vector<int> prefix(n);
        for(int i = right; i >= left; i--){
            if(s[i] == '0') {
                suffix[i] = min((i+1 > right ? 0 : suffix[i+1]), (i+1 > right ? 0 : right - i));
            }
            else {
                suffix[i] = (i+1 > right ? 0 : suffix[i+1]) + 2;
            }
        }
        for(int i = left; i <= right; i++){
            if(s[i] == '0') {
                prefix[i] = min((i-1 < 0 ? 0 : prefix[i-1]), (i-1 < 0 ? 0 : i-left));
            }
            else {
                prefix[i] = (i-1 < 0 ? 0 : prefix[i-1]) + 2;
            }
        }

        int res = INT_MAX;
        for(int i = left; i <= right; i++){
            int pre = min((i-1 < 0 ? 0 : prefix[i-1]), (i-1 < 0 ? 0 : i));
            res = min(res, pre + min(suffix[i], right - i + 1));
        }

        return res + count;
    }

};


/*
011111100001000111111000
所以可以去建造一個去判斷說走到某個位置為止將右邊全部合法最小cost
*/
