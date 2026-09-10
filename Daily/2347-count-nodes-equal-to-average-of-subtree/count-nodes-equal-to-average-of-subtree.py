# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def averageOfSubtree(self, root: TreeNode) -> int:
        if root == None:
            return 0
        subtree = {}
        def dfs(node:TreeNode) -> tuple[int,int]:
            if node == None:
                return 0, 0
            left_tot, left_cnt = dfs(node.left)
            right_tot, right_cnt = dfs(node.right)
            nonlocal subtree
            subtree[node] = left_tot + right_tot + node.val, left_cnt + right_cnt + 1
            return left_tot + right_tot + node.val, left_cnt + right_cnt + 1
        dfs(root)
        ans = 0
        def dfs_count(node:TreeNode) -> None:
            if node == None:
                return
            if node.val == subtree[node][0] // subtree[node][1]:
                nonlocal ans
                ans += 1
            dfs_count(node.left)
            dfs_count(node.right)
        dfs_count(root)
        return ans
        