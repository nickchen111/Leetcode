# TC:O(n) SC:O(n)
class Solution:
    def lexSmallestAfterDeletion(self, s: str) -> str:
        left = Counter(s)
        st = []
        for i, ch in enumerate(s):
            # 當目前這個元素比stack裡面的小 並且st最後一個有超過一個可以移除就使用它
            while st and ch < st[-1] and left[st[-1]] > 1:
                left[st.pop()] -= 1
            st.append(ch)
        # 再把後面的重複元素移除
        while left[st[-1]] > 1:
            left[st.pop()] -= 1
        return ''.join(st)
