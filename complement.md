###### 补码

#### -x = -x + $2^n$ (由于溢出位被舍弃)

如 0,1011 + 1,0000 = 1011

#### = $2^{n-1}$ - x + 1

eg: 求 -3 

###### 由原码 3: 0011 ,  -3: 1011

-3 = 3 + 1,0000 = 1111 - 3 + 0001 = 1100 + 0001

###### 所以-3的补码 

###### 用-3的原码将除符号位外的其他位翻转 再将最低位加1得到

##### from 3 to -3

###### 用1111 - 0011（这一步只需要将 0011 的每一位用 Not 处理即可），再最低位加1

###### 就得到了 -3 的机器码