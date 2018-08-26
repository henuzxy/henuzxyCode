#include<bits/stdc++.h>

using namespace std;
const int MAX_V = 100010;
const int MAX_E = 400010;
const int INF = 0x3f3f3f3f;

class Edge{
public:
    int to,cap,nex;
    Edge();
    Edge(int _to,int _cap,int _nex);
};
Edge edg[MAX_E];
int head[MAX_V],dis[MAX_V],gap[MAX_V],iter[MAX_V];
int V,cnt;
void init(){
    cnt = 0;
    memset(head,-1,sizeof(head));
}
void add_Edge(int from,int to,int cap){
    edg[cnt] = Edge(to,cap,head[from]);
    head[from] = cnt++;
    edg[cnt] = Edge(from,0,head[to]);
    head[to] = cnt++;
}
void BFS(int s,int t){
    memset(dis,-1,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = 1;
    dis[t] = 0;
    queue<int> que;
    que.push(t);
    while(!que.empty()){
        int u = que.front();que.pop();
        for(int i=head[u];~i;i=edg[i].nex){
            int v = edg[i].to;
            if(dis[v] == -1){
                dis[v] = dis[u]+1;
                que.push(v);
                gap[dis[v]]++;
            }
        }
    }
}
int S[MAX_V];
int SAP(int s,int t){
    int res = 0;
    BFS(s,t);
    int top = 0;
    for(int i=0;i<=V;++i){
        iter[i] = head[i];
    }
    int u = s;
    int i;
    while(dis[s] < V){
        if(u == t){
            int temp = INF;
            int inser;
            for(i=0;i<top;++i){
                if(temp > edg[S[i]].cap){
                    temp = edg[S[i]].cap;
                    inser = i;
                }
            }
            for(int i=0;i<top;++i){
                edg[S[i]].cap -= temp;
                edg[S[i]^1].cap += temp;
            }
            res += temp;
            top = inser;
            u = edg[S[top]^1].to;

        }
        if(u != t && gap[dis[u]-1] == 0)    break;
        for(i=iter[u];~i;i=edg[i].nex){
            if(edg[i].cap != 0 && dis[u] == dis[edg[i].to]+1)
                break;
        }
        if(i != -1){
            iter[u] = i;
            S[top++] = i;
            u = edg[i].to;
        }
        else{
            int Min = V;
            for(int i = head[u];~i;i=edg[i].nex){
                if(edg[i].cap == 0) continue;
                if(Min > dis[edg[i].to]){
                    Min = dis[edg[i].to];
                    iter[u] = i;
                }
            }
            --gap[dis[u]];
            dis[u] = Min+1;
            ++gap[dis[u]];
            if(u != s)  u = edg[S[--top]^1].to;
        }
    }
    return res;
}
/*
序号是从1到V的最大流，记得要初始V,和init()
*/
Edge::Edge(){
    to = cap = nex = 0;
}
Edge::Edge(int _to,int _cap,int _nex){
    to = _to;
    cap = _cap;
    nex = _nex;
}