#include<bits/stdc++.h>

using namespace std;
const int MAX_N = 1e5+10;
typedef long long ll;
vector<int> G[MAX_N];
ll value[MAX_N],num[MAX_N];
ll sum[MAX_N];
int N,M;
ll dfs(int now){
    ll tot = 1;
    for(int i=0;i<G[now].size();++i){
        tot += dfs(G[now][i]);
    }
    num[now] = tot;
    return tot;
}
void cal_sum(){
    for(int i=1;i<=N;++i){
        sum[i] = num[i]*(N-num[i]);
    }
}
int main(void){
    scanf("%d",&N);
    int x,y;
    for(int i=2;i<=N;++i){
        scanf("%d%d",&x,&y);
        G[x].push_back(i);
        value[i] = y;
    }
    dfs(1);
    cal_sum();
    ll res = 0;
    for(int i=1;i<=N;++i){
        res += sum[i]*value[i];
    }
    printf("%lld\n",res);
    scanf("%d",&M);
    int a,b;
    for(int i=1;i<=M;++i){
        scanf("%d%d",&a,&b);
        if(b >= value[a]){
            res += (b-value[a])*sum[a];
            value[a] = b;
        }
        else{
            res -= (value[a]-b)*sum[a];
            value[a] = b;
        }
        printf("%lld\n",res);
    }
    return 0;
}
/*
https://nanti.jisuanke.com/t/16446
*/
