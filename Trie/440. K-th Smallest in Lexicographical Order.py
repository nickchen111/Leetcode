# 優化前: TC:O(D * lgn * lgn) SC:O(1) 優化後: TC:O(D * lgn) SC:O(1)
class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        x = n // 10
        subtree_size = 0
        pow10 = 1
        while x > 0:
            subtree_size = subtree_size * 10 + 1
            x //= 10
            pow10 *= 10
        def count_subtree_size(node:int) -> int:
            left, right = node * pow10, (node + 1) * pow10
            size = subtree_size
            if left <= n:
                size += min(n + 1, right) - left
            return size
        node = 1
        k -= 1
        while k > 0:
            size = count_subtree_size(node)
            if size <= k:
                k -= size
                node += 1
            else:
                subtree_size //= 10
                pow10 //= 10
                node *= 10
                k -= 1
        return node

# 優化前
class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        def count_subtree_size(node:int) -> int:
            left, right = node, node + 1
            size = 0
            while left <= n:
                size += min(n + 1, right) - left
                left *= 10
                right *= 10
            return size
        node = 1
        k -= 1
        while k > 0:
            size = count_subtree_size(node)
            if size <= k:
                k -= size
                node += 1
            else:
                node *= 10
                k -= 1
        return node
