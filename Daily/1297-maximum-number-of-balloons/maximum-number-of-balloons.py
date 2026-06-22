class Solution:
    def maxNumberOfBalloons(self, text: str) -> int:
        mp = defaultdict(int)
        target = 'balon'
        for t in text:
            if t in target:
                mp[t] += 1
        ans = inf
        for t in target:
            if t in 'lo':
                ans = min(ans, mp[t] // 2)
            else:
                ans = min(ans, mp[t])
        return ans