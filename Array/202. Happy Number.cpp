/*
202. Happy Number
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> set;
        while( n != 1){
            int sum = 0;
            while(n/10){
                sum+=pow(n%10,2);
                n/=10;
            }
            sum+=pow(n%10,2);
            if(set.find(sum) != set.end()) return false;
            set.insert(sum);
            n = sum;
        }

        return true;
    }
};

// 分兩個函式寫
class Solution {
private:
    int nextNumber(int n){
        int newNumber = 0;
        while(n != 0){
            int num = n % 10;
            newNumber += num*num;
            n /=10;
        }
        return newNumber;
    }
public:
    bool isHappy(int n) {
        unordered_set<int> set;
        while(n != 1 && !set.count(n)){
            set.insert(n);
            n = nextNumber(n);
        }
        return n==1; //不是的話會return false:0
    }
};

/*
2
4
16
1+6^2 = 37
3 + 7->58
5 + 8 -> 25+64 -> 89
8+9 -> 64+81-> 145
1+4+5->42
4+2-> 16+4->20
*/
