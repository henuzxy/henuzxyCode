# Redis

## 五种基本数据结构

string,hash,list,set,sorted set.

## 新增数据结构

### HyperLogLog 

Redis 在2.8.9版本添加了HyperLogLog结构,用来做基数统计的结构，在输入元素或者体积非常大时，计算基数所需的空间时固定的。

PFADD key element. 添加一个元素
PFCOUNT key. 统计基数

