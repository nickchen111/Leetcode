/*
1286. Iterator for Combination
*/

// TC:O(n) SC:O(n)
class CombinationIterator {
    string cur;
    string end;
    bool flag;
    string characters;
    int combinationLength;
public:
    CombinationIterator(string characters, int combinationLength) {
        cur = characters.substr(0, combinationLength);
        end = characters.substr(characters.size() - combinationLength);
        flag = 1;
        this -> combinationLength = combinationLength;
        this -> characters = characters;
    }
    
    string next() {
        if(flag){
            flag = 0;
            return cur;
        }

        // 跟77題一樣先從最後面的元素開始判斷
        int i = cur.size()-1;
        while(i >= 0 && cur[i] == characters[i + characters.size() - combinationLength]) i--;
        
        int j = 0;
        while(cur[i] != characters[j]) j++;
        for(int k = i; k < cur.size(); k++){
            cur[k] = characters[j + 1 + k - i];
        }

        return cur;

    }
    
    bool hasNext() {
        return flag == 1 || cur != end;
    }
};

/*
此題是跟77題一樣的 Combinatorics 題目
不同點在於 這次往後遍歷的東西不是有固定順序的而是一串字串
so ex: 給你 七個字元 要求組出五個字串 每個字的最大最小值怎麼求出
a c e f g u z -> a 最小為 a 最大為 e... 所以也就是目前index + (7-5)
*/
