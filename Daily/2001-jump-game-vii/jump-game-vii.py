class Solution:
    def canReach(self, s: str, minJump: int, maxJump: int) -> bool:
        n = len(s)
        if s[-1] == '1':
            return False
        diff = [0] * (n + 1)
        if minJump <= n:
            diff[minJump] += 1
        if maxJump + 1 <= n:
            diff[maxJump + 1] -= 1
        cur = 0
        for i in range(minJump, n):
            cur += diff[i]
            if cur > 0 and s[i] == '0':
                if i + minJump <= n:
                    diff[i + minJump] += 1
                if i + maxJump + 1 <= n:
                    diff[i + maxJump + 1] -= 1
        return True if cur > 0 else False