// Gosper's Hack
// Iterate all the m-bit state where there are k 1-bits.

int state = (1 << k) - 1;            
while (state < (1 << m))
{
    doSomething(state);

    int c = state & - state;
    int r = state + c;
    state = (((r ^ state) >> 2) / c) | r;
}

// 3116題時的程式碼
int m = nums.size();
for(int k = 1; k <= m; k++){
    int state = (1<<k) -1;
    LL sum = 0;
    while(state < (1<<m)){
        LL product = 1;
        for(int i = 0; i < m; i++){
            if((state >> i)&1) {
                product = product * coins[i] / gcd(product, coins[i]);
            }
        }
        sum += (mid/product);
        
        int c = state&-state;
        int r = state + c;
        state = (((r^state)>>2)/c ) | r;
    }
    
    // do something
}

/*
Gosper's Hack
先要了解 low bit 就是最後面那個1與他之後的0
ex : 101011110 的low bit為10
補數:
x = 01011101
~x= 10100010 + 1
然後把-x & x 就會得到low bit
low bit = x & -x
就可以拆解為左半與右半部分組合起來就會是下一個二進位數
左半:x + low bit
右半: x^(x+low bit) 之後會得到很多一 我們想把一些1都先移到最右邊 直接除以low bit 之後呢 再將他移過取兩位就會是右半部分該有的1的數量
*/



/*
int c = state & -state;：這一行程式碼使用了位元運算中的位與（AND）操作符號 &，將 state 和 state 的補數 -state 進行位元與運算。補數的計算是取反加一的操作，即 ~state + 1。位元與操作會將 state 中最右邊的 1 保留下來，其他位元都設為 0。這樣就得到了 c，它是 state 中最右邊的 1 所在的位元位置。

int r = state + c;：這一行程式碼將 state 和 c 相加，這樣就將 state 中最右邊的 1 變成了 0，而其右邊的 0 也都變成了 1。

state = (((r ^ state) >> 2) / c) | r;：這一行程式碼是將 state 中除了最右邊的 1 之外的其他位元都進行 XOR 運算，然後右移 2 位再除以 c（也就是最右邊的 1 所在的位元位置），最後再與 r 進行位或運算。這樣做的目的是為了將 state 中原本的 1 移動到新的位置，並且保持其他位元不變。

綜合以上三步，這段程式碼的作用是將具有特定數量的位元為1的二進位數字 state 轉換成下一個具有相同位元為1數量的二進位數字。因此，這樣的程式碼可以用來生成具有特定特徵的二進位數字的排列組合，例如只有兩個1的排列組合。
*/
