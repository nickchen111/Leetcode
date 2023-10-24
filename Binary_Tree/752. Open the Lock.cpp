/*
752. Open the Lock
*/

//BFS TC:O(10^4) SC:O(10^4)
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        //設立一個set紀錄哪些不能走
        unordered_set<string> dead(deadends.begin(), deadends.end());
        //記錄走過的string 組合
        unordered_set<string> visited;
        
        queue<string> q;
        q.push("0000");
        visited.insert("0000");
        int step = 0;
        while(!q.empty()){
            int n = q.size();
            //看這層裡面有哪些可以做選擇
            for(int i = 0; i<n; i++){
                string temp = q.front();
                q.pop();

                if(dead.count(temp)) continue;//不能走此路
                if(temp == target) return step;//找到了
                for(int j = 0; j<4; j++){
                    string up = plusOne(temp, j);
                    if(!visited.count(up)){
                        q.push(up);
                        visited.insert(up);
                    }

                    string down = minusOne(temp,j);
                    if(!visited.count(down)){
                        q.push(down);
                        visited.insert(down);
                    }
                }
            }
            step++;
        }
        return -1; //沒有可走到的走法
    }

    string plusOne(string str, int j){
        if(str[j] == '9') str[j] = '0';
        else str[j]+=1;
        return str;
    }
    string minusOne(string str, int k){
        if(str[k] == '0') str[k] = '9';
        else str[k]-=1;
        return str;
    }
};
