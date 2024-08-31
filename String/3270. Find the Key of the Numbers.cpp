/*
3270. Find the Key of the Numbers
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int generateKey(int num1, int num2, int num3) {
        string s1 = to_string(num1);
        string s2 = to_string(num2);
        string s3 = to_string(num3);
        while(s1.size() < 4) {
            s1 = '0' + s1;
        }
        while(s2.size() < 4) {
            s2 = '0' + s2;
        }
        while(s3.size() < 4) {
            s3 = '0' + s3;
        }
        
        string key;
        for(int i = 0; i < 4; i++){
            int minVal = min(s1[i]-'0', min(s2[i]-'0', s3[i]-'0'));
            key += (minVal+'0');
        }
        
        return stoi(key);
        
        
    }
};
