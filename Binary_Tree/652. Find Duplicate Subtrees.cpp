/*
652. Find Duplicate Subtrees
*/

// TC:O(n) SC:O(n) 11/11
class Solution {
    vector<TreeNode*> res;
    unordered_map<string,int> key2Id;
    unordered_map<string,int> key2Count;
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        getId(root);
        
        return res;
    }
    int getId(TreeNode* root){
        if(root == NULL) return -1;
        string key = to_string(root->val)+"#"+ to_string(getId(root->left)) + "#" + to_string(getId(root->right));
        if(key2Id.find(key) == key2Id.end()){
            key2Id[key] = key2Id.size();
            key2Count[key] = 1;
        }
        else{
            key2Count[key]+=1;
            if(key2Count[key] == 2) res.push_back(root);
        }

        return key2Id[key];
    }
};

/*
這題首先想到要如何快速判別是否存在相同子樹->遍歷 但是如果每個都重投遍歷就會是n方的時間
需要利用樹的遍歷性質來做 就不用每個點都重複遍歷 
第二個問題是如果遍歷出來的長度太長 不想拖著這麼長的序列化結果走 ->將他再轉乘獨特的數字
*/


// 
class Solution {
public:
    unordered_map<string, int> key2id;
    unordered_map<string, int> key2count;
    vector<TreeNode*> ans; 
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        getID(root);
        return ans;
    }

    int getID(TreeNode* node){
        //base case
        if(node == nullptr) return 0;//可能會跟key2id.size()重複到所以key2id.size()要加一
        string key = to_string(node->val) + "#" + to_string(getID(node->left)) + "#" + to_string(getID(node->right));

        //後序位置
        if(key2id.find(key) == key2id.end()){//代表還沒被生成過這種子樹
            key2id[key] = key2id.size()+1;
            key2count[key] = 1;
        }
        else{
            key2count[key]++;//加過他了就直接加一
            if(key2count[key] == 2){//那就是重複的子樹 加進去答案
                ans.push_back(node);
            }
        }
        return key2id[key];
    }

      
};
/*
解題思路：
這題想求的是遍歷完的結果去判斷是否有重複的子樹 牽扯到子樹的話那麼應該就是在後序位置上要做文章了
由於此題給定的nodee實在太多了所以用分解問題的方式以及用序列化去將每個子樹轉成特定的數字最後再將root left right的數字轉成獨特的字串
此題需要用到hash table 來存放 string轉成int結果 以及各種特別的子樹string 出現過的頻率

這個算法的時間複雜度取決於樹中的節點數量，由於每個節點只被訪問一次，所以時間複雜度是 O(n)，
其中 n 是樹中的節點數量。空間複雜度取決於使用的 unordered_map 的大小，最壞情況下可能達到 O(n)，
但通常情況下， key2id 和 key2count 中的條目數量會遠小於節點數量，所以空間複雜度可能是較小的常數倍數。

需要注意的是，上述代碼在處理節點的 val 時，使用了 to_string 函數將整數轉換為字串。這在確保 key 是唯一的情況下是可行的，
但如果節點值較大，可能會導致字串過長，增加了哈希碰撞的風險。可以根據實際情況考慮其他方式來生成唯一的 key。
*/
