# Trie(字典樹)

Trie 是一種樹狀結構，可以用來在大量字串中快速搜尋某個字串。當然這樣問題也可以用 hash table 來解決，但是 Trie 在解決以下問題上有其優勢，

找出每個有特定 prefix 的字串
按照字典順序列出所有字串

hash table 面對上述問題，有兩個缺點

如果 input 大部份都擁有一樣的 prefix ，hash table 相對 trie 會耗費較多記憶體空間。
hash table 可能發生碰撞，導致搜尋的 time complexity 高達 O (n) ，n 是總共插入的資料數量; 而 Trie 執行搜尋可以保持時間複雜度僅有 O (k)，k 是搜尋字串的長度。
Trie 樹利用字串之間的共同前綴，將重複的前綴放在同一條路徑上，即可畫出樹狀架構。

總之trie跟hash table 就是時間與空間上的trade off hashtable查找字串速度快 而 trie空間利用度較低當有很多前綴字相同時
