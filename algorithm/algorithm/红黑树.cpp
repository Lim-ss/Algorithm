#include <cstdio>
#include <functional>

//红黑树（Red Black Tree）
class RBT
{
public:
	RBT();
	void Insert(int value);
	void Delete(int value);
	void Print();

private:
	enum Color;
	struct Node;

	void PreOrderTraverse(Node* node, std::function<void(Node*)> func);
	void LeftRotate(Node* node);
	void RightRotate(Node* node);
	void Balance(Node* node);
	void Adjust(Node* node, bool leftLack);
	void Delete(Node* node);

	int size;
	Node* root;

};
enum RBT::Color
{
	Red = 0,
	Black = 1,
};

struct RBT::Node
{
	Color color;
	int element;
	Node* parent;
	Node* lchild;
	Node* rchild;
	Node(int element, Node* parent);
	inline void InvertColor();
	inline static void ExchangeColor(Node* n1, Node* n2);
};

//默认构造红节点
RBT::Node::Node(int element, Node* parent)
	:color(Color::Red),
	element(element),
	parent(parent),
	lchild(nullptr),
	rchild(nullptr)
{
	
}

void RBT::Node::InvertColor()
{
	color = (Color)(1 - (int)color);
}

void RBT::Node::ExchangeColor(Node* n1, Node* n2)
{
	Color c = n1->color;
	n1->color = n2->color;
	n2->color = c;
}

RBT::RBT()
	:size(0),
	root(nullptr)
{

}

void RBT::Insert(int value)
{
	Node* n = root;
	Node* previous = nullptr;
	while (n != nullptr)
	{
		previous = n;
		if (value < n->element)
			n = n->lchild;
		else
			n = n->rchild;
	}
	if (n == root)
	{
		root = new Node(value, nullptr);
		root->InvertColor();
	}
	else
	{
		if (value < previous->element)
		{
			previous->lchild = new Node(value, previous);
			Balance(previous->lchild);
		}
		else
		{
			previous->rchild = new Node(value, previous);
			Balance(previous->rchild);
		}
	}
	size++;
}

void RBT::Delete(int value)
{
	Node* n = root;
	while (n != nullptr && n->element != value)
	{
		if (value < n->element)
			n = n->lchild;
		else
			n = n->rchild;
	}
	if (n != nullptr)
		Delete(n);
	return;
}

//for debug
//顺序输出所有元素
void RBT::Print()
{
	printf("RBT: ");
	PreOrderTraverse(root, [](Node* node) {printf("%d ", node->element);});
	printf("\n");
}

//for debug
//前序遍历
void RBT::PreOrderTraverse(Node* node, std::function<void(Node*)> func)
{
	if (node == nullptr)
		return;
	PreOrderTraverse(node->lchild, func);
	func(node);
	PreOrderTraverse(node->rchild, func);
	return;
}

//左旋，要求node及其右孩子非空
void RBT::LeftRotate(Node* node)
{
	Node* n0 = node->parent;
	Node* n1 = node;
	Node* n2 = node->rchild;
	Node* n3 = n2->lchild;

	//处理n0和n1的连接
	n2->parent = n0;
	if (n0 != nullptr)
	{
		if (n0->lchild == n1)
			n0->lchild = n2;
		else
			n0->rchild = n2;
	}
	else
	{
		root = n2;
	}
	//处理n1和n2的连接
	n1->parent = n2;
	n2->lchild = n1;
	//处理n1和n3的连接
	if (n3 != nullptr)
	{
		n3->parent = n1;
	}
	n1->rchild = n3;
}

//右旋，要求node及其左孩子非空
void RBT::RightRotate(Node* node)
{
	Node* n0 = node->parent;
	Node* n1 = node;
	Node* n2 = node->lchild;
	Node* n3 = n2->rchild;

	//处理n0和n1的连接
	n2->parent = n0;
	if (n0 != nullptr)
	{
		if (n0->lchild == n1)
			n0->lchild = n2;
		else
			n0->rchild = n2;
	}
	else
	{
		root = n2;
	}
	//处理n1和n2的连接
	n1->parent = n2;
	n2->rchild = n1;
	//处理n1和n3的连接
	if (n3 != nullptr)
	{
		n3->parent = n1;
	}
	n1->lchild = n3;
}

