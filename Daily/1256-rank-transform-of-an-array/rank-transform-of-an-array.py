class Solution:
    def arrayRankTransform(self, arr: List[int]) -> List[int]:
        sorted_arr = sorted(set(arr))
        rank = {x: i for i, x in enumerate(sorted_arr, 1)}

        for i, x in enumerate(arr):
            arr[i] = rank[x]

        return arr