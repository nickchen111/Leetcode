// TC:O(n) SC:O(n)
class Solution {
    using ll = long long;
public:
    long long bowlSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> L(n, -1), R(n, n);
        stack<int> st;

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[st.top()] < nums[i]) st.pop();
            L[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        while (!st.empty()) st.pop();

        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && nums[st.top()] < nums[i]) st.pop();
            R[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            if (L[i] != -1 && i - L[i] >= 2) ++ans; 
            if (R[i] != n  && R[i] - i >= 2) ++ans;
        }
        return ans;
    }
};
