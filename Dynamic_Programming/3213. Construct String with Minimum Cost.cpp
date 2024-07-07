/*
3213. Construct String with Minimum Cost
*/

// TC:O(n^2) SC:O(n*26) 但有剪枝
class TrieNode
{
    public:
    TrieNode* next[26];
    int cost;
    TrieNode()
    {
        for (int i=0; i<26; i++)
            next[i] = NULL;
        cost = -1;
    }        
};

class Solution {
    TrieNode* root = new TrieNode();
    vector<int>memo;
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) 
    {
        memo = vector<int>(target.size(), -1);
        
        for (int i=0; i<words.size(); i++)
        {
            TrieNode* node = root;
            for (auto ch: words[i])
            {
                if (node->next[ch-'a']==NULL)
                    node->next[ch-'a'] = new TrieNode();
                node = node->next[ch-'a'];
            }
            if (node->cost==-1)
                node->cost = costs[i];
            else
                node->cost = min(node->cost, costs[i]);
        }
        
        int ret = dfs(target, 0);        
        if (ret == INT_MAX/2) return -1;
        else return ret;
    }
    
    int dfs(string& target, int cur)
    {
        if (cur==target.size()) return 0;
        if (memo[cur] != -1) return memo[cur];
        
        int ans = INT_MAX/2;
        TrieNode* node = root;
        for (int i=cur; i<target.size(); i++)
        {
            if (node->next[target[i]-'a']==NULL)
                break;
            node = node->next[target[i]-'a'];
            if (node->cost!=-1)
                ans = min(ans, node->cost + dfs(target, i+1));
        }
        
        memo[cur] = ans;
        
        return ans;
    }
};

// TC:O(n^2) SC:O(n*26) dp剪枝
class Solution {
    struct TrieNode{
        int count;
        TrieNode* next[26];
        TrieNode(){
            for(int i = 0; i < 26; i++){
                next[i] = NULL;
            }
            count = INT_MAX/2;
        }
        ~TrieNode(){
            for(auto child : next){
                if(child) delete child;
            }
        }
    };
    TrieNode* root = new TrieNode();
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        vector<int> dp(target.size() + 1, INT_MAX / 2);
        dp[0] = 0;

        for(int i = 0; i < words.size(); i++) {
            TrieNode* node = root;
            auto word = words[i];
            for(auto ch : word) {
                if(node->next[ch - 'a'] == NULL) node->next[ch - 'a'] = new TrieNode();
                node = node->next[ch - 'a'];
            }
            node->count = min(node->count, costs[i]);
        }

        for(int i = 0; i < target.size(); i++) {
            if (dp[i] == INT_MAX / 2) continue; // No valid way to reach this point
            
            TrieNode* node = root;
            for(int j = i; j < target.size(); j++) {
                auto ch = target[j];
                if(node->next[ch - 'a'] != NULL) {
                    node = node->next[ch - 'a'];
                    if(node->count != INT_MAX / 2) {
                        dp[j + 1] = min(dp[j + 1], dp[i] + node->count);
                    }
                } else break;
            }
        }

        return dp[target.size()] == INT_MAX / 2 ? -1 : dp[target.size()];
    }
};
