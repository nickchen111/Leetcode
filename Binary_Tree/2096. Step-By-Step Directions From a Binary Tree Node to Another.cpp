/*
2096. Step-By-Step Directions From a Binary Tree Node to Another
*/


//  LCA TC:O(n) SC:O(n)
class Solution {
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        // LCA寫法 
        vector<int> nums1, nums2;
        string dir1,dir2;
        DFS(root, nums1,dir1, startValue);
        DFS(root, nums2, dir2, destValue);
        //找分岔點
        int k = 0;
        while(k < nums1.size() && k < nums2.size() &&  nums1[k] == nums2[k]) k++;
        
        //將左邊的都改成U
        for(int i = k; i < dir1.size(); i++){
            dir1[i] = 'U';
        }

        return dir1.substr(k) + dir2.substr(k);
    }
    bool DFS(TreeNode* root, vector<int>& nums, string& dir, int target){
        if(root == NULL) return false;
        if(root->val == target) return true;
        
        if(root->left){
            nums.push_back(root->left->val);
            dir += 'L';
            if(DFS(root->left, nums, dir, target)) return true;
            nums.pop_back();
            dir.pop_back();
        }
        if(root->right){
            nums.push_back(root->right->val);
            dir += 'R';
            if(DFS(root->right, nums, dir, target)) return true;
            nums.pop_back();
            dir.pop_back();
        }

        return false;

    }
};

// Hash Map + DFS TC:O(2*n) SC:O(n)
class Solution {
    unordered_map<TreeNode*,TreeNode*> child2parent;
    string res;
    vector<bool> visited;
    TreeNode* start;
    TreeNode* dest;
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        if(root->val == startValue) start = root;
        if(root->val == destValue) dest = root;

        DFS(root->left, root, startValue, destValue);
        DFS(root->right, root, startValue, destValue);

        string str;
        visited.resize(child2parent.size()+2);
        visited[start->val] = 1;
        DFS2(start, dest, str);
        return res;
    }
    void DFS(TreeNode* node, TreeNode* parent, int startValue, int destValue){
        if(node == NULL) return;
        if(node->val == startValue) start = node;
        if(node->val == destValue) dest = node;
        
        child2parent[node] = parent;

        if(node->left){
            DFS(node->left, node, startValue, destValue);
        }
        if(node->right){
            DFS(node->right, node, startValue, destValue);
        }

        return;
    }
    void DFS2(TreeNode* cur, TreeNode* dest, string& str){
        if(cur == dest && res.size() == 0){
            res = str;
            return;
        }
        if(res.size() > 0) return;
        
        if(cur->left && !visited[cur->left->val]){
            visited[cur->left->val] = 1;
            str += "L";
            DFS2(cur->left, dest, str);
            str.pop_back();   
        }

        if(cur->right && !(visited[cur->right->val])){
            visited[cur->right->val] = 1;
            str += "R";
            DFS2(cur->right, dest, str);
            str.pop_back();    
        }

        if(child2parent.find(cur) != child2parent.end()){
            int parent = child2parent[cur]->val;
            if(!visited[parent]){
                visited[parent] = 1;
                str += "U";
                DFS2(child2parent[cur], dest, str);
                str.pop_back();
            }
        }
    }
};

/*
一如既往地要你求從某樹的節點到另外一個節點走最短距離的走法 但這次要你output此走法的方式
LRU, U代表走向parent
當下的感覺是很難用地歸的方式去構造出要的string 可能還是得直接跑一遍先確定好路徑
但這題仔細觀察他的最短路徑是符合LCA的狀況的 所以只需去找兩條路線 將左邊那條都改成U並且分割出不需要的路徑 加上分割出需要的右邊路徑就會是答案
*/
