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
        解法1:
        討論逐個刪除一個字串之後 當下最長的公共前綴是? (需要再加回來) 並且公共前綴只要有兩個string有即可
        用一個hash map 儲存 cnt數量大於k 的 前綴長度數量有哪些 mp[cnt] -> 長度10,9,8....
        這題的words 可以先用Trie存起來
        感覺肯定是兩個大小的 最大 次大的在選擇吧 如果最大剛好是 k 個string共享 一旦刪除他 就會導致 次大會是答案
        
        解法2: 
        1.排序: 把任意k個變成考慮連續k個，並且只需要考慮前後兩個就好，夾在中間的肯定都是一樣的
        2. 排序後 整個子數組LCP =LCP(前後兩個的LCP) -> 把 k個字串轉成2個字串
        3. 如果不刪除，那麼答案是多少 就是每個子數組取最大值就是不刪除的答案
        4. 紀錄最大的LCP對應的子數組 [mx_i, mx_i+k-1]
           紀錄次大的LCP對應的子數組 [mx2_i, mx2_i+k-1]
        5. 考慮刪除一個字符串
            分類討論: 
            a.如果刪除的字符串不在[mx_i, mx_i+k-1]裡面，那麼就是不刪除的答案，及最大LCP
            b.如果刪除的字符串不在[mx2_i, mx2_i+k-1]中，答案就是次大LCP(並且刪除的會在最大而且最大剛好是k string個)
            c. 如果刪除的字符串在最大又在次大, 那麼答案是? 就是跑DFS某條string更新了兩次的狀況(次大LCP也是最大LCP前綴)，答案會是不包含最大的次大
            但這個也會是次大LCP, mx >= mx2 去掉任意一條 取交集還會是次大
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

// 解法2: LCP + Sort TC:O(L / n * nlgn = L lgn) SC:O(n)
class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        /*
        解法1
        討論逐個刪除一個字串之後 當下最長的公共前綴是? (需要再加回來) 並且公共前綴只要有兩個string有即可
        用一個hash map 儲存 cnt數量大於k 的 前綴長度數量有哪些 mp[cnt] -> 長度10,9,8....
        這題的words 可以先用Trie存起來
        感覺肯定是兩個大小的 最大 次大的在選擇吧 如果最大剛好是 k 個string共享 一旦刪除他 就會導致 次大會是答案
        
        解法2: 
        1.排序: 把任意k個變成考慮連續k個，並且只需要考慮前後兩個就好，夾在中間的肯定都是一樣的
        2. 排序後 整個子數組LCP =LCP(前後兩個的LCP) -> 把 k個字串轉成2個字串
        3. 如果不刪除，那麼答案是多少 就是每個子數組取最大值就是不刪除的答案
        4. 紀錄最大的LCP對應的子數組 [mx_i, mx_i+k-1]
           紀錄次大的LCP對應的子數組 [mx2_i, mx2_i+k-1]
        5. 考慮刪除一個字符串
            分類討論: 
            a.如果刪除的字符串不在[mx_i, mx_i+k-1]裡面，那麼就是不刪除的答案，及最大LCP
            b.如果刪除的字符串不在[mx2_i, mx2_i+k-1]中，答案就是次大LCP(並且刪除的會在最大而且最大剛好是k string個)
            c. 如果刪除的字符串在最大又在次大, 那麼答案是? 就是跑DFS某條string更新了兩次的狀況(次大LCP也是最大LCP前綴)，答案會是不包含最大的次大
            但這個也會是次大LCP, mx >= mx2 去掉任意一條 取交集還會是次大
        */
        int n = words.size();
        if(k >= n) return vector<int>(n);
        vector<int> idx(n);
        iota(idx.begin(),idx.end(), 0);
        ranges::sort(idx, {}, [&](int i) { return words[i]; });
        int mx = -1, mx2 = -1, mx_i = -1;
        auto cal_lcp = [&](string&s, string&t) -> int {
            int i = 0, j = 0;
            while (i < s.size() && j < t.size()) {
                if(s[i] != t[j]) return i;
                i += 1, j += 1;
            }
            return min((int)s.size(), (int)t.size());
        };
        for(int i = 0; i + k - 1 < n; i++) {
            int lcp = cal_lcp(words[idx[i]], words[idx[i+k-1]]);
            if (lcp > mx) {
                mx2 = mx;
                mx = lcp;
                mx_i = i;
            } else if (lcp > mx2) mx2 = lcp;
        }
        vector<int> ans(n, mx);
        for(int i = mx_i; i < mx_i + k; i++) {
            ans[idx[i]] = mx2;
        }
        return ans;
       
    }
};
