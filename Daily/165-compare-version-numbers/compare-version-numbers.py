class Solution:
    def compareVersion(self, version1: str, version2: str) -> int:
        def str_to_int (s:str) -> List[int]:
            arr = []
            n = len(s)
            i = 0
            while i < n:
                j = i
                tmp = ""
                while j < n and s[j] != '.':
                    tmp += s[j]
                    j += 1
                arr.append(int(tmp))
                i = j + 1
            return arr
        arr1 = str_to_int(version1)
        arr2 = str_to_int(version2)
        i = j = 0
        while i < len(arr1) and j < len(arr2):
            if arr1[i] > arr2[j]:
                return 1
            elif arr1[i] < arr2[j]:
                return -1
            i += 1
            j += 1
        while i < len(arr1):
            if arr1[i] > 0:
                return 1
            i += 1
        while j < len(arr2):
            if arr2[j] > 0:
                return -1
            j += 1
        return 0