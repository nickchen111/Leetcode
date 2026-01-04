class Solution:
    def wordSquares(self, words: List[str]) -> List[List[str]]:
        words.sort()
        ans = []
        st = set()
        def dfs(arr:List[str]) -> None: 
            nonlocal ans
            if len(arr) == 4:
                if arr[0][0] == arr[1][0] and arr[0][-1] == arr[2][0] and arr[3][0] == arr[1][-1] and arr[3][-1] == arr[2][-1]:
                    ans.append(arr[:])
                return
            for j in range(len(words)):
                if j in st:
                    continue
                st.add(j)
                arr.append(words[j])
                dfs(arr)
                arr.pop()
                st.remove(j)
            return
        dfs([])
        return ans
