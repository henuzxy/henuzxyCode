#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
const double eps = 1e-8;
const int MAX_V = 2300;
const double INF = 0x3f3f3f3f;
struct Edge{
    int to,rev;
    double cap;
    Edge();
    Edge(int _to,double _cap,int _rev);
};
vector<Edge> G[MAX_V];
int level[MAX_V],iter[MAX_V];
pair<int,int> p[MAX_V];
int N,M;
void add_Edge(int u,int v,double cap){
    G[u].push_back(Edge(v,cap,(int)G[v].size()));
    G[v].push_back(Edge(u,0,(int)G[u].size()-1));
}
void Creat_Map(double g){
    for(int i=0;i<=N+M+1;++i) G[i].clear();
    int s = 0,t = N+M+1;
    for(int i=1;i<=N;++i){
        add_Edge(i,t,g);
    }
    for(int i=1;i<=M;++i){
        add_Edge(N+i,p[i].first,INF);
        add_Edge(N+i,p[i].second,INF);
        add_Edge(s,N+i,1.0);
    }
}

void bfs(int s){
    memset(level,-1,sizeof(level));
    queue<int> q;
    level[s] = 0;q.push(s);
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i=0;i<G[v].size();i++){
            Edge &e = G[v][i];
            if(e.cap > eps && level[e.to] < 0){
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

double dfs(int s,int t,double f){
    if(s == t)  return f;
    for(int &i = iter[s];i < G[s].size();i++){
        Edge &e = G[s][i];
        if(e.cap > 0 && level[e.to] > level[s]){
            double d = dfs(e.to,t,min(f,e.cap));
            if(d > 0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
double max_flow(int s,int t){
    double flow = 0;
    while(true){
        bfs(s);
        if(level[t] < 0)    return flow;
        memset(iter,0,sizeof(iter));
        double f;
        while((f = dfs(s,t,INF)) > 0)
            flow += f;
    }
}
bool used[MAX_V];
void dfs(int s){
    used[s] = true;
    for(int i=0;i<G[s].size();++i){
         Edge &e = G[s][i];
         if(!used[e.to] && e.cap > 0){
            dfs(e.to);
         }
    }
}
//#define Local
int main(void){
    #ifdef Local
        freopen("in.txt","r",stdin);
    #endif // Local
    scanf("%d%d",&N,&M);
    if(M == 0){
        cout << 1 << endl;
        cout << 1 << endl;
        return 0;
    }
    int u,v;
    for(int i=1;i<=M;++i){
        scanf("%d%d",&p[i].first,&p[i].second);
    }
    int s = 0,t = N+M+1;
    double l = 0,r = M;
    double Min = 1.0/N/N;
    while(r - l >= Min){
        double mid = (l+r)/2;
        Creat_Map(mid);
        double f = M - max_flow(s,t);
        if(f > 0)
            l = mid;
        else
            r = mid;
    }
    Creat_Map(l);
    memset(used,false,sizeof(used));
    max_flow(s,t);
    dfs(s);
    vector<int> vec;
    for(int i=1;i<=N;++i){
        if(used[i]){
           vec.push_back(i);
        }
    }
    cout << vec.size() << endl;
    for(int i=0;i<vec.size();++i){
        cout << vec[i] << endl;
    }
    return 0;
}
Edge::Edge(){
    to = rev = 0;
    cap = 0;
}
Edge::Edge(int _to,double _cap,int _rev){
    to = _to;
    cap = _cap;
    rev = _rev;
}

/*
https://blog.csdn.net/pi9nc/article/details/12263855
题意：一个公司有n个人，给出了一些有冲突的人的对数(u,v)，公司决定裁人，那么总裁现在要裁掉冲突率最高的那些人（冲突率=在这些人中存在的冲突数/人数）。就是求出一些点，这些点之间的边数/点数最大。最大密度子图。

思路：胡伯涛的论文《最小割模型在信息学竞赛中的应用》介绍了两种方法：

第一种：转换为最大权闭合图的模型来求解：

设max g = f(x)= |E‘|/|V’| ，找一个子图的边数与点数的比值达到其中的最大，我们通常都是构造一个函数max h（g）= |E'|-g*|V'|,当h(g)为0的时候，g的值即为最优，h（g）>0 时 g<最优值， h(g)<0时，g>最优值；因为如果最大值大于0那么我们就可以继续增加g的值来减小h(g),若最大值都小于0了，那么g不可能增加只可能减少！

观察h（g）,边和点有依赖关系，就边依赖点，边存在的必要条件是点的存在，那么这样以后，如果我们将边看成点，那么这不就符合最大权闭合子图了。现在h（g）的求法就可以通过求新图的最大权闭合子图的值来求解，但是这里有个问题，建图之后你可以发现当求出来的值和h（g）原本应该为值不对应（具体为什么不怎么理解），可以这样理解，当最小的一个g使得h（g）为0的时候该解即为最优解，因为h(g)是以个单调递减函数，就该函数来看只可能存在一个g使得h（g）=0；然而通过求最大权闭合子图是子图权值和为0的有很多中g，当最小的一个g使得h（g）为0之后，如果g继续增大那么虽然通过最大权闭合子图的值求出来依旧为0，但是真正的h（g）< 0 了，所以要使得最优的一个解就是使得最大权闭合子图的权值和为0的最小的一个g值！这样求解之后从源点流到汇点为满流的边即为最大密度子图中的点。

第二种：

源点到各个点连接一条有向边权值为U,各个点到汇点连接一条边权值为U+2*g-d，原来有关系的点连接两条有向边（u,v），（v,u）权值为1（U可以取m，U的目的是用来使得2*g-d的值始终为正），这样以后求最小割，那么h（g）= （U*n-mincut）/2;二分找到最优值即为mid ，但是如果要求图中的点则需要用left来从新图求最大流之后然后从源点开始dfs遍历，最后得出结果。

*/
