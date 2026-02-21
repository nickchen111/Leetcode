# TC:O(nlogU) SC:O(nlogU)
WIDTH = 15
class Node:
    __slots__ = 'son', 'leaf'
    def __init__(self):
        self.son = [None] * 2
        self.leaf = 0
class Trie:
    def __init__(self):
        self.root = Node()

    def put(self, val:int) -> None:
        cur = self.root
        for i in range(WIDTH - 1, -1, -1):
            bit = val >> i & 1
            if cur.son[bit] is None:
                cur.son[bit] = Node()
            cur = cur.son[bit]
            cur.leaf += 1
    
    def delete(self, val:int) -> None:
        cur = self.root
        for i in range(WIDTH - 1, -1, -1):
            cur = cur.son[val >> i & 1]
            cur.leaf -= 1
        
    def max_xor(self, val:int) -> int:
        cur = self.root
        ans = 0
        for i in range(WIDTH - 1, -1, -1):
            bit = val >> i & 1
            if cur.son[bit ^ 1] and cur.son[bit ^ 1].leaf:
                ans |= (1 << i)
                bit  ^= 1
            cur = cur.son[bit]
        return ans

class Solution:
    def maxXor(self, nums: list[int], k: int) -> int:
        '''
        diff差可以用deque完成 O(n)
        但要如何判斷subarray要選哪一段才會有最大XOR?
        01trie 判斷目前有的數字組合中有哪個可以讓當前的組成最大
        '''

        n = len(nums)
        min_q = deque()
        max_q = deque()
        pre = list(accumulate(nums, xor, initial = 0))
        left = ans = 0
        t = Trie()
        for right, x in enumerate(nums):
            t.put(pre[right])
            while min_q and nums[min_q[-1]] >= x:
                min_q.pop()
            min_q.append(right)
            while max_q and nums[max_q[-1]] <= x:
                max_q.pop()
            max_q.append(right)

            while nums[max_q[0]] - nums[min_q[0]] > k:
                # left 扣掉
                t.delete(pre[left])
                left += 1
                if min_q[0] < left:
                    min_q.popleft()
                if max_q[0] < left:
                    max_q.popleft()
            ans = max(ans, t.max_xor(pre[right + 1]))
        return ans

