/*
1652. Defuse the Bomb
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size();
        vector<int> res(n);
        int idx = 0;
        int i = 0; int j = 0;
        int sum = 0;
        if(k > 0) {
            i++;j++;
            while(j <= k) {
                sum += code[j%n];
                j++;
            }
            while(idx < n) {
                res[idx] = sum;
                sum += code[j%n];
                sum -= code[i%n];
                j++;i++;idx++;
            }
        }
        else if(k < 0) {
            int count = abs(k);
            j = ((j-1)%n + n) % n;
            i = 0;
            while(count) {
                sum += code[j%n];
                j = ((j-1)%n + n) % n;
                count--;
            }
            j++;
            while(idx < n) {
                res[idx] = sum;
                sum += code[i%n];
                sum -= code[j%n];
                j++;i++;idx++;
            }
        }
        else return res;

        return res;
    }
};
