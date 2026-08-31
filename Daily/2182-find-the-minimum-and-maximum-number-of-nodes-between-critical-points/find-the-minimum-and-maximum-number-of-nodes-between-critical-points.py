class Solution:
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        first = last = -1
        mn = inf
        last_pos = prev_pos = -1

        prev = head.val
        head = head.next
        pos = 1

        while head.next:
            if prev < head.val > head.next.val or prev > head.val < head.next.val:
                if first == -1:
                    first = last_pos = pos
                else:
                    prev_pos, last_pos = last_pos, pos
                    mn = min(mn, last_pos - prev_pos)

            prev = head.val 
            head = head.next
            pos += 1

        return [mn,last_pos - first] if last_pos != first else [-1, -1]