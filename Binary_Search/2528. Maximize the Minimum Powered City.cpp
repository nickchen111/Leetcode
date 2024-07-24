/*
2528. Maximize the Minimum Powered City
*/


// TC:O(nlgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maxPower(vector<int>& stations, int r, int k) {
       
        LL left = 0, right = LLONG_MAX/2;
        while(left < right){
            LL mid = left + (right - left + 1)/2;
            if(check(stations, r, k, mid)){
                left = mid;
            }
            else right = mid - 1;
        }

        return left;
    }

    bool check(vector<int> stations, int r, int k, LL mid){
        int n = stations.size();
        LL total = 0;
        // x x x x
        for(int i = 0; i <= min(r-1, n-1); i++){
            total += stations[i];
        }
        for(int i = 0; i < n; i++){
            if(i+r < n){
                total += (LL)stations[i+r];
            }

            if(i-r-1 >= 0){
                total -= (LL)stations[i-r-1];
            }

            if(total >= mid) continue;

            LL diff = mid - total;
            if(diff > k) return false;
            stations[min(n-1, i+r)] += diff;
            total = mid;
            k -= diff;
        }

        return true;
    }
};
