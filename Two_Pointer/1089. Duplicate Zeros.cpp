// TC:O(n) SC:O(1)
class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int i = 0, j = 0;
        while(j < n) {
            if(arr[i] == 0) j += 1;
            i++, j ++;
        }
        j--, i--;
        while(i >= 0) {
            if(j < n) arr[j] = arr[i];
            if(arr[i] == 0 && --j >= 0) {
                arr[j] = 0;
            }
            j--, i--;
        }
    }
};
