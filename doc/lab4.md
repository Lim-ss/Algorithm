# Lab4

__林文浩 PB21050974__

#### P1009 合并果子

由于越早合并越容易被多次计算代价，为了让总代价最小，应该优先合并最小的数，当这些数能组成完全三叉树时，总代价一定最小的情况一定是完全三叉树，当不能组成完全三叉树时，通过填补值为0的点使之满足组成完全三叉树的条件即可。为了高效取得最小值，用优先队列来存储这些数，建堆需要$O(n)$，每次合并需要$O(logn)$，需要合并大约$\frac{n}{2}$次，因此总时间复杂度为$O(nlogn)$

#### P1010 一场豪赌，朋友！

设扔至多$n$次骰子的最优策略期望是$E(n)$。假设第一次投掷投出了点数 $j$，如果选择收手，则条件期望就是 $j$ 本身，如果不收手，选择继续投，由于该问题的无记忆性，因此条件概率为 $E(n-1)$，为了达到最优当$j>E(n-1)$时，需要选择收手，反之需要选择继续投，从而$E(n)=\sum_{i=1}^{\lfloor E(n-1) \rfloor}E(n-1)*p(i) + \sum_{i=\lfloor E(n-1) \rfloor+1}^{m}i*p(i) = $

$E(n-1)*\sum_{i=1}^{\lfloor E(n-1) \rfloor}p(i) + \sum_{i=\lfloor E(n-1) \rfloor+1}^{m}i*p(i)$  ，为了快速求得这两个求和，可以提前计算并分别存入两个数组中，仅耗时$O(n)$。由于$E(1)$已知，因此只需递推就能求出$E(n)$，总时间复杂度为$O(n)$

#### P1011 狂扁小怪兽

显然应该先把总效果为加血的怪先打了，再打总效果为减血的，然后加血怪里面，为了保证有尽量多的血量去打扣血多的怪，应该先打扣血少的，再打扣血多的。在减血怪里面，用逆序思维，反过来从最后一个怪开始，回血变扣血，扣血变回血，那么怪就变成加血怪了，变成了刚刚的问题，应该从后往前是“减血”越来越多，也就是从前往后加血越来越少。因此将怪物分为positive和negative两组，第一组按a升序排列，第二组按照b降序排列（排列前需要给怪物赋上id），按序将id存入临时数组内，并每次循环内判断是否会死亡，如果死亡直接返回-1，如果成功结束循环，则输出临时数组内的id。总时间复杂度主要为排序时间$O(nlogn)$

#### P1012 最长下降子序列

之前作业已经做过，因为这次不需要输出序列，只需要输出最大长度，所以更加简单，只需要用贪心算法，如果下一个数a小于等于已有子序列的末尾，则直接加上，否则用二分查找，往前找到第一个小于a的数，用a替换掉，最终得到的子序列并不一定是下降子序列，但是长度就是最长下降子序列的长度。总时间复杂度为$O(nlogn)$
