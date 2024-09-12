/*
1684. Count the Number of Consistent Strings
*/

// Bit TC:O(n*10) SC:O(1)
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int allw=0;
        for(int i=0;i<allowed.size();i++){
            allw |= (1 << (allowed[i]-'a'));
        }

        int cnt=0;
        for(int i=0;i<words.size();i++){
            int wc=0;
            for(int j=0;j<words[i].size();j++){
                if(allw & (1 << (words[i][j]-'a')))
                    wc++;
                if(words[i].size()==wc)
                    cnt++;
            }
        }

        return cnt;
    }
};

// Bitset TC:O(n*10) SC:O(26)
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int count = 0;
        bitset<26> bit;
        for(auto ch : allowed){
            int num = ch - 'a';
            bit.set(num); // 此位置設置為1
        }
        for(int i = 0; i < words.size(); i++){
            bool flag = 1;
            for(int j = 0; j < words[i].size(); j++){
                int num = words[i][j]-'a';
                if(bit.test(num) == 0) { // 判斷此位置是否為1
                    flag = 0;
                    break;
                }
            }

            if(flag) count += 1;
        }

        return count;
    }
};

// Hash Map TC:O(n*10) SC:O(26)
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int count = 0;
        vector<int> map(26);
        for(auto ch : allowed){
            map[ch-'a'] += 1;
        }

        for(int i = 0; i < words.size(); i++){
            bool flag = 1;
            for(int j = 0; j < words[i].size(); j++){
                if(map[words[i][j]-'a'] == 0) {
                    flag = 0;
                    break;
                }
            }

            if(flag) count += 1;
        }

        return count;
    }
};
