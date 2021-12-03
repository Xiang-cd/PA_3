# prefix 报告



## 解题思路：

令next[i]表示最长的前缀l, 使得l是i的一个后缀, 



abab

next[0] = -1  ct= 1    len  =1

next[1] = -1  ct = 1 +1   len = 1

next[2] =  0  ct =  1 + 2 + 1  len = 2

next[3] = 1  ct = 1 + 4 +  1  len = 2 

2+2+1+1

