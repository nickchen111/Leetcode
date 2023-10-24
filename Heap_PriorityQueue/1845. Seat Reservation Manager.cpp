/*
1845. Seat Reservation Manager
*/

class SeatManager {
    priority_queue<int, vector<int>, greater<int> > pq;
public:
    SeatManager(int n) {//初始化
        for(int i = n; i > 0; i--){
            pq.push(i);
        }
    }
    
    int reserve() {
        int ans = pq.top();
        pq.pop();

        return ans;
    }
    
    void unreserve(int seatNumber) { // tc: o(lgn)
        pq.push(seatNumber);
        return;
    }
};


 /*
 此題是使用數據結構 如果麻煩一點就要設計的問題型態
 題目提到每次都要拿出最小的那個座位 貌似可以想到用：
 1. priority_queue
 2. queue/ stack感覺可以但其實不行 他只能用來處離單調遞增減 如果unreserve一個較top大的數字會把top擠掉==

   tc: o(lgn) sc:o(n)
 */