//处理由于红节点node(插入或涂色)而破坏的平衡,node不可能是root
void RBT::Balance(Node* node)
{
	if (node->parent->color == Black)
	{
		//情况1，父节点为黑色
		//do nothing
	}
	else
	{
		//父节点红，此时一定存在爷节点
		Node* parent = node->parent;
		Node* grand = parent->parent;
		Node* uncle = (grand->lchild == parent) ? grand->rchild : grand->lchild;
		if (uncle != nullptr && uncle->color == Red)
		{
			//情况2，父节点和叔节点都为红色
			parent->InvertColor();
			grand->InvertColor();
			if (uncle != nullptr)
				uncle->InvertColor();
			if (grand == root)
				grand->InvertColor();
			else
				Balance(grand);//递归
		}
		else
		{
			//情况3，父节点红，叔节点黑
			//里面再细分两类 1、爷父子共线 2、爷父子不共线
			//又分左边和右边共 2x2=4种
			if (grand->lchild == parent)
			{
				//父在左边
				if (parent->lchild == node)
				{
					//共线
					parent->InvertColor();
					grand->InvertColor();
					RightRotate(grand);
				}
				else
				{
					//不共线
					LeftRotate(parent);
					node->InvertColor();
					grand->InvertColor();
					RightRotate(grand);
				}
			}
			else
			{
				//父在右边
				if (parent->rchild == node)
				{
					//共线
					parent->InvertColor();
					grand->InvertColor();
					LeftRotate(grand);
				}
				else
				{
					//不共线
					RightRotate(parent);
					node->InvertColor();
					grand->InvertColor();
					LeftRotate(grand);
				}
			}
		}
	}
}

//处理由于node的左右子树黑色层数不相同造成的不平衡
//leftLack==true表示左子树缺一层黑，缺失侧的孩子一定是黑节点
//node不可能是nullptr
void RBT::Adjust(Node* node, bool leftLack)
{
	//优先给缺侧补上一层黑节点，如果成功则平衡成功
	//如果不行再考虑给满侧去掉一层黑，使得两侧平衡，但此时整棵局部树就少了一层，则需要对上一层递归调用
	//注意以上操作中，如果该局部树的根原本是黑的，则最终局部根也只能是黑的
	//这样可以防止涂红导致与局部树的上层冲突（连续两红），或者无法继续递归（因为该函数要求缺失侧的孩子一定是黑节点）

	if (leftLack == true)
	{
		Node* n0 = node;
		Node* n1 = node->lchild;//缺侧
		Node* n2 = node->rchild;//满侧
		Node* n3 = n2->rchild;//满侧远侧孙节点
		Node* n4 = n2->lchild;//满侧近侧孙节点

		//情况1：满侧孩子为红节点
		//大致思路是利用旋转将满侧红节点的一颗子树转给缺侧，此时又会造成缺侧内部不平衡，需要递归
		if (n2->color == Color::Red)
		{
			LeftRotate(n0);
			n0->InvertColor();
			n2->InvertColor();
			Adjust(n0, true);
		}
		//情况2、3：满侧孩子为黑节点，且其两个子节点均为黑节点
		else if (n3->color == Color::Black && n4->color == Color::Black)
		{
			//情况2：局部根为红节点
			//直接改色即可平衡
			if (n0->color == Color::Red)
			{
				n0->InvertColor();
				n2->InvertColor();
			}
			//情况3：局部根为黑节点
			//直接改色可局部平衡，但总体少一层黑色，需递归
			else
			{
				n2->InvertColor();
				if (n0 == root)
				{
					//do nothing
				}
				else
				{
					if (n0->parent->lchild == n0)
						Adjust(n0->parent, true);
					else
						Adjust(n0->parent, false);
				}
			}
		}
		//情况4、5：满侧孩子为黑节点，且其两个子节点不全为黑节点
		else
		{
			//情况4：远侧孙节点为红节点
			//通过旋转增加缺侧一层黑，并维持局部根颜色不变，满侧少的一层黑由远侧孙节点变黑补回来
			//可总体平衡
			if (n3->color = Color::Red)
			{
				LeftRotate(n0);
				RBT::Node::ExchangeColor(n0, n2);
				n3->InvertColor();
			}
			//情况5：远侧孙节点为黑节点
			//通过旋转变成情况4
			else
			{
				RightRotate(n2);
				n2->InvertColor();
				n4->InvertColor();
				Adjust(n0, true);
			}
		}
	}
	else
	{
		Node* n0 = node;
		Node* n1 = node->rchild;//缺侧
		Node* n2 = node->lchild;//满侧
		Node* n3 = n2->lchild;//满侧远侧孙节点
		Node* n4 = n2->rchild;//满侧近侧孙节点

		//情况1：满侧孩子为红节点
		//大致思路是利用旋转将满侧红节点的一颗子树转给缺侧，此时又会造成缺侧内部不平衡，需要递归
		if (n2->color == Color::Red)
		{
			RightRotate(n0);
			n0->InvertColor();
			n2->InvertColor();
			Adjust(n0, false);
		}
		//情况2、3：满侧孩子为黑节点，且其两个子节点均为黑节点
		else if (n3->color == Color::Black && n4->color == Color::Black)
		{
			//情况2：局部根为红节点
			//直接改色即可平衡
			if (n0->color == Color::Red)
			{
				n0->InvertColor();
				n2->InvertColor();
			}
			//情况3：局部根为黑节点
			//直接改色可局部平衡，但总体少一层黑色，需递归
			else
			{
				
				n2->InvertColor();
				if (n0 == root)
				{
					//do nothing
				}
				else
				{
					if (n0->parent->lchild == n0)
						Adjust(n0->parent, true);
					else
						Adjust(n0->parent, false);
				}
			}
		}
		//情况4、5：满侧孩子为黑节点，且其两个子节点不全为黑节点
		else
		{
			//情况4：远侧孙节点为红节点
			//通过旋转增加缺侧一层黑，并维持局部根颜色不变，满侧少的一层黑由远侧孙节点变黑补回来
			//可总体平衡
			if (n3->color = Color::Red)
			{
				RightRotate(n0);
				RBT::Node::ExchangeColor(n0, n2);
				n3->InvertColor();
			}
			//情况5：远侧孙节点为黑节点
			//通过旋转变成情况4
			else
			{
				LeftRotate(n2);
				n2->InvertColor();
				n4->InvertColor();
				Adjust(n0, false);
			}
		}
	}
	return;
}

