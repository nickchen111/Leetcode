# TC:O(26 * 26 * n) SC:O(26 * 26)
class Solution:
    def minimumDistance(self, word: str) -> int:
        '''
        因為這題的字可以由任意兩指同時存在的狀況下拼湊出
        狀態可以定義成i,j,k 左指在某個位置上，右指在某個位置上，並且已經拼湊出K的長度
        首先根據貪心一定要有一指在起始點，一指在任意word上有的字元上的位置上
        所以會是26 * 26 * 300的時間複雜度
        '''
        arr = [ord(word[i]) - ord('A') for i in range(len(word))]
        n = len(arr)
        
        def cost(a: int, b: int) -> int:
            ax, ay = a // 6, a % 6
            bx, by = b // 6, b % 6
            return abs(ax - bx) + abs(ay - by)
        # 空間優化
        f = [[inf] * 26 for _ in range(26)]
        for j in range(26):
            f[arr[0]][j] = 0
        visited_set = set()
        visited_set.add(arr[0])
        for i in range(1, len(arr)):
            target = arr[i]
            new_f = [[inf] * 26 for _ in range(26)]
            for l in range(26):
                if l not in visited_set:
                    continue
                for r in range(26):
                    if f[l][r] == inf: continue
                    cost1, cost2 = cost(target, l),cost(target, r)
                    if f[l][r] + cost1 < new_f[target][r]:
                        new_f[target][r] = f[l][r] + cost1
                    if f[l][r] + cost2 < new_f[l][target]:
                        new_f[l][target] = f[l][r] + cost2
            visited_set.add(target)
            f = new_f
        return min(f[i][j] for i in range(26) for j in range(26))
        '''
        遞推
        f = [[[inf] * 26 for _ in range(26)] for _ in range(n)]
        for j in range(26):
            f[0][arr[0]][j] = 0
        for i in range(1, len(arr)):
            target = arr[i]
            for l in range(26):
                for r in range(26):
                    if f[i-1][l][r] + cost(target, l) < f[i][target][r]:
                        f[i][target][r] = f[i-1][l][r] + cost(target, l)
                    if f[i-1][l][r] + cost(target, r) < f[i][l][target]:
                        f[i][l][target] = f[i-1][l][r] + cost(target, r)
        return min(f[n-1][i][j] for i in range(26) for j in range(26))
        '''
        '''
        遞歸
        @cache
        def dfs(i:int, j:int, k:int) ->int:
            if k == len(arr):
                return 0
            nxt_pos_x,nxt_pos_y = arr[k] // 6, arr[k] % 6
            cur_pos_x_i, cur_pos_y_i = i // 6, i % 6
            cur_pos_x_j, cur_pos_y_j = j // 6, j % 6
            ans = min(dfs(arr[k], j, k + 1) + abs(nxt_pos_x - cur_pos_x_i) + abs(nxt_pos_y - cur_pos_y_i), dfs(i, arr[k], k + 1) + abs(nxt_pos_x - cur_pos_x_j) + abs(nxt_pos_y - cur_pos_y_j))
            return ans
        return min(dfs(arr[0], j, 0) for j in range(26))
        '''
