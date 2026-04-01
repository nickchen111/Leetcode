class Solution:
    def survivedRobotsHealths(self, positions: List[int], healths: List[int], directions: str) -> List[int]:
        '''
        排序完做單調棧
        1. 按照位置排序
        2. 遇到向右的直接放入 st（存 [health, idx]）
        3. 遇到向左的，與 st 頂端碰撞：
            - 右 > 左：右方 health-1 放回，左方消滅
            - 右 < 左：左方 health-1，彈出右方，繼續碰撞
            - 右 == 左：兩者同歸於盡
            - st 空了仍存活：左方加入答案
        4. 只取 health > 0
        '''
        # 1. 按照位置排序
        idx = sorted(range(len(positions)), key=lambda i: positions[i])

        st  = []   # 存活且向右的機器人 [health, orig_idx]
        ans = []   # 向左且存活的機器人 [health, orig_idx]

        for i in idx:
            # 2. 向右：直接入棧
            if directions[i] == 'R':
                st.append(i)
                continue

            # 3. 向左：與棧頂碰撞
            while st:
                j = st[-1]
                if healths[j] > healths[i]:       # 右方勝，右方 -1 放回
                    healths[i] = 0
                    healths[j] -= 1
                    break
                elif healths[j] < healths[i]:     # 左方勝，左方 -1，繼續碰撞
                    healths[i] -= 1
                    healths[j] = 0
                    st.pop()
                else:                         # 同歸於盡
                    healths[i] = 0
                    healths[j] = 0
                    st.pop()
                    break
        # 4. 只取 health > 0
        return [h for h in healths if h > 0]