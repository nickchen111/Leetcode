/*
455. Assign Cookies
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        
        int left = 0;
        int right = 0;
        while(left < g.size() && right < s.size()){
            if(g[left] <= s[right]){
                left++;
                right++;
            }
            else right++;
        }

        return left;

    }
};

// 此題要看兩個數組 第二個數組大於等於第一個數組最多的數量可以是多少
