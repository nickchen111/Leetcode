# TC:O(n * 4 ^ m) SC:O(4^m + n * 2 ^ m)
class Solution:
    def colorTheGrid(self, m: int, n: int) -> int:
        '''
        塗色 三種可選 問說有多少種塗色方法 兩邊不可以是相同顏色 題目沒有描述得很好 上下左右都不能是一樣顏色才對
        m = 5, n = 1000
        所以 m 的可能性可以被三進制枚舉 & 一下就知道是否有重疊
        如此一來就可以每個顏色去嘗試 這一排會有 3 ^ m 種可能 下一排會有 3 ^ m 
        總共狀態 3 * 2 ^ (m - 1) 每個狀態需要試試看2 ^ m -> 3 * 4 ^ m
        然後有n次 n * 3 * 4 ^ m
        更好的判斷是否數字相同的做法:
        回想一下以前十進制怎麼判斷的 會去 % 10 ^ x 判斷餘數是否相同 3進制同樣道理
        '''
        MOD = 10**9 + 7
        pow3 = [3 ** i for i in range(m)]
        valid = []
        for color in range(3 ** m):
            for i in range(1, m): # 每個狀態一樣是需要判斷ｍ次
                if color // pow3[i] % 3 == color // pow3[i - 1] % 3:  # 相鄰顏色相同
                    break
            else:  # 没有中途 break，合法
                valid.append(color)
        # 兩狀態之間有效轉移 更加優化時間
        nv = len(valid)
        nxt = [[] for _ in range(nv)]
        for i, color1 in enumerate(valid):
            for j, color2 in enumerate(valid):
                for p3 in pow3:
                    if color1 // p3 % 3 == color2 // p3 % 3:
                        break
                else:
                    nxt[i].append(j)
        # 空間優化
        f = [1] * nv
        for i in range(1, n):
            new_f = [0] * nv
            for j in range(nv):
                new_f[j] = sum(f[k] for k in nxt[j]) % MOD
            f = new_f
        return sum(f) % MOD
        '''
        f = [[0] * nv for _ in range(n)]
        f[0] = [1] * nv
        for i in range(1, n):
            for j in range(nv):
                f[i][j] = sum(f[i - 1][k] for k in nxt[j]) % MOD
        return sum(f[-1]) % MOD
        '''
