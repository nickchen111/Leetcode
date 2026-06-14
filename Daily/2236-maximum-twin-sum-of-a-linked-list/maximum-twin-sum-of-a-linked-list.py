class Solution:
    def pairSum(self, head: Optional[ListNode]) -> int:
        ans = 0
        left = head

        def dfs(right: Optional[ListNode]) -> None:
            # 「递」，先把 right 移到链表末尾
            if right.next:
                dfs(right.next)
            # 「归」的过程就是在从右到左遍历链表
            nonlocal ans, left
            ans = max(ans, left.val + right.val)
            left = left.next  # left 往右走
            # 归，right 会往左走

        dfs(head)
        return ans