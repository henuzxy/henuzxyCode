#include<bits/stdc++.h>

using namespace std;
const int MAX_V = 10010;
const int INF = 0x3f3f3f3f;
class Edge{
public:
    int to,cap,rev;
    Edge();
    Edge(int _to,int _cap,int _rev);
};
vector<Edge> G[MAX_V];
int level[MAX_V],iter[MAX_V];

void add(int u,int v,int cap){
    G[u].push_back(Edge(v,cap,(int)G[v].size()));
    G[v].push_back(Edge(u,0,(int)G[u].size()-1));
}


void bfs(int s){
    memset(level,-1,sizeof(level));
    queue<int> q;
    level[s] = 0;q.push(s);
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i=0;i<G[v].size();i++){
            Edge &e = G[v][i];
            if(e.cap > 0 && level[e.to] < 0){
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

int dfs(int s,int t,int f){
    if(s == t)  return f;
    for(int &i = iter[s];i < G[s].size();i++){
        Edge &e = G[s][i];
        if(e.cap > 0 && level[e.to] > level[s]){
            int d = dfs(e.to,t,min(f,e.cap));
            if(d > 0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s,int t){
    int res = 0;
    while(true){
        bfs(s);
        if(level[t] < 0)    return res;
        memset(iter,0,sizeof(iter));
        int f;
        while((f = dfs(s,t,INF)) > 0)
            res += f;
    }
}
int main(void){



}

Edge::Edge(){
    to = cap = rev = 0;
}
Edge::Edge(int _to,int _cap,int _rev){
    to = _to;
    cap = _cap;
    rev = _rev;
}
