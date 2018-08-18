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
���⣺һ����˾��n���ˣ�������һЩ�г�ͻ���˵Ķ���(u,v)����˾�������ˣ���ô�ܲ�����Ҫ�õ���ͻ����ߵ���Щ�ˣ���ͻ��=����Щ���д��ڵĳ�ͻ��/���������������һЩ�㣬��Щ��֮��ı���/�����������ܶ���ͼ��

˼·�������ε����ġ���С��ģ������Ϣѧ�����е�Ӧ�á����������ַ�����

��һ�֣�ת��Ϊ���Ȩ�պ�ͼ��ģ������⣺

��max g = f(x)= |E��|/|V��| ����һ����ͼ�ı���������ı�ֵ�ﵽ���е��������ͨ�����ǹ���һ������max h��g��= |E'|-g*|V'|,��h(g)Ϊ0��ʱ��g��ֵ��Ϊ���ţ�h��g��>0 ʱ g<����ֵ�� h(g)<0ʱ��g>����ֵ����Ϊ������ֵ����0��ô���ǾͿ��Լ�������g��ֵ����Сh(g),�����ֵ��С��0�ˣ���ôg����������ֻ���ܼ��٣�

�۲�h��g��,�ߺ͵���������ϵ���ͱ������㣬�ߴ��ڵı�Ҫ�����ǵ�Ĵ��ڣ���ô�����Ժ�������ǽ��߿��ɵ㣬��ô�ⲻ�ͷ������Ȩ�պ���ͼ�ˡ�����h��g�����󷨾Ϳ���ͨ������ͼ�����Ȩ�պ���ͼ��ֵ����⣬���������и����⣬��ͼ֮������Է��ֵ��������ֵ��h��g��ԭ��Ӧ��Ϊֵ����Ӧ������Ϊʲô����ô��⣩������������⣬����С��һ��gʹ��h��g��Ϊ0��ʱ��ý⼴Ϊ���Ž⣬��Ϊh(g)���Ը������ݼ��������͸ú�������ֻ���ܴ���һ��gʹ��h��g��=0��Ȼ��ͨ�������Ȩ�պ���ͼ����ͼȨֵ��Ϊ0���кܶ���g������С��һ��gʹ��h��g��Ϊ0֮�����g����������ô��Ȼͨ�����Ȩ�պ���ͼ��ֵ���������Ϊ0������������h��g��< 0 �ˣ�����Ҫʹ�����ŵ�һ�������ʹ�����Ȩ�պ���ͼ��Ȩֵ��Ϊ0����С��һ��gֵ���������֮���Դ���������Ϊ�����ı߼�Ϊ����ܶ���ͼ�еĵ㡣

�ڶ��֣�

Դ�㵽����������һ�������ȨֵΪU,�����㵽�������һ����ȨֵΪU+2*g-d��ԭ���й�ϵ�ĵ�������������ߣ�u,v������v,u��ȨֵΪ1��U����ȡm��U��Ŀ��������ʹ��2*g-d��ֵʼ��Ϊ�����������Ժ�����С���ôh��g��= ��U*n-mincut��/2;�����ҵ�����ֵ��Ϊmid ���������Ҫ��ͼ�еĵ�����Ҫ��left������ͼ�������֮��Ȼ���Դ�㿪ʼdfs���������ó������

*/
