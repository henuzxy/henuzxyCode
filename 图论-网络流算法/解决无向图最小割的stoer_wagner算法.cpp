#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<cstdio>

using namespace std;
const int MAX = 510;
const int INF = 0x3f3f3f3f;
int N,M;
int v[MAX],w[MAX];
int e[MAX][MAX];
bool used[MAX];
int stoer_wagner(){
    int res = INF;
    for(int i=0;i<N;++i){
        v[i] = i;
    }
    while(N > 1){
        int pre = 0;
        memset(used,false,sizeof(used));
        memset(w,0,sizeof(w));
        for(int i=1;i<N;++i){
            int k = -1;
            for(int j=1;j<N;++j){
                if(!used[v[j]]){
                    w[v[j]] += e[v[pre]][v[j]];
                    if(k == -1 || w[v[j]] > w[v[k]])
                            k = j;
                }
            }
            used[v[k]] = true;
            if(i == N-1){
                int s = v[pre],t = v[k];
                res = min(res,w[t]);
                for(int j=0;j<N;++j){
                    e[s][v[j]] += e[v[j]][t];
                    e[v[j]][s] += e[v[j]][t];
                }
                v[k] = v[--N];
            }
            pre = k;
        }
    }
    return res;
}
//#define Local
int main(void){
    #ifdef Local
        freopen("in.txt","r",stdin);
    #endif
    while(scanf("%d%d",&N,&M) != EOF){
        int u,v,w;
        memset(e,0,sizeof(e));
        for(int i=0;i<M;++i){
            scanf("%d%d%d",&u,&v,&w);
            e[u][v] += w;
            e[v][u] += w;
        }
        printf("%d\n",stoer_wagner());
    }
    #ifdef Local
        fclose(stdin);
    #endif // Local


    return 0;
}
