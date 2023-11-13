/*
1948. Delete Duplicate Folders in System
*/

class Solution {
    struct TreeNode{
        string val;
        map<string, TreeNode*> next;
        TreeNode(string s): val(s){}
    };
    unordered_map<TreeNode*, string> node2key;
    unordered_map<string,int> key2Count;
    unordered_map<string,int> key2Id;
    TreeNode* root;
    vector<vector<string>> res;
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        //此題跟652用到的技巧一樣需要序列化並且因為序列化太長在轉成數字
        //先將paths轉成tree
        root = new TreeNode("/");
        for(auto path:paths){
            TreeNode* node = root;
            for(auto s:path){
                if(node->next.find(s) == node->next.end()) node->next[s] = new TreeNode(s);
                node = node->next[s];
            }
        }
        
        //將每個Tree的各種子樹編號
        getId(root);

        //在遍歷一次計算哪些是重複到2次
        vector<string> track;
        DFS(root,track);

        return res;
    }

    int getId(TreeNode* node){
        //if (node==NULL)
         //   return 0;可不加
        
        string key;
        for (auto x: node->next)
        {
            TreeNode* child = x.second;
            key += to_string(getId(child)) + "#" + child->val + "#";
        }
        
        node2key[node] = key;
        key2Count[key] += 1;
        if (key2Count[key]==1)
        {
            key2Id[key] = key2Id.size()+1;
        }
        
        return key2Id[key];
    }
    void DFS(TreeNode* node, vector<string>& track){
        
        string key = node2key[node];

        //因為最後一個節點都是注意沒東西這樣會被都當成是一樣的
        if(key != "" && key2Count[key] >=2) return;
        
        if(node->val != "/"){
            track.push_back(node->val);
            res.push_back(track);
        }
        for(auto x:node->next){
            DFS(x.second,track);
        }

        if(node->val != "/"){
            track.pop_back();
        }
    }
};