void RBT::Delete(Node* node)
{
	if (node->lchild != nullptr && node->rchild != nullptr)
	{
		//有两个孩子，不能直接删除，应该先与左子树的最大节点交换
		//这里只是简单交换了值，如果节点挂载数据较大，最好是通过指针重新组织的方式避免大量数据拷贝
		Node* n = node->lchild;
		while (n->rchild != nullptr)
			n = n->rchild;
		node->element = n->element;
		Delete(n);
		return;
	}

	//可以直接删除，分两大类
	//第一大类：删除红节点，或删除黑节点，但其有红色子节点，较为简单

	//注意，child可能为nullptr
	Node* child = (node->lchild == nullptr) ? node->rchild : node->lchild;
	if (node->color == Color::Red)
	{
		//删除的是红节点
		//不会破坏平衡，直接接上
		if (child != nullptr)
			child->parent = node->parent;
		if (node->parent->lchild == node)
			node->parent->lchild = child;
		else
			node->parent->rchild = child;
		delete node;
		return;
	}
	else if (child != nullptr && child->color == Color::Red)
	{
		//删除的是黑节点，但是其子节点是红的
		//用红节点变黑补回一个黑节点，重新平衡
		child->parent = node->parent;
		if (node == root)
		{
			root = child;
		}
		else
		{
			if (node->parent->lchild == node)
				node->parent->lchild = child;
			else
				node->parent->rchild = child;
		}
		child->InvertColor();
		delete node;
		return;
	}

	//第二大类：删除黑节点，且其子节点也是黑色的，这种情况较为复杂，需要递归
	//注意子节点可能为nullptr
	if (child != nullptr)
		child->parent = node->parent;
	if (node == root)
	{
		root = child;
	}
	else
	{
		if (node->parent->lchild == node)
		{
			node->parent->lchild = child;
			Adjust(child->parent, true);
		}
		else
		{
			node->parent->rchild = child;
			Adjust(child->parent, false);
		}
	}
	delete node;
	return;
}

int main()
{
	//test
	RBT tree;
	tree.Insert(10);
	tree.Insert(7);
	tree.Insert(-4);
	tree.Insert(0);
	tree.Insert(17);
	tree.Insert(988);
	tree.Insert(100);
	tree.Insert(20);

	tree.Delete(7);
	tree.Delete(988);
	tree.Delete(100);
	tree.Delete(222);
	tree.Delete(444);

	tree.Print();

}