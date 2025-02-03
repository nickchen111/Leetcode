// TC:O(n * lg M) M 為removable數組長度 SC:O(n)
class Solution {
public:
    int maximumRemovals(string s, string p, vector<int>& removable) {
        int left = 0, right = removable.size(), m = s.size(), n = p.size();
        auto check = [&](int mid, string& remove) -> bool {
            int i = 0, j = 0;
            if(m - mid < n) return false;
            while(i < m && j < n) {
                if(remove[i] == p[j]) j += 1;
                i += 1;
            }
            return j == n;
        };
        while(left < right) {
            int mid = left + (right - left + 1) / 2;
            string remove(s);
            for(int i = 0; i < mid; i++) {
                remove[removable[i]] = '#';
            }
            if(check(mid, remove)) left = mid;
            else right = mid - 1;
        }
        return left;
    }
};
