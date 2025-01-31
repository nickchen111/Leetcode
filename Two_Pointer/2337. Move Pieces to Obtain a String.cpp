/*
2337. Move Pieces to Obtain a String
*/

// Two Pointer TC:O(n) SC:O(1)
class Solution {
public:
    bool canChange(string start, string target) {
        int n = start.size(), i = 0, j = 0;
        while(i < n && j < n) {
            while(start[i] == '_') i += 1;
            while(target[j] == '_') j += 1;
            if(i == n && j ==n) return true;
            if(start[i] == target[j] && ((start[i] == 'R' && i <= j) || (start[i] == 'L' && i >= j))) {
                i += 1;
                j += 1;
            }
            else return false;
        }
        while(i < n && start[i] == '_') i += 1;
        while(j < n && target[j] == '_') j += 1;
        return i == n && j == n;
    }
};

// Two Pass TC:O(n) SC:O(n)
class Solution {
public:
    bool canChange(string start, string target) {
        vector<int> pos1;
        vector<int> pos2;
        string str1;
        string str2;
        // two pass
        for(int i = 0; i < start.size(); i++){
            if(start[i] == 'L'){
                str1 += 'L';
                pos1.push_back(i);
            }
            else if(start[i] == 'R'){
                str1 += 'R';
                pos1.push_back(i);
            }
            if(target[i] == 'L'){
                str2 += 'L';
                pos2.push_back(i);
            }
            else if(target[i] == 'R'){
                str2 += 'R';
                pos2.push_back(i);
            }
        }

        if(str2 != str1) return false;

        for(int i = 0; i < str1.size(); i++){
            if(str1[i] == 'L'){
                if(pos1[i] < pos2[i]) return false;
            }
            else if(str1[i] == 'R'){
                if(pos1[i] > pos2[i]) return false;
            }
        }

        return true;
    }
};

/*
＿代表空格 L 是可左移方塊 R是可又移方塊
問說string start 能否移成target
two pass
1. 空格拿掉 字串一定要相等
2. 再來看方向  start L 要在 target L 右邊或一樣位置 start R 要在 target R左邊或一樣位置 
one pass Two pointer
直接通通在一同一loop判斷
*/
