#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<set>
#include<queue>
#include<map>
#include<cstdio>

using namespace std;
const int MAX_V = 110;
const int INF = 0x3f3f3f3f;
class Edge{
public:
    int to,cap,cost,rev;
    Edge();
    Edge(int _to,int _cap,int _cost,int _rev);
};
int V;
vector<Edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V],preve[MAX_V];
void add_Edge(int from,int to,int cap,int cost){
    G[from].push_back(Edge(to,cap,cost,(int)G[to].size()));
    G[to].push_back(Edge(from,0,-cost,(int)G[from].size()-1));
}
void spfa(int s){
    fill(dist,dist+1+V,INF);
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    while(!que.empty()){
        int v = que.front();que.pop();
        for(int i=0;i<G[v].size();++i){
            Edge &e = G[v][i];
            if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
                dist[e.to] = dist[v] + e.cost;
                prevv[e.to] = v;
                preve[e.to] = i;
                que.push(e.to);
            }
        }
    }
}
int min_cost_flow(int s,int t,int f){
    int res = 0;
    while(f > 0){
        spfa(s);
        if(dist[t] == INF)  return -1;
        int d = f;
        for(int v = t;v != s;v = prevv[v])
            d = min(d,G[prevv[v]][preve[v]].cap);
        f -= d;
        res += d*dist[t];
        for(int v = t;v != s;v = prevv[v]){
            Edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}