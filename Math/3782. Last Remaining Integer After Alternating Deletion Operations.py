# TC:O(logn) SC:O(1)
class Solution:
    def lastInteger(self, n: int) -> int:
        # python 內建 range是個對象不是list
        r = range(1, n + 1) # 不是真的生成數列
        while len(r) > 1:
            r = r[::2][::-1]
        return r[0]
    
        '''
        等差數列
        start = d = 1
        while n > 1:
            start += (n - 2 + n % 2) * d # 計算下一輪首項的公式 可以計算下一個的末項 st + (n - 1) * d(公差) or st + (n - 2) * d (如果是偶數長)
            d *= -2
            n = (n + 1) // 2
        return start
        '''
