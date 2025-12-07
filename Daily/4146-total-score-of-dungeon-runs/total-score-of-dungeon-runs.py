class Solution:
    def totalScore(self, hp: int, damage: List[int], requirement: List[int]) -> int:
        '''
        先走一次從零開始 建造一個arr
        然後就可以開始判斷後續每一次這個位置會被多少之前的位置計算到
        '''

        nums = []
        n = len(damage)
        for i in range(n):
            hp -= damage[i]
            nums.append(hp)
        i = 0
        pre = [0]
        tot = ans = 0
        while i < n:
            if nums[i] < requirement[i]:
                #判斷之前的他要從哪出發才可以大於等於
                diff = requirement[i] - nums[i]
                j = bisect_left(pre, diff)
                if j != len(pre):
                    ans += i - j + 1
            else:
                ans += i + 1
            tot += damage[i]
            pre.append(tot)
            i += 1
        return ans




        