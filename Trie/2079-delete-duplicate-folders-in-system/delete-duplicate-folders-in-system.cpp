class Solution {
    struct TreeNode{
        string val;
        TreeNode(string s): val(s){}
        map<string, TreeNode*> next;
    };
    TreeNode* root;
    unordered_map<string, int> key2Count;
    unordered_map<string, int> key2Id;
    unordered_map<TreeNode*, string> node2Key;
    vector<vector<string>> res;
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        root = new TreeNode("/");
        for(auto path : paths){
            TreeNode* node = root;
            for(auto x : path){
                if(node->next.find(x) == node->next.end()) node->next[x] = new TreeNode(x);
                node = node->next[x];
            }
        }

        getId(root);

        vector<string> track;
        DFS(root, track);

        return res;
    }
    int getId(TreeNode* node){
        if(node == NULL) return 0;
        string key;

        for(auto x : node->next){
            TreeNode* child = x.second;
            key += to_string(getId(child)) + "#" + child->val + "#";
        }

        node2Key[node] = key;
        key2Count[key] += 1;
        if(key2Count[key] == 1){
            key2Id[key] = key2Id.size() + 1;
        }

        return key2Id[key];
    }

    void DFS(TreeNode* node, vector<string>& track){
        
        string key = node2Key[node];
        if(key != "" && key2Count[key] >= 2){
            return;
        }

        if(node->val != "/"){
            track.push_back(node->val);
            res.push_back(track);
        }

        for(auto x : node->next){
            DFS(x.second, track);
        }

        if(node->val != "/"){
            track.pop_back();
        }
    }
};