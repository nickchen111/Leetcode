class Solution:
    def compareVersion(self, version1: str, version2: str) -> int:
        version1=version1.split('.')
        version2=version2.split('.')
        m=len(version1)
        n=len(version2)
        while m<n:
            version1.append('0')
            m+=1
        while n<m:
            version2.append('0')
            n+=1
        for i,j in zip(version1,version2):
            if (int(i))<(int(j)):
                return -1
            elif (int(i))>(int(j)):
                return 1
        return 0