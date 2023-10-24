/*
100. Same Tree
*/

//recursion TC:O(n) SC:O(lgn)
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        //recursion
        if(!p && !q) return true;
        if(!p || !q) return false;
        if(p->val != q->val) return false;
        return isSameTree(p->left,q->left) && isSameTree(p->right, q->right);
    }
};

//BFS TC:O(n) SC:O(w) 底層數量
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<TreeNode*> q1;
        queue<TreeNode*> q2;
        q1.push(p);
        q2.push(q);
        while(!q1.empty() && !q2.empty()){
            TreeNode* tmp1 = q1.front();
            TreeNode* tmp2 = q2.front();
            q1.pop(); q2.pop();
            if(tmp1 == NULL || tmp2 == NULL){
                if(tmp1 != tmp2) return false;
                //兩個都是空 這回合不做防止 error
                continue;
            }
            if(tmp1->val != tmp2->val) return false;
            q1.push(tmp1->left);
            q2.push(tmp2->left);
            q1.push(tmp1->right);
            q2.push(tmp2->right);
        }

        return true;
    }
};

/*
挺有趣的題目 邏輯要清晰 要先思考說遞歸過程先比較兩者是否為空 如果不是那其中一方為空就返回false 在比較是否數值相同 
BFS的話就是要在外層確立兩個q都得非空 在比較取出的元素是否會有兩個NULL or 一個NULL情況
*/
