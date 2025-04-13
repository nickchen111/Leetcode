class Solution:
    def uniqueXorTriplets(self, nums):
        nums = list(set(nums))
        st = {x ^ y for x, y in combinations(nums, 2)} | {0} # st = {x ^ y for x in nums for y in nums}
        return len({xy ^ z for xy in st for z in nums})
