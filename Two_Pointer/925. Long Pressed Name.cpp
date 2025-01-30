// TC:O(n) SC:O(1)
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int m = name.size(), n = typed.size(), i = 0, j = 0;
        while(i < m && j < n) {
            if(name[i] == typed[j]) {
                i += 1;
                j += 1;
            }
            else if(i - 1 >= 0 && (name[i-1] == typed[j])) j += 1;
            else break;
        }
        while(j < n) {
            if(j - 1 >= 0 && typed[j-1] == typed[j]) j += 1;
            else break;
        }

        return i == m && j == n;
    }
};
