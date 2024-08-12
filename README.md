# 线性同余方程

## 定义

形如
$$
ax \equiv b \pmod p
$$

的方程称为 **线性同余方程** (Linear Congruence Equation) 。其中，$a$ 、$b$ 和 $n$ 为给定整数，$x$ 为未知数。需要从区间 $[0,n-1]$ 中求解 $x$ , 当解不唯一时需要求出全体解。

## 求解

1. 用逆元

- 当 $\gcd(a,n)=1$ 时，可以计算 $a$ 的逆元 $a^{-1}$ ，根据同余方程的性质，可以得到 $x \equiv ba^{-1} \pmod n$，从而求出唯一解。

- 当 $\gcd(a,n) \neq 1$，此时不一定有解，例如对于如下方程：
  $$
  2x \equiv 1 \pmod 4
  $$
  此时无解。

  设 $g=\gcd(a,n)$，显然，当 $g \nmid b$ 时无解，反之，可将 $a,n,b$ 都进行约分。

  设约分后的新方程为：
  $$
  a'x \equiv b' \pmod n'
  $$
  此时 $a'$ 和 $n'$ 已经互质，所以可以用求解逆元的方式解方程。

2. 用扩展欧几里得算法求解

   **定理1:** 对于线性同余方程 $ax \equiv b \pmod n$ 我们对它进行变换，变换成线性不定方程。
   $$
   ax=kn+b (根据同余的定义) \\
   ax-kn=b
   $$
   ​			根据 **裴蜀定理**，只要  $\gcd(a,n) \mid b$ , 方程就有解。

   

   



# 费马小定理

## 定义

设 $p \in P$ , 对于 $\forall {a} \in \N$ , 满足
$$
a^p \equiv a \pmod p
$$
若 $\gcd(a,p) = 1$ ，则满足：

$$
a^{p-1} \equiv 1 \pmod p
$$


## 证明

### 普通方法

构造一个序列 $A = \{1, 2, 3, ..., p - 1\}$

设 $\gcd(a, p) = 1$

因为 $\gcd(A_i, p) = 1$，$\gcd(a, p) = 1$

所以 $\gcd(A_i \times a, p) = 1$

再设 $f = (p - 1)!$

则
$$
\begin {aligned}
f &= (p - 1)! \\
&= A_1 \times A_2 \times ... \times A_{p-1} \\
&\equiv a \times A_1 \times a \times A_2 \times ... \times a \times A_{p-1} \pmod p \\
&\equiv a^{p-1} \times f
\end {aligned}
$$
证毕。

### 归纳法

设 $a^p \equiv a \pmod p$ , 则根据二项式定理，

$$
\begin{aligned}
(a+1)^p &= \sum_{i = 0}^{p} {a^i \times 1^{p-i} \times C_p^{i}} \\
&= \sum_{i = 0}^{p} {a^i \times C_p^{i}}
\end{aligned}
$$
因为
$$
C_p^{i} = \frac{p!}{i! \times (p - i)!}
$$

易得：
$$
\begin {align}
\forall {1 \le i \le p - 1} , p \mid C_p^{i}
 \end {align}
$$

$$
\begin {align}
\forall {1 \le i \le p - 1} , C_p^{i} \equiv 0 \pmod p
\end {align}
$$

也就是说，
$C_p^{i}$ 中除了 $C_p^{0}$ 和 $C_p^{p}$ 外，剩余的 $C_p^{i} \equiv 0 \pmod p$ ，所以最后化简得
$$
\begin {align}
(a+1)^p \equiv a^p + 1 \pmod p
\end {align}
$$
又因为
$$
a^p \equiv a \pmod p
$$
所以
$$
(a+1)^p \equiv (a+1) \pmod p
$$
证毕。

# 乘法逆元

## 定义

对于一个线性同余方程 $$ ax \equiv 1 \pmod b$$ , 则 $x$ 称为 $a \bmod b$ 的逆元，记作 $a^{-1}$。

## 求法

