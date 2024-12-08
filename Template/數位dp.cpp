function<int(int i, bool isLimit, bool isNum)> dfs = [&](int i, bool isLimit, bool isNum) -> int {
            if(i == m) {
                return isNum;
            }
            if(!isLimit && memo[i] != -1 && isNum && isValid) return memo[i];
            int res = 0;
            // 代表是否有數字過了!?
            if(!isNum) {
                res = dfs(i+1, false, false);
            }
            int up = isLimit ? s[i]-'0' : 9;
            for(int j = 1-(isNum); j <= up; j++) {
                if(inValid[j]) continue;
                res = res + dfs(i+1, isLimit && j == up, true); 
            }

            if(!isLimit && isNum) memo[i] = res;
            
            return res;
        };
