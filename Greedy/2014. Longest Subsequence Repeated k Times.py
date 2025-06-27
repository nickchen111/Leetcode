# TC:O((n/k)! * n) SC:O(n * M) M = 26
class Solution:
    def longestSubsequenceRepeatedK(self, s: str, k: int) -> str:
        s = [ord(c) - ord('a') for c in s]
        n = len(s)
        nxt = [[n] * 26 for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            nxt[i][:] = nxt[i + 1]
            nxt[i][s[i]] = i

        def isSubsequence(seq: Tuple[int, ...]) -> bool:
            i = -1
            for _ in range(k):
                for c in seq:
                    i = nxt[i + 1][c]
                    if i == n: 
                        return False
            return True

        cnt = Counter(s)
        a = [ch for ch, freq in cnt.items() for _ in range(freq // k)]
        a.sort(reverse=True)

        for i in range(len(a), 0, -1):
            for seq in permutations(a, i): 
                if isSubsequence(seq): 
                    return ''.join(ascii_lowercase[c] for c in seq)
        return ''
