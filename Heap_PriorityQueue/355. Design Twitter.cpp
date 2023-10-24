/*
355. Design Twitter
*/



class Twitter {
    //使用兩個hash map實現
    unordered_map<int, set<int>>friends;//面向user有哪些朋友 userid -> set of followee 
    unordered_map<int, vector<pair<int, int>>> tweet;//這些人發了哪些文 userid-> {timestamp, tweetid}
    int globalTime;
public:
    Twitter() {
        globalTime = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        follow(userId,userId);//這樣你才不會看不到自己的貼文
        globalTime++;
        tweet[userId].push_back({globalTime, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        set<pair<int, int>> news; //用這個來記錄動態
        for(auto i: friends[userId]){//我追蹤的名人i 想知道他們的動態
            for(int j = tweet[i].size()-1; j>=0; j--){//從後面比較新的開始加入
                if(news.size() < 10){
                    news.insert(tweet[i][j]);
                }
                else if(tweet[i][j].first > news.begin()->first){//加進來的動態比我最舊的動態還要新
                    news.erase(news.begin());
                    news.insert(tweet[i][j]);
                }
                else break;//後面也不會比較新的動態啦
            }
        }

        vector<int> ans;
        for(auto a:news){//new有人用哩
            ans.push_back(a.second);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    
    void follow(int followerId, int followeeId) {
        friends[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if(followerId != followeeId){
            friends[followerId].erase(followeeId);
        }
    }
};

/*
设计如下的数据结构：
unordered_map<int,set>Friends; //记录每个用户的好友（包括自己）
int global_id; // 全局变量，记录所有推文的时间顺序。
unordered_map<int,vector<pair<int,int>>>Tweets; // 记录每个用户发推的global_id和tweetID。

在getNewsFeed时，遍历所有好友的推文记录，寻找最近的10个。
基本思路是构造一个数据结构news，每次放进一个推文，news能够自动保持根据global_id保持有序。什么数据结构能实现这个功能呢？
有两个方案：priority_queue，或者有序set。考虑到set里的元素已经是pair，并且其自动排序就是依照pair的第一个key从小到大，在这里更为方便。

時間複雜度分析：
postTweet 操作的時間複雜度為 O(1)，因為它只需要更新用戶的推文列表。
getNewsFeed 操作的時間複雜度主要取決於用戶的朋友數目和用戶的推文數目。在最壞情況下，需要遍歷用戶的所有朋友的推文，然後進行插入和刪除操作，最終返回前10個動態。
因此，時間複雜度為 O(F * (T + 10))，其中 F 是用戶的朋友數目，T 是用戶的平均推文數目。通常情況下，這個操作的時間複雜度應該是可接受的，因為 F 和 T 都不會太大。
follow 和 unfollow 操作的時間複雜度均為 O(1)，因為它們只涉及到對哈希映射的操作。

空間複雜度分析：
friends 哈希映射用於存儲每個用戶的朋友列表，空間複雜度取決於用戶數目和其朋友的數目，即 O(U + F)，其中 U 是用戶數目，F 是所有用戶的平均朋友數目。
tweet 哈希映射用於存儲每個用戶的推文，空間複雜度取決於用戶數目和他們的推文數目，即 O(U + T)，其中 U 是用戶數目，T 是所有用戶的平均推文數目。
*/

//自己改了一下用pq
class Twitter {
    int globalTime;
    unordered_map<int, set<int>> user2Friend;//紀錄每個user有追蹤哪些人 user->各種userid
    unordered_map<int, vector<pair<int, int>>> tweet2Time;//紀錄user的每個tweet 是在何時發的 userid-> time, tweetid
public:
    Twitter() {
        globalTime = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        follow(userId, userId);
        globalTime++;
        tweet2Time[userId].push_back({globalTime, tweetId});
    }
    
    //考點在這
    vector<int> getNewsFeed(int userId) {
        //要如何維持前十個新的news -> 將時間做排序 ->排序自己的跟大家的 ->用啥容器排序好！？-> pq or set
        //返回tweetId
        vector<int> res;
        auto comp = [](pair<int,int> a, pair<int,int> b){
            return a.first < b.first;//大頂堆 時間較大的較新
        };
        priority_queue<pair<int, int>, vector<pair<int,int>>, decltype(comp)> pq(comp);
        //要怎麼取出tweetid
        for(auto fri:user2Friend[userId]){ //friend 為某個userId
            for(int j = tweet2Time[fri].size()-1; j>=0; j--){ //從後面開始++ 
                
                pq.push({tweet2Time[fri][j].first, tweet2Time[fri][j].second});
            }
        }

        while(res.size() < 10 && pq.size() != 0){
            res.push_back(pq.top().second);
            pq.pop();
        }

        return res;


    }
    
    void follow(int followerId, int followeeId) {
        user2Friend[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        if(followerId != followeeId){
            user2Friend[followerId].erase(followeeId);
        }
    }
};

//按照la大的寫 測資一直有問題
class Twitter {
private:
    //需先建立起user 跟 tweet貼文本身兩個class
    class Tweet{
    private:
        int id;
        Tweet* next;
        int timestamp;
    public:
        Tweet(int id){
            this->id = id;
            //更新時間
            this->timestamp = globalTime++;
        }
        int getId(){
            return id;
        }
        int getTimestamp(){
            return timestamp;
        }
        Tweet* getNext(){
            return next;
        }
        void setNext(Tweet* next){
            this->next = next;
        }
    };

    class User{
    private:
        int id;
        unordered_set<User*> followedUserSet;
        Tweet* tweethead;

    public:
        User(int id){
            this->id = id;
            followedUserSet = unordered_set<User*>();
            this->tweethead = nullptr;
        }

        int getId(){
            return id;
        }

        unordered_set<User*> getFollowedUserSet(){
            return followedUserSet;
        }

        Tweet* getTweethead(){
            return tweethead;
        }

        void follow(User* other){
            followedUserSet.insert(other);
        }

        void unfollow(User* other){
            followedUserSet.erase(other);
        }

        void post(Tweet* tweet){
            tweet->setNext(tweethead);
            tweethead = tweet;
        }
    };
    unordered_map<int, User*> idToUser;
    int globalTime = 0;
    
public:
    Twitter() {
    }
    
    void postTweet(int userId, int tweetId) {
        if(idToUser.find(userId) == idToUser.end()){
            idToUser[userId] = new User(userId);
        }
        User* user = idToUser[userId];
        user->post(new Tweet(tweetId));
    }
    
    vector<int> getNewsFeed(int userId) {
        //從自己有追蹤的人上面找動態 自己如果有po也要包含進來 by pq
        vector<int> ans = {};
        if(idToUser.find(userId) == idToUser.end()) return ans;
        User* user = idToUser[userId];
        unordered_set<User*> followedUserSet = user->getFollowedUserSet();
        
        auto cmp = [](Tweet* a, Tweet* b){
            //大的在堆頂
            return a->getTimestamp() < b->getTimestamp();
        };

        priority_queue<Tweet*, vector<Tweet*>, decltype(cmp)> pq(cmp);
        if(user->getTweethead() != nullptr){
            pq.push(user->getTweethead());
        }
        for(User* other:followedUserSet){
            if(other->getTweethead() != nullptr){
                pq.push(other->getTweethead());
            }
        }
        //開始把pq pop出來
        int count = 0;
        while(!pq.empty() && count < 10){
            Tweet* tweet = pq.top(); pq.pop();
            ans.push_back(tweet->getId());
            if(tweet->getNext() != nullptr){
                pq.push(tweet->getNext());
            }
            count++;
        }

        return ans;
    }
    
    void follow(int followerId, int followeeId) {
        if(idToUser.find(followerId) == idToUser.end()){
            idToUser[followerId] = new User(followerId);
        }
        if(idToUser.find(followerId) == idToUser.end()){
            idToUser[followeeId] = new User(followeeId);
        }
        User* user = idToUser[followerId];
        User* other = idToUser[followeeId];
        user->follow(other);
    }
    
    void unfollow(int followerId, int followeeId) {
        if(idToUser.find(followerId) == idToUser.end() || idToUser.find(followeeId) == idToUser.end()){
            return;
        }
        User* user = idToUser[followerId];
        User* other = idToUser[followeeId];
        user->unfollow(other);
    }
};

