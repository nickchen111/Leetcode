/*
3303. Find the Occurrence of First Almost Equal Substring
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<int> cal_z(string s){
        int n = s.size();
        int box_l = 0, box_r = 0;
        vector<int> z(n);
        for(int i = 1; i < n; i++){
            if(i <= box_r){
                z[i] = min(z[i-box_l], box_r - i + 1);
            }

            while(i + z[i] < n && s[z[i]] == s[z[i]+i]){
                box_l = i;
                box_r = z[i]+i;
                z[i]++;
            }
        }

        return z;
    }
public:
    int minStartingIndex(string s, string pattern) {
        vector<int> prefix_z = cal_z(pattern + s);
        reverse(s.begin(), s.end());
        reverse(pattern.begin(), pattern.end());

        vector<int> suffix_z = cal_z(pattern + s);
        
        int m = pattern.size();
        int n = s.size();
        int t = suffix_z.size();
        // 5 + 4 = x x x x  (O O) O O O
        for(int i = m; i <= n; i++){
            // -1 代表的是目前這個字可更改所以加入的長度
            if(prefix_z[i] + suffix_z[t-1-i+1] >= m-1){
                return i - m;
            }
        }

        return -1;
    }
};
