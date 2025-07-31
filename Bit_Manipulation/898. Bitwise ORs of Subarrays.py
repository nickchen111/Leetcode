# TC:O(nlogU) SC:O(n) -> O(1)
class Solution:
    def subarrayBitwiseORs(self, nums: List[int]) -> int:
        n = len(nums)
        st = set()
        ors = []
        for i in range(n - 1, -1, -1): # 固定右端點 去看左端點可以到哪
            ors.append([nums[i], i])
            ors[0][0] |= nums[i]
            k = 0
            for j in range(1, len(ors)):
                ors[j][0] |= nums[i]
                if ors[j][0] == ors[k][0]:
                    ors[k][1] = ors[j][1]
                else:
                    k += 1
                    ors[k] = ors[j]
            ors = ors[:k + 1]
            for num, idx in ors:
                st.add(num)
        return len(st)


class Solution:
    def subarrayBitwiseORs(self, nums: List[int]) -> int:
        n = len(nums)
        st = set()
        for i in range(n):
            st.add(nums[i])
            for j in range(i - 1, -1, -1):
                if nums[j] | nums[i] == nums[j]:
                    break
                nums[j] |= nums[i]
                st.add(nums[j])
        return len(st)
            
