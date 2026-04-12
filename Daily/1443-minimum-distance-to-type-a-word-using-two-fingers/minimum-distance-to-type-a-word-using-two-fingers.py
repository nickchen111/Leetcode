class Solution:
    def minimumDistance(self, word: str) -> int:
        arr = [ord(w) - ord('A') for w in word]
        @cache
        def dfs(i:int, j:int, k:int) -> int:
            if k == len(arr):
                return 0
            nxt_pos_x, nxt_pos_y = arr[k] // 6, arr[k] % 6
            pos_1_x, pos_1_y = i // 6, i % 6
            pos_2_x, pos_2_y = j // 6, j % 6
            ans = min(dfs(arr[k], j, k + 1) + abs(nxt_pos_x - pos_1_x) + abs(nxt_pos_y - pos_1_y), dfs(i, arr[k], k + 1) + abs(nxt_pos_x - pos_2_x) + abs(nxt_pos_y - pos_2_y))
            return ans
        return min(dfs(arr[0], j, 1) for j in range(26))
