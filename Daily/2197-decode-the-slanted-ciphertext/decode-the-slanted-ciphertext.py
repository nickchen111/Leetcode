class Solution:
    def decodeCiphertext(self, encodedText: str, rows: int) -> str:
        if rows == 0:
            return ""
            
        cols = len(encodedText) // rows
        ans = []

        i = j = k = 0
        while k < cols:
            ans.append(encodedText[i * cols + j])
            i += 1
            j += 1

            # 觸及邊界
            if i == rows or j == cols:
                k += 1
                i, j = 0, k  # 移到下一條斜線

        return ''.join(ans).rstrip(' ')