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
