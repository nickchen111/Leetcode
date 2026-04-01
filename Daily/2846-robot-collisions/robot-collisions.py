class Solution:
    def survivedRobotsHealths(self, positions: List[int], healths: List[int], directions: str) -> List[int]:
        '''
        排序完做單調棧
        1. 按照位置排序但要記得帶上healths, directions, original index
        2. 遇到向右的直接放入 st（存 [health, idx]）
        3. 遇到向左的，與 st 頂端碰撞：
            - 右 > 左：右方 health-1 放回，左方消滅
            - 右 < 左：左方 health-1，彈出右方，繼續碰撞
            - 右 == 左：兩者同歸於盡
            - st 空了仍存活：左方加入答案
        4. 碰撞結束後，st 內剩餘（向右存活）也加入答案
        5. 將答案按照 original index 排序，只取 health
        '''
        # 1. 按照位置排序，帶上 health, direction, original index
        robots = sorted(zip(positions, healths, directions, range(len(positions))), key=lambda x: x[0])

        st  = []   # 存活且向右的機器人 [health, orig_idx]
        ans = []   # 向左且存活的機器人 [health, orig_idx]

        for _, health, dire, idx in robots:
            # 2. 向右：直接入棧
            if dire == 'R':
                st.append([health, idx])
                continue

            # 3. 向左：與棧頂碰撞
            while st:
                top_health, top_idx = st[-1]
                if top_health > health:       # 右方勝，右方 -1 放回
                    st[-1][0] -= 1
                    break
                elif top_health < health:     # 左方勝，左方 -1，繼續碰撞
                    health -= 1
                    st.pop()
                else:                         # 同歸於盡
                    st.pop()
                    break
            else:
                # 3. st 空了仍存活：加入答案
                ans.append([health, idx])

        # 4. st 內剩餘向右存活者也加入答案
        ans.extend(st)

        # 5. 依 original index 排序，只回傳 health
        return [h for h, _ in sorted(ans, key=lambda x: x[1])]