class Solution:
    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        n = len(nums)
        # 需要一個資料結構紀錄以某個點為右端點 他能夠達到最大值的左端點是？
        ors = []
        ans = [0] * n
        for i in range(n - 1, -1, -1):
            ors.append([nums[i], i])
            idx = 0
            ors[0][0] |= nums[i]
            for j in range(1, len(ors)):
                ors[j][0] |= nums[i]
                if ors[j][0] == ors[idx][0]:
                    ors[idx][1] = ors[j][1]
                else:
                    idx += 1
                    ors[idx] = ors[j]
            ors = ors[: idx + 1]
            ans[i] = ors[0][1] - i + 1
        return ans
