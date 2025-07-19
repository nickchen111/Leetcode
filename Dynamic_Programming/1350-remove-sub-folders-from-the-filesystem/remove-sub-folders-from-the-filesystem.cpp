class Solution {
    struct TrieNode {
        bool isEnd;
        unordered_map<string, TrieNode*> next;
        TrieNode() : isEnd(false) {}
    };
    TrieNode* root = new TrieNode();
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        ranges::sort(folder);
        vector<string> ans;
        // 根據isEnd判斷是否屬於其他人底下
        for (auto &s : folder) {
            TrieNode* node = root;
            bool flag = true;
            int i = 0;
            while (i < s.size()) {
                while (i < s.size() && s[i] == '/') i += 1;
                string tmp = "";
                while (i < s.size() && s[i] != '/') {
                    auto ch = s[i];
                    tmp += ch;
                    i += 1;
                }
                if (!node->next.count(tmp)) {
                    node->next[tmp] = new TrieNode();
                }
                node = node->next[tmp];
                if (node -> isEnd) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                ans.emplace_back(s);
                node -> isEnd = true;
            }
        }
        return ans;
    }
};