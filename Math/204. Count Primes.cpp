/*
204. Count Primes
*/


//簡化效率最低的埃氏篩
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> isPrime(n, true);
        int count = 0;
        for(int i = 2; i<n; i++){
            if(isPrime[i] == false) continue;
            count++;
            for(int j = 2*i; j<n; j+=i){
                isPrime[j] = false; 
            }
        }

        return count;
    }
};

//加入埃氏篩的定義 i*i <n 並且優化多於重複計算的部分 TC:O(nlglgn) SC:O(n)
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> isPrime(n, true);

        for(int i = 2; i*i<n; i++){ // 埃氏篩：意即只需要 i < sqrt(n)的部分就好 前面的計算已涵蓋到後面
            if(isPrime[i] == false) continue;
            //從i*i開始而非 2*i 跳過前面重複計算的部分 ex: 2*2*2 = 8, 4*2 = 8
            for(int j = i*i; j<n; j+=i){
                isPrime[j] = false; 
            }
        }

        int count = 0;
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                count++;
            }
        }

        return count;
    }
};

//優化寫在其他地方
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> isPrime(n, true);
        int count = 0;

        for(int i = 2; i<n; i++){ 
            if(isPrime[i] == false) continue;
            count++;
            if(i < sqrt(n))// 埃氏篩：意即只需要 i < sqrt(n)的部分就好 前面的計算已涵蓋到後面
                for(int j = 2*i; j<n; j+=i){
                    isPrime[j] = false; 
                }
        }



        return count;
    }
};


//brute force
class Solution {
    //brute force
public:
    int countPrimes(int n) {
        int count = 0;
        for(int i = 2; i<n; i++){
            if(isPrime(i)) count++;
        }

        return count;
    }

    bool isPrime(int n){
        for(int i = 2; i<n; i++){
            if(n%i == 0) return false;
        }

        return true;
    }
};


/*
本題是埃氏篩的程式碼實現
1.brute force TC:O(n^2)
2. 埃氏篩： TC:O(nlglgn)
解釋：
n*(1/2 + 1/3 + 1/4 +....) => n*lgn 但是中間過程像是4 6都會在2的時候被判定為非prime所以不會run到
因此進一步優化了時間複雜度變成 n*lglgn 
2: 4, 6, 8, 10, ....
3: 3, 6, 9, 12, 15....
5: 5, 10, 15,20,....
按照埃氏篩寫完後還可以做兩個小地方優化
*/
