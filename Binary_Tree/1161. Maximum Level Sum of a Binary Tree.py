# TC:O(n) SC:O(n)
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        q = deque([root])
        ans = -inf
        ret = 0
        level = 0

        while q:
            level += 1
            tot = 0
            for _ in range(len(q)):
                cur = q.popleft()
                tot += cur.val
                if cur.left:
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)
            if tot > ans:
                ans = tot
                ret = level
        return ret
