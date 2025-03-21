# Lab2

__林文浩 PB21050974__

#### P1004 红黑树

红黑树的实现主要是插入和删除比较困难，插入的时候优先插入红色节点，这样可以使得不平衡的程度最小，然后再根据四种不同情况调整

1. 新节点是根节点，直接变黑

2. 父节点是黑色时无需调整，直接插入

3. 父节点是红色，叔叔节点也是红色，将他们颜色变成黑色，爷爷节点变成红色即可，但是爷爷节点有可能又和再往上冲突，因此要递归调用平衡的方法。

4. 父节点红，叔叔节点黑，里面再细分两类 1、爷父子共线 2、爷父子不共线，根据具体情况通过至多两次旋转和换色就能重新平衡

删除操作更麻烦，我参考了别人的处理做法，思考了为什么会这么做，现在我大致的观点是这样的：当节点有两个孩子时与至多只有一个孩子的节点交换再删除，是为了后面的删除更方便，而到了真正要删除的时候，由于会造成子树的不平衡，我们要优先给缺少黑色的一侧补上一层黑节点，如果成功则平衡成功，但是如果实在不行，再想办法给黑节点数足够的一侧去掉一层黑节点，这样子的话局部的子树会平衡，但是总体不平衡了，接着就可以递归调用这个方法来使得树往上继续平衡，直到根节点所以一般方法中分的很多类都是按照这个逻辑来的，能直接平衡的就直接平衡，不能的就先局部平衡再递归。具体有下面几种情况：

1. 满侧孩子为红节点
2. 满侧孩子为黑节点，且其两个子节点均为黑节点，局部根为红节点
3. 满侧孩子为黑节点，且其两个子节点均为黑节点，局部根为黑节点
4. 满侧孩子为黑节点，且其两个子节点不全为黑节点，远侧孙节点为红节点
5. 满侧孩子为黑节点，且其两个子节点不全为黑节点，远侧孙节点为黑节点

当然这只是一个方向的，考虑到有左右方向应该有更多的处理，这些情况我在代码里已经注释好了，因为讲起来实在是太多了，所以我这里也不详细写了，不过有一点需要注意的是涉及到根节点时一般要特殊处理。

#### P1005 区间合并

哈希函数的实现上课讲过，这里就不写了，这题的大致思路是先把数组转变成区间和数组，也就是B[i]代表A[0]~A[i]的和的形式，这样就能后面在O(1)内求和，然后每次选一个l2，然后r2从l2一直变到n，

对每个(l2,r2),以它的和为key去哈希表里找value加到总结果里去，value就是0~l2-1区间内的和为key的区间数，然后将A[i]-A[l2] (0<=i<=l2)的和为key将对应的value加一，这样就能保证每次统计与(l2,r2)相同和的区间时，l2之前的区间全部已经在哈希表里了，而超过l2的区间都包括在内。

我确信我的做法是O（n^2）的，不过不知道为什么无论我用链表的方式处理哈希冲突还是用再哈希还是用二次再探测法，无论哈希函数取什么样，都总有一两个测试点超时。目前还没有很好的解决办法。

