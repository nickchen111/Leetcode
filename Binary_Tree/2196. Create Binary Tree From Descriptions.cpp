/*
2196. Create Binary Tree From Descriptions
*/

// Hash Map + Set TC:O(n) SC:O(n)
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_set<int> set;
        unordered_map<int, TreeNode*> map;
        for(auto des : descriptions){
            int parent = des[0], child = des[1], left = des[2];
            TreeNode* np;
            TreeNode* nc;
            
            if(map.find(parent) != map.end()) np = map[parent];
            else {
                np = new TreeNode(parent);
                map[parent] = np;
            }

            if(map.find(child) != map.end()){
                nc = map[child];
                set.insert(child);
            } 
            else {
                nc = new TreeNode(child);
                set.insert(child);
                map[child] = nc;
            }

            if(left){
                np->left = nc;
            }
            else np->right = nc;   
        }

        for(auto p : map){
            if(set.find(p.first) == set.end()){
                return map[p.first];
            } 
        }

        return NULL;
    }
};

// BFS + Indegree + Hash Map TC:O(n) SC:O(n)
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, vector<pair<int,int>>> map; // child-> parent ? left ? 
        unordered_map<int,int> indegree;
        for(auto des : descriptions){
            int parent = des[0], child = des[1], left = des[2];
            map[parent].push_back({child, left});
            map[child].push_back({parent, -1});
            if(indegree.find(parent) == indegree.end()){
                indegree[parent] = 0;
            }
            indegree[child] += 1;
        }

        queue<pair<int, TreeNode*>> q;
        TreeNode* root;
        for(auto i : indegree){
            if(i.second == 0){
                root = new TreeNode(i.first);
                q.push({-1,root});
                break;
            }
        }
        
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int prev = q.front().first;
                TreeNode* cur = q.front().second;
                q.pop();
                int curVal = cur->val;
                for(auto [ch, check] : map[curVal]){
                    if(ch == prev) continue;
                    if(check == 1) {
                        cur->left = new TreeNode(ch);
                        q.push({curVal, cur->left});
                    }
                    else if(check == 0){
                        cur->right = new TreeNode(ch);
                        q.push({curVal,cur->right});
                    }
                }
            }
        }

        return root;
    }
};
