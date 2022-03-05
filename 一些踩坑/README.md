# 关于我刷题踩坑这挡事

## 在数据量大时，使用对每个循环使用memset导致超时

```cpp
    //bad
    cin >> T;
    while(T--){
        cin >> N;
        memset(cnt,0,sizeof(cnt));
    }

    //good
    while(T--){
        cin >> N;
        vector<int> cnt(N,0);
    }
```

当T和N都是2e5的规模时，这里就会导致超时，正确的姿势应该是下面那种，因为题目会保证N的和不超过2e5,所以如果你每次都初始化2e5这么大，肯定会超时。

## 在考虑一些区间算法的时候，最后的区间没有被计算

例如每次考虑长度为K的区间，在[N-K,N]这个区间一定不要忘记,能用if break，不要想着在for里面不执行它，这个根本不是优化，反而会让自己踩坑。

```cpp
    //bad
    for(int i = 1;i+K<=N;i += 1){   
        sum -= book[i];
        sum += book[i+K];
        for(int j=1;j<=M;j+=1){
            res = (res + C(book[i],j)*C(sum,M-j)%Mod) % Mod;
        }
    }

    //good
    for(int i = 1;i<=N;i += 1){
        sum -= book[i];
        if(i+K <= N){
            sum += book[i+K]; 
        }
        for(int j=1;j<=M;j+=1){
            res = (res + C(book[i],j)*C(sum,M-j)%Mod) % Mod;
        }
    }
```

## 在考虑特判问题时一定要确定特判的那个点是否被触发

```cpp
    //bad
    for(int i = 1;i <= N;i += 1){
        auto it = mp.lower_bound(b[i]);
        if(it != mp.end() && (it->first) == b[i]){
            res[it->second] = i;
            mp.erase(it);
        }
    }
    if(res[M] == 0){
        cout << "NO" << endl;
        return;
    }
    //good
    for(int i = 1;i <= N;i += 1){
        if(res[M] != 0){
            break;
        }
        if(b[i] == c[M]){
            res[M] = i;
        }
    }
    if(res[M] == 0){
        cout << "NO" << endl;
        return;
    }
```

上一个会出现c[M] = b[i],但是没有匹配到c[M]的情况

## 做模拟题目要把每个操作都拆分成一个小函数，让思路更加清晰

```cpp
void run(int &now,int dir,int add){

}
bool inrange(int l,int r,int value){
 
}
int getdir(int now,int target){
 
}
void solve(){}
```

## 二维坐标映射为一维坐标，一定要注意基数是一行的个数，而不是最大值

例如：0 <= x, y <= 1000，如果基数认为是1000，那么机会出现(0,1000),(1000,0)映射结果都是1000，所以切记，这里是1001或者更大的数，更大的数，只会相当于末尾的数不存在，浪费一些空间，但是绝对不会出现重复导致错误。


## 回文串之类的题目，要左右l,r两个变量向中间靠近，不要想着固定l,直接计算r的最大位置。

踩坑题目: https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/
错误代码：https://leetcode.com/contest/biweekly-contest-73/submissions/detail/653880058/
正确代码：https://leetcode.com/submissions/detail/653935330/
```cpp
for(int l=0;l<=m;l++){
    int r = N-1-l;//典型
    if(s[l] != s[r]){
        for(int j=r-1;j>l;j--){
            if(s[l] == s[j]){
                res += r-j;
                // cout << l << " " << j << " " << r << endl;
                s = s.substr(0,j) + s.substr(j+1,r-j) + s[j] + s.substr(r+1);
                // cout << s << endl;
                break;
            }
        }
    }
}
```

这里想着枚举l，直接就确定r的位置，但是实际如果存在一个单数的字符在l的前面，那么l的位置对应算出来的r的位置就不正确了。
