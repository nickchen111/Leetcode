/*
732. My Calendar III
*/


//sweeping line "TC:O(n^2) SC:O(n)
// 因為傳入一次整包的事件就要n 
// 傳n次呼叫n次函式就是n方"
class MyCalendarThree {
    map<int, int> Map;
public:
    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        Map[startTime] += 1;
        Map[endTime] -= 1;

        int res = 0;
        int sum = 0;
        for(auto& [t, diff]: Map){
            sum+=diff;
            res = max(res, sum);
        }

        return res;
    }
};


 /*
 掃描線的基礎題型
 用hash table去做最方便(map 紅黑樹) 自動幫你排序好起點結束點
 起點就加一代表這個時間點開始有新的事件 結束點就減一代表事件結束
 */
