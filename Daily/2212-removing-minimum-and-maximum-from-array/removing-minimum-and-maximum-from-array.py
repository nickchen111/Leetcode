class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return 1
        mn, mx = inf, -inf
        mn_pos, mx_pos = -1, -1
        for i, x in enumerate(nums):
            if x > mx:
                mx = x
                mx_pos = i
            if x < mn:
                mn = x
                mn_pos = i
        # 判斷哪個比較快可以刪掉 直接一路從頭刪除 or 一路從尾刪除 or 兩邊刪除
        return min(max(mn_pos, mx_pos) + 1, n - min(mn_pos, mx_pos), min(mn_pos, mx_pos) + 1 + n - max(mn_pos, mx_pos))