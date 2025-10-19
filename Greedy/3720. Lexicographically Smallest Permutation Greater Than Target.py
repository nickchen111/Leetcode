# TC:O(m * n) m 為字母數量 SC:O(m)
class Solution:
    def lexGreaterPermutation(self, s: str, target: str) -> str:
        n = len(s)
        cnt = Counter(s)
        letters = [chr(c) for c in range(ord('a'), ord('z')+1)]

        for i in range(n-1, -1, -1):
            temp = cnt.copy()
            ok = True
            for j in range(i):
                ch = target[j]
                if temp[ch] == 0:
                    ok = False
                    break
                temp[ch] -= 1
            if not ok:
                continue

            cur = target[i]
            for c_ord in range(ord(cur) + 1, ord('z') + 1):
                c = chr(c_ord)
                if temp[c] > 0:
                    temp[c] -= 1
                    tail_parts = []
                    for ch in letters:
                        if temp[ch] > 0:
                            tail_parts.append(ch * temp[ch])
                    tail = ''.join(tail_parts)
                    prefix = target[:i]
                    return prefix + c + tail
        return ""
