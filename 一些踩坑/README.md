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