class Solution:
    def findAllPeople(self, n: int, meetings: List[List[int]], firstPerson: int) -> List[int]:
        pa = list(range(n))
        def find(x:int) -> int:
            if x != pa[x]:
                pa[x] = find(pa[x])
            return pa[x]
        def merge(x:int, y:int) -> None:
            x, y = find(x), find(y)
            if x <= y:
                pa[y] = x
            else:
                pa[x] = y
        
        meetings.sort(key = lambda x : x[2])
        merge(0, firstPerson)
        i = 0
        n = len(meetings)
        st = {0, firstPerson}
        while i < n:
            person = set()
            j = i
            while j < n and meetings[i][2] == meetings[j][2]:
                a, b = meetings[j][0], meetings[j][1]
                if find(a) != find(b):
                    merge(a, b)
                person.add(a)
                person.add(b)
                j += 1
            for p in person:
                if find(p) == 0:
                    st.add(p)
                else:
                    pa[p] = p # rollback
            i = j
        return list(st)