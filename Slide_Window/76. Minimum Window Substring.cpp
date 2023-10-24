/*
76. Minimum Window Substring
*/


// slide window TC:O(n) SC:O(k)
class Solution {
public:
    string minWindow(string s, string t) {
        int left = 0, right = 0;//紀錄當前位置
        int start = 0, len = INT_MAX;//紀錄字符串長度
        int valid = 0; //紀錄滑動期間收集了多少需要的字元
        unordered_map<char, int> need, window;
        for(char x:t){
            need[x]++;//需要哪些字元
        }

        //開始套模板
        //擴大窗口
        while(right < s.size()){//滑動窗口到結尾才會結束
            char c = s[right];
            right++;//這裡 先給出當下right是啥 在right++
            if(need.count(c)){
                window[c]++;
                if(window[c] == need[c]){
                    valid++;
                }
            }
            //shrink窗口
            while(valid == need.size()){
                // right 相對是最後滿足條件的index在往後一格
                if(right-left < len){
                    start = left;
                    len = right-left;
                }

                char d = s[left]; //準備被拋棄的字元
                left++;
                if(need.count(d)){
                    if(window[d] == need[d]){
                        valid--;
                    }
                    window[d]--;
                }
            }
        }
        
        return len == INT_MAX ? "": s.substr(start, len);

    }
};
/*
解題思路
因為是求子串的問題 所以有可能可以用滑動窗口的方式去解
思考：

1、什么时候应该移动 right 扩大窗口？窗口加入字符时，应该更新哪些数据？
當字符串沒有符合藥的時候 所以要有一個地方紀錄要什麼字符串
也要有個地方紀錄有了什麼字符串 加入時要去判斷是否符合縮小的資格了

2、什么时候窗口应该暂停扩大，开始移动 left 缩小窗口？从窗口移出字符时，应该更新哪些数据？
當滿足所需字符串時 縮小時如果把需要的字符串給縮了 就要剪剪然後再去擴大窗口

3、我们要的结果应该在扩大窗口时还是缩小窗口时进行更新？
應該再縮小時滿足情況時更新


时间复杂度：整体是线性时间复杂度，即 O(N)，其中 N 是字符串 s 的长度。因为 left 和 right 指针都最多各移动 N 次。

空间复杂度：需要额外使用哈希表来存储字符出现次数，所以空间复杂度是 O(K)，其中 K 是字符串 t 中不同字符的个数。
*/
