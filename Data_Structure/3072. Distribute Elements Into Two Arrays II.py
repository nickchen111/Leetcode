# TC: O(nlgn) SC:O(n)
class Solution:
    def resultArray(self, nums: List[int]) -> List[int]:
        '''
        有一個Function會去計算某個數字丟進去某個資料結構中大於該數字的數字量有多少個
        第一次先丟arr1, 第二次丟arr2 之後就按照規則看哪個經過function後數字量多丟哪個
        如果相等就看哪個數字少丟哪個
        最後就是問arr1 + arr2 會是啥？
        兩種想法
        1. 用類似orderset的方式去做, python可以用SortedList 應該更快 底層感覺是bucket sort 但是效率很好
        2. 樹狀數組離散化
        '''
        arr1 = SortedList([nums[0]])
        arr2 = SortedList([nums[1]])
        ans1 = [nums[0]]
        ans2 = [nums[1]]

        for i in range(2, len(nums)):
            val = nums[i]
            l1,l2 = len(arr1), len(arr2)
            cnt1 = l1 - arr1.bisect_right(val)
            cnt2 = l2 - arr2.bisect_right(val)
            if cnt1 > cnt2 or cnt1 == cnt2 and l1 <= l2:
                arr1.add(val)
                ans1.append(val)
            else:
                arr2.add(val)
                ans2.append(val)
        return ans1 + ans2
