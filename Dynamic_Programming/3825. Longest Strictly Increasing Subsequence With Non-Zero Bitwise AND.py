# 空間優化寫法 TC:O(nlognlogU) SC:O(n)
class Solution:
    def longestSubsequence(self, nums: List[int]) -> int:
        L = max(nums).bit_length()
        ans = 0
        for bit in range(L):
            arr = []
            for x in nums:
                if (x >> bit) & 1:
                    idx = bisect_left(arr, x)
                    if idx < len(arr):
                        arr[idx] = x
                    else:
                        arr.append(x)
                ans = max(ans, len(arr))
        return ans

#
class Solution:
    def longestSubsequence(self, nums: List[int]) -> int:
        max_val = max(nums) if nums else 0
        if max_val == 0: return 0
        L = max_val.bit_length()
        
        arr = [[] for _ in range(L)]
        
        for x in nums:
            for bit in range(L):
                if (x >> bit) & 1:
                    idx = bisect_left(arr[bit], x)
                    
                    if idx < len(arr[bit]):
                        arr[bit][idx] = x
                    else:
                        arr[bit].append(x)
            
        return max(map(len, arr))
