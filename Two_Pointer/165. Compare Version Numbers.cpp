/*
165. Compare Version Numbers
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int m = version1.size();
        int n = version2.size();
        int i = 0, j = 0;
        while(i < m || j < n){
            int num1 = 0;
            int num2 = 0;
            int start1 = i;
            int start2 = j;
            bool flag1 = 0;
            bool flag2 = 0;
            while(i < m && version1[i] != '.'){
                i++;
                flag1 = true;
            }
            if(flag1){
                num1 = stoi(version1.substr(start1, i-start1));
            }
            while(j < n && version2[j] != '.'){
                j++;
                flag2 = true;
            }
            if(flag2){
                num2 = stoi(version2.substr(start2, j-start2));
            }
            if(num1 > num2) return 1;
            else if(num1 < num2) return -1;
            i++;
            j++;
        }

        return 0;
    }
};
