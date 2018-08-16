using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX = 1010;
int a[MAX],dp[MAX],N;´Ó0¿ªÊ¼
int LIS(){
    fill(dp,dp+N,INF);
    for(int i=0;iN;++i){
        lower_bound(dp,dp+N,a[i]) = a[i];
    }
    return lower_bound(dp,dp+N,INF)-dp;
}
