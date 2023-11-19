/*
2935. Maximum Strong Pair XOR II
*/

// TC:O(nlgmaxNum) SC:O(nlgmaxNum) lgmaxNum 頂多32
class Solution {
    class TrieNode{
    public:
        vector<TrieNode*> next; 
        int count;
        TrieNode(): next(2,NULL), count(0){};
        ~TrieNode(){
            for(auto child:next){
                if(child) delete child;
            }
        }
    };
    TrieNode* root;
public:
    int maximumStrongPairXor(vector<int>& nums) {
        root = new TrieNode();
        sort(nums.begin(),nums.end());
        //從高位到低位建樹
        int j=0;
        int res = INT_MIN/2;
        for(int i = 0; i<nums.size(); i++){
            while( j < nums.size() && nums[j] <= 2*nums[i]){
                add(nums[j]);
                j++;
            }
            res = max(res,DFS(nums[i],root,31));
            remove(nums[i]);
        }

        return res;
    }
    void add(int num){
        TrieNode* node = root;
        for(int k = 31; k>=0; k--){
            int bit = ((num>>k)&1);
            if(node->next[bit] == NULL) node->next[bit] = new TrieNode();
            node = node->next[bit];
            node->count+=1;
        }
    }
    void remove(int num){
        TrieNode* node = root;
        for(int k = 31; k>=0; k--){
            int bit = ((num>>k)&1);
            node = node->next[bit];
            node->count-=1;
        }
    }
    int DFS(int num, TrieNode* node, int k){
        if(k == -1) return 0;
        int bit = (num>>k)&1;//XOR運算 要大就要找相反的數值
        if(bit == 0){
            if(node->next[1] && node->next[1]->count > 0){
                return DFS(num,node->next[1],k-1)+(1<<k);
            }
            else if(node->next[0] && node->next[0]->count > 0){
                return DFS(num,node->next[0],k-1);
            }
        }
        else if(bit == 1){
            if(node->next[0] && node->next[0]->count > 0){
                return DFS(num,node->next[0],k-1)+(1<<k);
            }
            else if(node->next[1] && node->next[1]->count > 0){
                return DFS(num,node->next[1],k-1);
            }
        }
        //都沒有代表沒有這個數 回傳一個最小值不會被選到
        return INT_MIN/2;
    }
};
/*
if x>=y
x-y <=y
-> x<=2y
[o o [o o o o] o o o o o o]
      y     x
*/
