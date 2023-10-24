/*
654. Maximum Binary Tree
*/

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//此題給你一串數組 說最大值的左邊數組為他的左子樹 右邊為右子樹 要求你重組他們的數組成binary tree的型態
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return build(nums, 0, nums.size()-1);
    }
    TreeNode* build(vector<int>& nums, int lo, int high){
        if(lo > high) return nullptr;
        int index = -1; //隨意初始化
        int maxval = INT_MIN;
        for(int i = lo; i <= high; i++){
            if(nums[i] > maxval){
                maxval = nums[i];
                index = i;
            }
        }
        TreeNode* root = new TreeNode(maxval);
        root->left = build(nums, lo, index-1);
        root->right =build(nums, index+1, high);

        return root;
    }
};
/*
解題思路
此題就是想要你構造出一個二叉樹
所以用分解問題的思路去解 跟+左子樹+右子樹
1.先找出最大值與他的index 
2.依照index 分成左邊右邊去遞歸 

时间复杂度：

构建最大二叉树的时间复杂度由递归函数 build 决定。
在每一层递归中，都需要线性遍历数组以找到最大值，所以每层递归的时间复杂度是 O(n)，其中 n 是当前递归层的数组长度。
因为每次递归都将数组分成两半，总共有 log n 层递归（这是递归树的高度），所以总的时间复杂度为 O(n log n)。
空间复杂度：

空间复杂度主要由递归函数的调用栈以及新建的二叉树节点所占用的空间决定。
递归调用栈的深度是 O(log n)，因为每次递归都将数组减半。
新建的二叉树节点数量与输入数组长度相同，所以空间复杂度是 O(n)。
递归调用栈的空间：
每次递归调用 build 函数时，系统会为函数的参数、局部变量、返回地址等在内存中分配一块称为栈帧（Stack Frame）的空间。随着递归的深入，每个递归函数调用都会在栈中创建一个新的栈帧。当递归函数返回时，对应的栈帧会被释放。因此，递归调用栈的空间复杂度取决于递归的深度，也就是最大递归层数。

在这段代码中，每次递归调用 build 函数时，数组范围都会缩小一半。如果数组的长度为 n，那么递归的深度将是 O(log n)（假设每次都能均匀地将数组划分为两半）。因此，递归调用栈的空间复杂度是 O(log n)。

新建的二叉树节点的空间：
每次在 build 函数中创建一个新的二叉树节点时，需要为节点的值、左孩子和右孩子等信息分配一块内存空间。在最坏情况下，每个输入数组元素都会对应一个新的二叉树节点，所以新建的二叉树节点的数量与输入数组的长度成正比。

综合上述两个方面，这段代码的空间复杂度主要由递归调用栈和新建的二叉树节点共同决定，分别是 O(log n) 和 O(n)。因此，总的空间复杂度为 O(log n + n)，在大 O 表示法中，通常忽略低阶项和常数系数，所以最终的空间复杂度是 O(n)。
*/
