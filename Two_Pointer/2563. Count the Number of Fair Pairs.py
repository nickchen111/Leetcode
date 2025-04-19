#TC:O(nlgn) SC:O(1)
class Solution:
    def countFairPairs(self, nums: List[int], lower: int, upper: int) -> int:
        '''
        lower <= nums[i] + nums[j] <= upper
        lower - nums[i] <= nums[j] <= upper - nums[i]
        可以用SortedList
        '''
        nums.sort()
        n = len(nums)
        ans = 0
        # Two Pointer
        def twoPointer(x:int) ->int:
            cnt = 0
            left, right = 0, n - 1
            while left < right:
                if nums[left] + nums[right] > x:
                    right -= 1
                else:
                    cnt += right - left
                    left += 1
            return cnt
            
        return twoPointer(upper) - twoPointer(lower - 1)

        '''
        二分
        for i in range(n):
            l = bisect_left(nums, lower - nums[i], i + 1, n)
            r = bisect_right(nums, upper - nums[i], i + 1, n)
            ans += r - l
        return ans
        '''

        '''
        SortedList
        st = SortedList()
        ans = 0
        for i in range(n):
            ans += st.bisect_right(upper - nums[i]) - st.bisect_left(lower - nums[i])
            st.add(nums[i])
        return ans
        '''
