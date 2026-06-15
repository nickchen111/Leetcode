# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def deleteMiddle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head.next is None:  # 只有一个节点
            return None

        # 876. 链表的中间结点
        # 本题先让快指针走两步，这样慢指针少走一步，刚好落在中间节点的前一个节点
        slow = head
        fast = head.next.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

        slow.next = slow.next.next  # 删除 slow 的下一个节点
        return head
