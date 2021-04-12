https://leetcode-cn.com/problems/implement-rand10-using-rand7/

基础代码
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
std::random_device rd; // 真随机数生成器（但有些编译器没有实现），用于生成伪随机数生成器的种子
std::mt19937 eng(rd()); // 使用梅森旋转法作为伪随机数生成器，随机程度较好
std::uniform_int_distribution<int> dis(1, 7); // 10到20之间的整数均匀分布
int timeCount = 0; 
int rand7(){            //可以确定是均匀的，并且进行了验证。
    timeCount += 1;
    return dis(eng);
}
```
思路均是拒绝采样
做法一：期望次数:2.45
```cpp
int rand10_1() {
    int idx;
    do{
        int row = rand7();
        int col = rand7();
        idx = (row-1)*7+col;
    }while(idx > 40);
    return idx%10+1;
}
```
做法二：期望次数:2.2次
```cpp
int rand10_2() {
    while(true){
        int row = rand7();
        int col = rand7();
        int p = (row-1)*7+col;//1-49;
        if(p <= 40){
            return p%10+1;
        }
        row = p - 40;
        col = rand7();
        p = (row-1)*7+col;//1-63
        if(p <= 60){
            return p%10+1;
        }
        row = p-60;
        col = rand7();
        p = (row-1)*7+col;//1-21;
        if(p <= 20){
            return p%10+1;
        }
    }
}
```
做法三：期望次数:2.56次

```cpp
int rand6(){
    while(true){
        int value = rand7();
        if(value <= 6){
            return value;
        }
    }
    return 0;
}
int rand10_3() {
    int value = rand5();
    int t = rand6();
    if(t % 2 == 0){
        return value*2;
    }else{
        return value*2-1;
    }
}
```

做法四：期望次数:3.9

```cpp
int rand10_4(){
    int first = rand7();
    if(first <= 5){
        while(true){
            int second = rand7();
            if(second == 6){
                return first*2;
            }else if(second == 7){
                return first*2-1;
            }
        }
    }else{
        while(true){
            int second = rand7();
            if(second <= 5){
                if(first == 6){
                    return second*2;
                }else{
                    return second*2-1;
                }
            }
        }
    }
}
```