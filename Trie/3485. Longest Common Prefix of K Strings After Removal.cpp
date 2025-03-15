// TC:O(n * M) M 為 字串平均長度 SC:O(26 * d) d為字典樹深度
class Solution {
    struct TrieNode {
        TrieNode* next[26];
        int cnt;
        TrieNode() {
            for(int i = 0; i < 26; i++) next[i] = NULL;
            cnt = 0;
        }
    };
    TrieNode* root = new TrieNode();
public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        /*
        討論逐個刪除一個字串之後 當下最長的公共前綴是? (需要再加回來) 並且公共前綴只要有兩個string有即可
        用一個hash map 儲存 cnt數量大於k 的 前綴長度數量有哪些 mp[cnt] -> 長度10,9,8....
        這題的words 可以先用Trie存起來
        感覺肯定是兩個大小的 最大 次大的在選擇吧 如果最大剛好是 k 個string共享 一旦刪除他 就會導致 次大會是答案
        */
        int n = words.size();
        for(auto &word : words) {
            TrieNode* node = root;
            for(auto &ch : word) {
                if(node->next[ch - 'a'] == NULL) node->next[ch - 'a'] = new TrieNode();
                node = node->next[ch - 'a'];
                node -> cnt += 1;
            }
        }
        // 確認最大最小       
        int mx = 0, smx = 0, mxcnt = 0, cnt_mx_depth = 0;
        unordered_map<int,int> mp;
        auto dfs = [&](auto &&dfs, TrieNode* node, int depth, bool choose) -> void {
            for(int i = 0; i < 26; i++)  {
                if(node->next[i] != NULL) {
                    if(node->next[i]->cnt >= k) {
                        if (depth > mx && !choose) {
                            cnt_mx_depth = 1;
                            smx = mx;
                            mx = depth;
                            mxcnt = node->next[i]->cnt;
                            choose = true;
                        }
                        else if(depth == mx) {
                            cnt_mx_depth += 1;
                        }
                        else if(depth > mx && choose) {
                            mx = depth;
                            mxcnt = node->next[i]->cnt;
                        }
                        if(depth > smx && (node->next[i]->cnt > k || !choose)) {
                            smx = depth;
                        }
                    }
                    dfs(dfs, node->next[i], depth+1, choose);
                    choose = false;
                }
            }
        };
        dfs(dfs, root, 1, false);
        if(mxcnt > k || cnt_mx_depth > 1) {
            return vector<int>(n, mx);
        }
        if(mx == 0) {
            return vector<int>(n, 0);
        }
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            TrieNode* node = root;
            int depth = 0;
            bool flag = true;
            for(auto &ch : words[i]) {
                node = node->next[ch - 'a'];
                depth += 1;
                if(node->cnt == k && depth == mx) {
                    flag = false;
                }
                node->cnt -= 1;
            }
            ans[i] = flag ? mx : smx;
            node = root;
            for(auto &ch : words[i]) {
                node = node->next[ch - 'a'];
                node->cnt += 1;
            }
        }
        return ans;
    }
};