1. 扩展欧几里得算法

   证法见**线性同余方程**

   ```cpp
   void exgcd(int a, int b, int &x, int &y) {
       if (b == 0) {
           x = 1;
           y = 0;
           return;
       }
       exgcd(b, a % b, x, y);
       int t = x;
       x = y;
       y = t - a / b * t;
   }
   ```

   在求时我们只需输入：

   ```cpp
   exgcd(a, b, x, y);
   ```

   

   由于 $x$ 最后可能为负，所以我们要进行一下处理，将最终答案变为

   ```cpp
   x = (x + MOD) % MOD;
   ```

2. 快速幂 + 费马小定理

   $\because ax \equiv 1 \pmod b$

   $\therefore ax \equiv a^{b-1} \pmod b$ (根据费马小定理)

   $\therefore x \equiv a^{b-2} \pmod b$

   然后就可以用快速幂来求了。

   ```cpp
   int qpow(int a, int b) {
       int ret = 1;
       while (b) {
           if (b & 1)
               ret = 1ll * ret * a % p;
           a = 1ll * a * a % p;
           b >>= 1;
       }
       return ret;
   }
   ```

   要求：模数 $b$ 是质数。对于扩展欧几里得法只要求 $\gcd(a,b)=1$

3. 线性求逆元

   上述方法可以在 $O(logn)$ 的复杂度内求解一个数的逆元，现在我们提供一个可以在 $O(n)$ 的复杂度内求解 $1$ ~ $n$ 中每个数的逆元的方法。

   首先，显然 $1^{-1} \equiv 1 \pmod p$ 

   证明：在模任意大于 $1$ 的模数 $p$ 意义下，都有 $1 \times 1 \equiv 1 \pmod p$，证毕。

   对于 $i^{-1}$，我们令 $k = \lfloor \frac{p}{i} \rfloor $，$j=p \bmod i$，有 $p = ki + j$，所以 $ki + j \equiv 0 \pmod p$;

   两边同时乘 $i^{-1} \times j^{-1}$:

   $kj^{-1}+i^{-1} \equiv 0 \pmod p$

   $i^{-1} \equiv -kj^{-1} \pmod p$

   再代入 $j = p \bmod i$，$k=\lfloor \frac{p}{i} \rfloor$，得：

   $i^{-1} \equiv -\lfloor \frac{p}{i} \rfloor (p \bmod i)^{-1} \pmod p$

   注意 $p \bmod i < i$

   所以在计算 $i^{-1}$ 时，$(p \bmod i)^{-1}$ 已经算过。

   从而可以 $O(n)$ 推出所有逆元。

   ```cpp
   inv[1] = 1;
   for (int i = 2; i <= n; ++i)
       inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
   ```

4. 线性求任意 $n$ 个数的逆元

   给定 $n$ 个数 $a_i$，满足 $1 \le a_i < p$

   首先计算前缀积，记为 $s_i$，然后利用快速幂或扩展欧几里得算法求出 $s_n^{-1}$

   根据定义，$s_i^{-1}=s_{i+1}^{-1} \times (i+1)$

   从而逆推出每个前缀积的逆元，然后在利用

   $a_i^{-1}=s_i^{-1} \times s_{i-1}$ 得到每个数的逆元。

   ```cpp
   s[0] = 1;
   for (int i = 1; i <= n; ++i)
       s[i] = s[i - 1] * a[i] % p;
   s_inv[i] = qpow(s[n], p - 2);
   //这里也可以用 exgcd 来求
   for (int i = n - 1; i >= 1; --i)
       s_inv[i] = s_inv[i + 1] * (i + 1) % p;
   for (int i = 1; i <= n; ++i)
       inv[i] = s_inv[i] * s[i - 1] % p;
   ```

   时间复杂度：$O(n+logp)$

   运用，求 $1$ ~ $n$ 中每个数的阶乘的逆元。

   ```cpp
   s[0] = 1;
   for (int i = 1; i <= n; ++i)
       s[i] = s[i - 1] * i % p;
   exgcd(s[n], p, x, y);
   x = (x + p) % p;
   inv[n] = x;
   for (int i = n - 1; i >= 1; --i)
       inv[i] = inv[i + 1] * (i + 1) % p;
   ```

# 欧拉定理

## 定义

定义 $\varphi$ 为欧拉函数，$\varphi(n)$ 表示 $1$ ~ $n$ 中与 $n$ 互质的数的个数。

未完待续。。。
