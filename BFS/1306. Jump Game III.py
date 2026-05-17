# TC:O(n) SC:O(n)
class Solution:
    def canReach(self, arr: List[int], start: int) -> bool:
        q = deque()
        n = len(arr)
        vis = [False] * n
        q.append(start)
        vis[start] = True
        while q:
            cur = q.pop()
            if arr[cur] == 0:
                return True
            left, right = cur - arr[cur], cur + arr[cur]
            if left >= 0 and not vis[left]:
                vis[left] = True
                q.append(left)
            if right < n and not vis[right]:
                vis[right] = True
                q.append(right)
        return False
