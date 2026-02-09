# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def balanceBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        # 先取得所有的value
        arr = []
        def dfs(node:TreeNode) -> None:
            if node == None:
                return
            dfs(node.left)
            arr.append(node.val)
            dfs(node.right)
        dfs(root)
        def construct(l:int, r:int) -> TreeNode:
            if l == r:
                return TreeNode(arr[l])
            if l > r:
                return None
            mid = (l + r) // 2
            root = TreeNode(arr[mid])
            leftNode = construct(l, mid - 1)
            rightNode = construct(mid + 1, r)
            root.left = leftNode
            root.right = rightNode
            return root
        return construct(0, len(arr) - 1)

