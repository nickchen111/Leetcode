/*
2960. Count Tested Devices After Test Operations
*/

// 最優解  TC:O(n) SC:O(1) 
class Solution {
public:
    int countTestedDevices(vector<int>& batteryPercentages) {
        int count = 0;
        int n = batteryPercentages.size();
        for(int i = 0; i < n; i++){
            if(batteryPercentages[i] - count > 0){
                count++;
            }
        }
        
        return count;
    }
};

// Brute force TC:O(n^2) SC:O(1) 
class Solution {
public:
    int countTestedDevices(vector<int>& batteryPercentages) {
        int count = 0;
        int n = batteryPercentages.size();
        for(int i = 0; i < n; i++){
            if(batteryPercentages[i] > 0){
                count++;
                for(int j = i + 1; j < n; j++){
                    if(batteryPercentages[j] > 0) batteryPercentages[j] -= 1;
                }
            }
        }
        
        return count;
    }
};
