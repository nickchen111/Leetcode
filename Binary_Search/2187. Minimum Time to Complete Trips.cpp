/*
2187. Minimum Time to Complete Trips
*/

// TC:O(nlg1e14) or 根據題億找當前最大值 TC:O(nlgmax)  SC:O(1) 
class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long low = 1;
        long long high = 0;
        for(long long t : time){
            high = max(high, t);
        }
        high *= totalTrips;

        while(low < high){
            long long mid = low + (high - low)/2;
            if(solve(time,mid,totalTrips) == false){
                low = mid + 1;
            }
            else high = mid;
        }

        return low;
    }

    bool solve(vector<int>& time, long long mid, int totalTrips){
        
        int n = time.size();
        //題目變成給你一段時間 從數組中取出小於等於他的時間段有多少公車運行次數總和
        long long count = 0;
        for(int i = 0; i < n; i++){
            count += mid/time[i];
        }

        return count >= totalTrips;
    }
};

// 1e14寫法
class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long low = 1;
        long long high = 1e14;// 因為時間最久繞一圈的選項是1e7 最大可能需要圈數也是1e7
        while(low < high){
            long long mid = low + (high - low)/2;
            if(solve(time,mid) < totalTrips){
                low = mid + 1;
            }
            else high = mid;
        }

        return low;
    }

    long long solve(vector<int>& time, long long mid){
        
        int n = time.size();
        //題目變成給你一段時間 從數組中取出小於等於他的時間段有多少公車運行次數總和
        long long count = 0;
        for(int i = 0; i < n; i++){
            count = (count + mid/time[i]);
        }

        return count;
    }
};

/*
此題給了一串每輛公車繞一整圈所需時間 問最少需要多少時間可以完成 totalTrips圈的概念
第一個想到用PQ 最小的先pop上來 然後自己加上自己放回去堆裡這樣不斷循環totalTrips次去取最小值 每個公車的運行不影響其他人 就會是 10^7*lg10^5 = 10^9 可能要有個lgn的解法-> Binary Search
旅程數越多我所需時間愈多 ->單調性
假設可以 t 時間內完成 此時間數內能在的數量如果大於等於total high = mid  反之 low = mid + 1

*/
