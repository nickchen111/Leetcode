# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        q = deque()
        q.append(root)
        ans = -inf
        ret = step = 0
        while q:
            tot = 0
            step += 1
            nxt_q = deque()
            while q:
                cur = q.popleft()
                tot += cur.val
                if cur.left:
                    nxt_q.append(cur.left)
                if cur.right:
                    nxt_q.append(cur.right)
            q = nxt_q
            if tot > ans:
                ans = tot
                ret = step
        return ret
                    