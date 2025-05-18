# TC:O(nlgn) SC:O(n)
class Solution:
    def minimumOperations(self, root: Optional[TreeNode]) -> int:
        ans, q = 0, [root]
        while q:
            a = []
            tmp = q
            q = []
            for node in tmp:
                a.append(node.val)
                if node.left: q.append(node.left)
                if node.right: q.append(node.right)

            n = len(a)
            a = sorted(range(n), key=lambda i: a[i])  # 離散化

            ans += n
            vis = [False] * n
            for v in a:
                if vis[v]: continue
                while not vis[v]:
                    vis[v] = True
                    v = a[v]
                ans -= 1
        return ans
