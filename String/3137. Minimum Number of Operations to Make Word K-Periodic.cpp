/*
3137. Minimum Number of Operations to Make Word K-Periodic
*/

// TC:O(n) SC:O(n/k)
class Solution {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k) {
        int n = word.size();
        int maxFreq = 0;
        unordered_map<string, int> map;
       
        string s;
        for(int i = 0; i < n; i+= k){
            s = word.substr(i,k);
            map[s] += 1;
            if(map[s] > maxFreq){
                maxFreq = map[s];
            }
        }
        
        int res = (n - maxFreq*k) / k;
        
        return res;
     }
};

/*
可以取代長度為k的某個字串 by 不重疊的某個長度為k的字串 問說最少換幾次讓他變成perodic
"hnccccajbwccajut"
2
*/
