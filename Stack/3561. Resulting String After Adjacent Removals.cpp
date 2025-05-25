// TC:O(n) SC:O(n)
class Solution {
public:
    string resultingString(string s) {
        /*
        需要不斷移動 連續的字母 直到最後沒有這種狀況 回傳結果字串
        */
        int n = s.size();
        vector<int> stack;
        for (int i = 0; i < n; i++) {
            int cur = s[i] - 'a';
            if (!stack.empty() && ((stack.back() + 1) % 26 == cur || (cur + 1) % 26 == stack.back())) {
                stack.pop_back();
                continue;
            }
            stack.push_back(cur);
        }
        string ans;
        for (int i = 0; i < stack.size(); i++) ans += (stack[i] + 'a');
        return ans;
    }
};
