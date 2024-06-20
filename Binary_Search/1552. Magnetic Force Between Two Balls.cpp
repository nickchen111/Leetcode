/*
1552. Magnetic Force Between Two Balls
*/

// TC:O(lg(maxVal)*m*lgn + nlgn) SC:O(1) 
class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        int n = position.size();

        int left = 1;
        int right = position[n-1] - position[0];
        while(left < right){
            int mid = left + (right - left+1)/2;
            if(check(mid, position, m)){
                left = mid;
            }
            else right = mid - 1;
        }

        return left;
        
    }

    bool check(int mid, vector<int>& position, int m){
        int count = 1;
        int n = position.size();
        int cur = position[0];
        while(count < m){
            auto iter = lower_bound(position.begin(), position.end(), cur+mid);
            if(iter != position.end()) {
                count += 1;
                cur = *iter;
            }
            else break;
        }

        if(count < m) return false;

        return true;
    }
};

// TC:O(lg(maxVal)*n) SC:O(1)
class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        int n = position.size();

        int left = 1;
        int right = position[n-1] - position[0];
        while(left < right){
            int mid = left + (right - left+1)/2;
            if(check(mid, position, m)){
                left = mid;
            }
            else right = mid - 1;
        }

        return left;
        
    }

    bool check(int mid, vector<int>& position, int m){
        int count = 1;
        int n = position.size();
        for(int i = 0; i < n; i++){
            int j = i + 1;
            while(j < n && position[j] - position[i] < mid){
                j++;
            }
            if(j == n) break;
            count += 1;
            i = j-1;
            if(count == m) return true;
        }

        return false;
    }
};


/*
平均分配球到指定的位置上 問說最大的最小距離可以為多少
*/
