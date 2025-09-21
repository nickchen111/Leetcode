# TC:O(n ^ 4 * n!) SC:O(n!)
class Solution:
    def minSplitMerge(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums1)
        target = tuple(nums2)
        start = tuple(nums1)
        if start == target:
            return 0
        
        queue = deque([(start, 0)])
        visited = {start}
        
        while queue:
            current, ops = queue.popleft()
            
            for L in range(n):
                for R in range(L, n):
                    subarray = current[L:R+1]
                    remaining = current[:L] + current[R+1:]
                    
                    for insert_pos in range(len(remaining) + 1):
                        new_array = remaining[:insert_pos] + subarray + remaining[insert_pos:]
                        
                        if new_array == target:
                            return ops + 1
                        
                        if new_array not in visited:
                            visited.add(new_array)
                            queue.append((new_array, ops + 1))
        return -1
