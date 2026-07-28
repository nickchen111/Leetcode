class Solution:
    def smallestPalindrome(self, s: str) -> str:
        
        n = len(s)
        cnt = [0] * 26
        for ch in s:
            cnt[ord(ch) - ord('a')] += 1

        s1 = ""
        for i in range(26):
            if cnt[i]:
                s1 += chr(i + ord('a')) * (cnt[i] // 2)
                cnt[i] -= cnt[i] - (cnt[i] % 2)

        s2 = ""
        if n % 2 == 1:
            for i in range(26):
                if cnt[i]:
                    s2= chr(i + ord('a'))
                    cnt[i] -= 1
                    break
        s3 = s1[::-1]

        return s1 + s2 + s3