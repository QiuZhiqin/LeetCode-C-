#include "common.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>

using namespace std;

/* Solution for leetcode problem: https://leetcode.cn/problems/open-the-lock/description/ */
class SolutionForOpenLock {
    public:
        string cur, tar;
        unordered_set<string> deads;
        int openLock(vector<string>& deadends, string target) {
            cur = "0000";
            tar = target;
            if(cur == target)
                return 0;

            for(const auto& d : deadends)
                deads.insert(d);
            if(deads.count(cur))
                return -1;
            int ans = bfs();
            return ans;
        }
        /* BFS from two directions: start and target */
        int bfs() {
            queue<string> d1,d2;
            unordered_map<string,int> m1,m2;
            d1.push(cur);
            m1[cur] = 0;
            d2.push(tar);
            m2[tar] = 0;
            /* Loop until one of the queue is empty.
             * If one of the queue is empty, it means that we cant find the target in this direction.
             */
            while(d1.size() && d2.size()){
                int t = -1;
                if(d1.size() <= d2.size()){
                    t = update(d1,m1,m2);
                }
                else{
                    t = update(d2,m2,m1);
                }
                if(t != -1)
                    return t;
            }
            return -1;
        }
        int update(queue<string>& q, unordered_map<string,int>& cur, unordered_map<string,int>& other) {
            int m = q.size();
            while (m-- > 0) {
                string t = q.front();
                q.pop();
                int step = cur[t];
                for(int i = 0; i < 4; i++){
                    for(int j = -1; j <= 1; j++){
                        if(j == 0)
                            continue;
                        int origin = t[i] - '0';
                        int next = (origin + j) % 10;
                        if(next == -1)
                            next = 9;
                        string copy = t;
                        copy[i] = '0' + next;
                        if(deads.count(copy) || cur.count(copy))
                            continue;
                        if(other.count(copy))
                            return step + 1 + other[copy];
                        else{
                            q.push(copy);
                            cur[copy] = step + 1;
                        }
                    }
                }
            }
            return -1;
        }
};