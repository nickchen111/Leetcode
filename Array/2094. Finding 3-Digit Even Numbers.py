# TC:O(n) SC:O(m) m 為陣列長度, n為枚舉的數字數量 約500 
class Solution:
    def findEvenNumbers(self, digits: List[int]) -> List[int]:
        '''
        選三個數字組成偶數不能包含leading zero
        偶數條件 後面接 0 2 4 6 8 
        前面可以是任意
        '''
        mp = Counter(digits)
        ans = []
        for num in range(100, 999, 2):
            tmp = num
            curCount = defaultdict(int)
            while tmp:
                curCount[tmp % 10] += 1
                tmp //= 10
            flag = True
            for x in curCount:
                if curCount[x] > mp[x]:
                    flag = False
                    break
            if flag:
                ans.append(num)
        return ans


            
