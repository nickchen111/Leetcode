/*
3399. Smallest Substring With Identical Characters II
*/

//TC:O(nlgM) SC:O(1)
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.size();
        int left_len = 0; char ch = '#';
        
        auto check = [&](int len) -> bool {
            int cnt = 0;
            if(len == 1) {
                int ch = 0;
                for(int i = 0; i < n; i++) {
                    if(s[i] - '0' != ch) {
                        cnt += 1;
                    }
                    ch ^= 1;
                }
                return min(n-cnt, cnt) <= numOps;
            }
            else {
                // 5/2+1 or 4/2
                for(int i = 0; i < n; i++) {
                    int j = i;
                    while(j < n && s[i] == s[j]) j++;
                    int cur_len = j - i;
                    cnt += (cur_len-1)/(len);
                    i = j - 1;
                }
            }
            return cnt <= numOps;
        };

        int left = 1, right = n;
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(check(mid)) {
                right = mid;
            } 
            else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};
