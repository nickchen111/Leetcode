class Solution:
    def handleQuery(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        '''
        lazy 線段樹入門
        問題： 一個數組，更新一個子數組的值(都加上一個數，把子數組內的值取反)
                      查詢一個子數組的值(求和，最大值...)

        兩大思想:
        1. 挑選O(n)特殊區間 使得任意一個區間可以被拆分成O(lgn)個特殊區間(用最近公共祖先思考)
            挑選O(n)特殊區間: build
        2. lazy 更新 / 延遲更新
        lazy tag : 用一個數組維護每個區間需要更新的值，如果這個值 = 0 表示不需要更新操作 
        值 != 0 表示更新操作在這個區間停住了 就不繼續遞歸後續的子區間
        如果後面又多了一個更新，破壞了lazy tag區間 那麼這個區間就得繼續遞歸更新下去
        '''
        n = len(nums1)
        cnt1 = [0] * (4 * n)
        todo = [False] * (4 * n)
        def maintain(o:int) -> None:
            cnt1[o] = cnt1[o * 2] + cnt1[o * 2 + 1]
        def build(o:int, l:int, r:int) -> None: # add:int
            if l == r:
                cnt1[o] = nums1[l]
                return
            m = (l + r) // 2
            build(o * 2, l, m)
            build(o * 2 + 1, m + 1, r)
            # maintain
            maintain(o)
        # 更新[L,R] 查詢一樣概念
        def do(o:int, l:int, r:int) -> None:
            cnt1[o] = r - l + 1 - cnt1[o]
            todo[o] = not todo[o] # 區間翻轉
        def update(o:int, l:int, r:int, L: int, R:int) -> None: # add:int 
            if L <= l and r <= R:
                do(o, l, r)
                # todo[o] += add 原本會寫成 todo = [0] * (4 * n) 但這題的更新只是
                return
            m = (l + r) // 2
            # 需要繼續遞歸，就把todo[o]的內容傳下去(給左右兒子)
            if todo[o]:
                do(o * 2, l, m)
                do(o * 2 + 1, m + 1, r)
                # todo[o * 2] += todo[o]
                # todo[o * 2 + 1] += todo[o]
                todo[o] = False # 0

            if L <= m:
                update(o * 2, l, m, L, R)
            if m < R:
                update(o * 2 + 1, m + 1, r, L, R)
            # maintain
            maintain(o)
        build(1,0,n-1)
        ans = []
          s = sum(nums2)
          for op, l, r in queries:
              if op == 1: update(1, 0, n-1, l, r)
              elif op == 2: s += l * cnt1[1]
              else: ans.append(s)
          return ans
