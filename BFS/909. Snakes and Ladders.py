# TC:O(n * n) SC:O(n * n)
class Solution:
    def snakesAndLadders(self, board: List[List[int]]) -> int:
        '''
        BFS 最少需要幾步走到 n ^ 2 位置
        可以先將數字與位置映射
        '''
        pos = dict()
        n = len(board)
        cnt = 1
        for i in range(n - 1, -1, -1):
            if (n - 1 - i) % 2 == 0: # 代表從左到右
                for j in range(n):
                    pos[cnt] = (i, j)
                    cnt += 1
            else:
                for j in range(n-1, -1, -1):
                    pos[cnt] = (i, j)
                    cnt += 1
        q = deque()
        q.append(1)
        step = 0
        while q:
            for _ in range(len(q)):
                cur = q.popleft()
                if cur == n * n:
                    return step
                for i in range(cur + 1, min(cur + 6, n * n) + 1):
                    r, c = pos[i]
                    dest = board[r][c] if board[r][c] != -1 else i
                    if board[r][c] != -2:
                        board[r][c] = -2
                        q.append(dest)
            step += 1
        return -1
