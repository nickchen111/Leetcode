# 區間技巧是這段
def update(i:int, op:int) -> None:
    idx = bisect_left(sl, i)
    pre = sl[idx - 1]
    nxt = sl[idx % len(sl)] # 因為有可能刪除到最後面的導致越界
    bit.update((nxt - pre + n - 1) % n + 1, -op) # 移除/添加舊長度 # python 可以寫成 (nxt - pre - 1) % n + 1 
    bit.update((i - pre + n) % n, op) 
    bit.update((nxt - i + n) % n, op) # 新增/刪除新長度
def remove(i:int) -> None: # 去除間隔 刪除一個結尾位置
    sl.remove(i)
    if not sl:
        bit.update(n, -1)
    else:
        update(i, -1)
def add(i:int) -> None: # 新增間隔 新增一個結尾位置為至
    if not sl:
        bit.update(n, 1)
    else:
        update(i, 1)
    sl.add(i)
# 操作區間增減過程
for i, c in enumerate(a):
    if a[i] == a[(i + 1) % n]:
        add(i) 
ans = []
for q in queries:
    if q[0] == 1:
        if not sl: # 所有點都可以形成一個size長度的答案
            ans.append(n)
        else:
            cnt, s = bit.pre(q[1])
            ans.append(s - cnt * (q[1] - 1))
    else:
        i, c = q[1], q[2]
        if a[i] == c:
            continue
        pre, nxt = (i-1) % n, (i + 1) % n
        if a[pre] == a[i]:
            remove(pre)
        if a[nxt] == a[i]:
            remove(i)
        a[i] = c
        if a[pre] == a[i]:
            add(pre)
        if a[nxt] == a[i]:
            add(i)
return ans


# LC. 3245
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [[0, 0] for _ in range (n + 1) ]
    def update(self, size: int, op: int, ) -> None:
        i = len(self.tree) - size
        while i < len(self.tree):
            self.tree[i][0] += op # 數量
            self.tree[i][1] += op * size # 長度
            i += i & -i
    def pre(self, size: int) -> int:
        cnt = s = 0
        i = len(self.tree) - size
        while i > 0:
            cnt += self.tree[i][0]
            s += self.tree[i][1]
            i &= i - 1
        return cnt, s
class Solution:
    def numberOfAlternatingGroups(self, a: List[int], queries: List[List[int]]) -> List[int]:
        '''
        就是在問說 每次查詢的時候有多少個交替數組 size = 指定長度 並且我可以去更改 交替數組的數字讓他發生變化
        假設原本有一段 4 5 3 長度的交替數組
        0101 | 10101 | 101 他就是 4 - (size - 1) + 5 - (size - 1) + 3 - (size - 1) 
        = (4 + 5 + 3) - 3 * (size - 1)
        長度和 - 有多少個分段? 這可以用樹狀數組維護
        查詢size >= 3 以後的總和結果 用兩個樹狀數組 一個維護總和 一個維護數量 即可 或者一個pair
        a. 非環形 沒有修改 大概2200-2300難度
        b. 非環形 有修改
        我要做的事情就是
        1. 分段處理每個字段並加入樹狀數組中 分組循環
        2. 在變化過程中動態修改 怎知修改點上的長度 以及他的左右端點在哪 -> 有序集合
        但是有序集合修改結束位置的操作有很多要討論的狀況
        11 | 0 1 0 | 0 1 0 1 0
        假設修改010 -> 0 1 1 這樣要討論的點變成左邊的結束位置是否要刪除修改 右邊又多出新的長度啥的
        修改 0 1 0 -> 0 0 0 變成 分出三段 
        情況太多
        不如
        刪除 i 和 i - 1 處的結束位置
        添加 i 和 i - 1 處的結束位置
        i + 1 結束位置是不會影響到的 他是和 i + 2 相比的
        用當前的結束位置和他在有序集合中的前驅和後繼去計算出[交替段]的長度
        再用兩個樹狀數組維護長度的[出現次數] 與 [元素和]

        nxt - pre - 1 -> pre = 6, nxt = 2 x o x x x o
        2 - 6 - 1 = -5 % 7 + 1
        '''
        # 首先sl 紀錄每個位置的結束位置 該位置長度 以及 數量
        n = len(a)
        sl = SortedList()
        bit = FenwickTree(n)
        def update(i:int, op:int) -> None:
            idx = bisect_left(sl, i)
            pre = sl[idx - 1]
            nxt = sl[idx % len(sl)] # 因為有可能刪除到最後面的導致越界
            bit.update((nxt - pre + n - 1) % n + 1, -op) # 移除/添加舊長度 # python 可以寫成 (nxt - pre - 1) % n + 1 
            bit.update((i - pre + n) % n, op) 
            bit.update((nxt - i + n) % n, op) # 新增/刪除新長度
        def remove(i:int) -> None: # 去除間隔 刪除一個結尾位置
            sl.remove(i)
            if not sl:
                bit.update(n, -1)
            else:
                update(i, -1)
        def add(i:int) -> None: # 新增間隔 新增一個結尾位置為至
            if not sl:
                bit.update(n, 1)
            else:
                update(i, 1)
            sl.add(i)
        for i, c in enumerate(a):
            if a[i] == a[(i + 1) % n]:
                add(i) 
        ans = []
        for q in queries:
            if q[0] == 1:
                if not sl: # 所有點都可以形成一個size長度的答案
                    ans.append(n)
                else:
                    cnt, s = bit.pre(q[1])
                    ans.append(s - cnt * (q[1] - 1))
            else:
                i, c = q[1], q[2]
                if a[i] == c:
                    continue
                pre, nxt = (i-1) % n, (i + 1) % n
                if a[pre] == a[i]:
                    remove(pre)
                if a[nxt] == a[i]:
                    remove(i)
                a[i] = c
                if a[pre] == a[i]:
                    add(pre)
                if a[nxt] == a[i]:
                    add(i)
        return ans
