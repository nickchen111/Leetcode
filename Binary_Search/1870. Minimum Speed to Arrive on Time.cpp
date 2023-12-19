/*
1870. Minimum Speed to Arrive on Time
*/

// TC:O(n*23) SC:O(1)
class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int n = dist.size();
        if(hour <= n-1) return -1;
        
        int low = 1; int high = 1e7;
        while(low < high){
            int mid = low + (high - low)/2;
            if(count(dist,mid) <= hour){
                high = mid;
            }
            else low = mid + 1;
        }

        return low;
    }
    double count(vector<int>& dist,int mid){
        double needTime = 0;
        for(int i = 0; i < dist.size() - 1; i++){
            needTime += (dist[i]-1)/mid + 1;//這招要學起來 無條件進位大法 
        }

        needTime += (dist.back()*1.0)/mid;

        return needTime;
    }
};

/*
給你一串代表火車要走得公里數的數組
必須搭完所有火車才能到辦公室 但是限定 hour內要到 問說火車最低速度可以是多少 ...火車速度越高時間越短 單調性 Binary Search
還有個限制如果要搭下一個火車 就必須補滿你上次搭火車的時間到整數 ex 0->1 1->2 
*/
