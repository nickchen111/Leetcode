/*
1233. Remove Sub-Folders from the Filesystem
*/

// TC:O(10^2*n + nlgn) SC:O(k*m*n) m 為平均切了幾段 k 為每段的平均長度 受限於100
class Solution {
    struct TrieNode {
        unordered_map<string, TrieNode*> children;
        bool isEnd;
        TrieNode() : isEnd(false) {}
    };
    TrieNode* root = new TrieNode();
public:
    vector<string> removeSubfolders(vector<string>& folder) {
       
        sort(folder.begin(), folder.end(), [](const std::string &a, const std::string &b) {
            return a.size() < b.size();
        });

        vector<string> res;

        for (const auto &str : folder) {
            bool isSubfolder = false;
            TrieNode* node = root;
            int m = str.size();
            int j = 1;
            while(j < m) {
                int start = j;
                string tmp;
                while(j < m && str[j] != '/') {
                    tmp += str[j++];
                }
                if(node->children.find(tmp) == node->children.end()) {
                    node->children[tmp] = new TrieNode();
                }
                node = node->children[tmp];
                if(node->isEnd) {
                    isSubfolder = true;
                    break;
                }
                j += 1;
            }

            node -> isEnd = true;
            if (!isSubfolder) {
                res.push_back(str);
            }
        }

        return res;
    }
};

// TC:O(10^4*n + nlgn) SC:O(100*n) 
class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
       

        sort(folder.begin(), folder.end(), [](const std::string &a, const std::string &b) {
            return a.size() < b.size();
        });

        unordered_set<string> set;
        for (const auto &dir : folder) {
            string parentDir;
            bool isSubfolder = false;
            for (int i = 1; i < dir.size(); i++) {
                if (dir[i] == '/') {
                    parentDir = dir.substr(0, i);
                    if (set.count(parentDir)) {
                        isSubfolder = true;
                        break;
                    }
                }
            }
            if (!isSubfolder) {
                set.insert(dir);
            }
        }

        return vector<string>(set.begin(), set.end());
    }
};
