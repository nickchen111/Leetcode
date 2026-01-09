# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def subtreeWithAllDeepest(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        '''
        求LCA
        '''
        ans = None
        maxDepth = 0
        def dfs(node: TreeNode, depth:int) -> int:
            nonlocal maxDepth, ans
            if not node:
                maxDepth = max(maxDepth, depth)
                return depth
            left, right = dfs(node.left, depth + 1), dfs(node.right, depth + 1)
            if left == right == maxDepth:
                ans = node
            return max(left, right)
        dfs(root, 0)
        return ans

            

