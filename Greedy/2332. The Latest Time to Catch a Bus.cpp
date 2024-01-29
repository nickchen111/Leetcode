/*
2332. The Latest Time to Catch a Bus
*/

// TC:O(nlgn + n) SC:O(1)
class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());
        
        int j = 0;
        int m = buses.size();
        int n = passengers.size();
        int res = -1;
        for(int i = 0; i < m; i++){
            int cap = capacity;
            //有可能坐滿了 那我就要找cap還夠的時候見縫插針
            while(j < n && buses[i] >= passengers[j] && cap > 0){
                if(j == 0 || (j >= 1 && passengers[j]-1 != passengers[j-1])){
                    res = max(res, passengers[j]-1);
                }
                j++;
                cap--;
            } 

            //沒坐滿 我可以卡最晚的時刻到達
            if(cap > 0){
                if(j == 0 || (j >= 1 && passengers[j-1] != buses[i])){
                    res = max(res, buses[i]);
                }
            }
        }

        return res;
    }

};

/*
給你每個公車出發時刻 每個人抵達時刻 這些數字都是獨特的
在給你一個capacity 代表公車限制人數上限
問你要搭上公車你最晚何時到 並且你的抵達時間不能跟其他人一樣
我的想法是 先從最早的公車check 看他是否載滿 會left 多少人等下一台
既然不知道的話就猜一個數字 去看這個時間抵達能不能上車
正著來的話寫法類似每一輛公車抵達時間對人群二分 看小於他的人有多少 超過cap的話加入left
在下一輪就會加上這些left 看超過多少更新left 一但沒有超過了 但是我還要去查找這些符合的人群有哪個較大的時間是能讓我見縫插針的
目前想不到除了遍歷這個數組以外的好方法 
所以不如猜個數字
還要注意猜的數字不能跟其他人相同 二分猜數字有個問題 猜到重複數字會不知道該往上加還是往下條
這題最理想的是模擬過程 模擬每輛公車的狀況by two pointer 並且在過程中假定你插了誰的隊上車了 或者公車有剩餘的cap 你壓死線上車的可能性
*/
