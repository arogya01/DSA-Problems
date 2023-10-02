#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// so the constraints are like:
// userid is between 1 and 500
// and tweet id is between 1 and 1000

// every user will have their own tweets, then should I use a hashmap...
// understood the basic working of desiging twitter, now have to figure out the apt data structs

// how do you store things like:
// userId =>
// it is a bit tricky, I'll have to write things down.

class Twitter
{
    // considering the design up till now.
    vector<int> user_ids;
    vector<int> tweets;
    queue<pair<int, int>> recentTweets;
    unordered_map<int, vector<int>> followersList;

public:
    Twitter()
    {
        user_ids[1] = 1;
    }

    void postTweet(int userId, int tweetId)
    {
        user_ids[userId] = 1;
        recentTweets.push(make_pair(userId, tweetId));
    }

    vector<int> getNewsFeed(int userId)
    {
        vector<int> newsfeed;

        while (!recentTweets.empty())
        {
            pair<int, int> tweet = recentTweets.front();
            if (tweet.first == userId)
                newsfeed.push_back(tweet.second);
            else if (find(followersList[userId].begin(), followersList[userId].end(), tweet.first) != followersList[userId].end())
            {
                newsfeed.push_back(tweet.second);
            }
        }
    }

    void follow(int followerId, int followeeId)
    {
        followersList[followerId].push_back(followeeId);
    }

    void unfollow(int followerId, int followeeId)
    {
        vector<int> &followeArr = followersList[followeeId];
        followeArr.erase(remove(followeArr.begin(), followeArr.end(), followeeId), followeArr.end());
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

int main()
{
    Twitter twitter;
    twitter.postTweet(1, 5);
    twitter.getNewsFeed(1);
}