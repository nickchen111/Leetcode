# 逆向思維: a.遞歸 TC:O(k * k* 史特林生成函數 大概是sqrt_k(sqrt(k * n))) SC:O(k * k* 史特林生成函數 大概是sqrt_k(sqrt(k * n))) b. 遞推 TC:O(k*n) SC:O(k)
@cache
def dfs(i:int, j:int) ->int:
    if i == 0 or j == 0: return 0
    return dfs(i - 1, j - 1) + dfs(i - 1, j) + 1
class Solution:
    def superEggDrop(self, k: int, n: int) -> int:
        '''
        n = 1e4, k = 100
        每一層都去試試看 並且如果破了就看我是否還有雞蛋可以亂試 這樣狀態會是 n * k * n 不行
        要將時間控在n * k的話該怎麼做
        先來思考從特殊到一般 之前case i = 15 j = 2 就要從15開始
        那如果j = 3 可以從17開始?! 不行 因為不知道i = 16狀態 假設失敗的話
        dfs(i, j) 有i次操作j個雞蛋可以達到的最高樓層數 這題就是逆向思維的一種，正著來不好求，從可能的答案反推更好求
        '''
        # 空間優化
        f = [0] * (k + 1)
        for i in count(1): 
            for j in range(k, 0, -1):
                f[j] += f[j - 1] + 1
            if f[k] >= n:
                return i
        '''
        遞推
        f = [[0] * (k + 1) for _ in range(n + 1)]
        for i in count(1):
            for j in range(1, k + 1):
                f[i][j] = f[i-1][j-1] + f[i-1][j] + 1
            if f[i][j] >= n:
                return i
        return f[n][k]
        '''

        '''
        遞歸 
        for i in count(1):
            if dfs(i, k) >= n:
                return i
        '''
