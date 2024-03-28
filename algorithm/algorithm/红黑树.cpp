#include <cstdio>
#include <functional>

//�������Red Black Tree��
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

//Ĭ�Ϲ����ڵ�
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
//˳���������Ԫ��
void RBT::Print()
{
	printf("RBT: ");
	PreOrderTraverse(root, [](Node* node) {printf("%d ", node->element);});
	printf("\n");
}

//for debug
//ǰ�����
void RBT::PreOrderTraverse(Node* node, std::function<void(Node*)> func)
{
	if (node == nullptr)
		return;
	PreOrderTraverse(node->lchild, func);
	func(node);
	PreOrderTraverse(node->rchild, func);
	return;
}

//������Ҫ��node�����Һ��ӷǿ�
void RBT::LeftRotate(Node* node)
{
	Node* n0 = node->parent;
	Node* n1 = node;
	Node* n2 = node->rchild;
	Node* n3 = n2->lchild;

	//����n0��n1������
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
	//����n1��n2������
	n1->parent = n2;
	n2->lchild = n1;
	//����n1��n3������
	if (n3 != nullptr)
	{
		n3->parent = n1;
	}
	n1->rchild = n3;
}

//������Ҫ��node�������ӷǿ�
void RBT::RightRotate(Node* node)
{
	Node* n0 = node->parent;
	Node* n1 = node;
	Node* n2 = node->lchild;
	Node* n3 = n2->rchild;

	//����n0��n1������
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
	//����n1��n2������
	n1->parent = n2;
	n2->rchild = n1;
	//����n1��n3������
	if (n3 != nullptr)
	{
		n3->parent = n1;
	}
	n1->lchild = n3;
}

//�������ں�ڵ�node(�����Ϳɫ)���ƻ���ƽ��,node��������root
void RBT::Balance(Node* node)
{
	if (node->parent->color == Black)
	{
		//���1�����ڵ�Ϊ��ɫ
		//do nothing
	}
	else
	{
		//���ڵ�죬��ʱһ������ү�ڵ�
		Node* parent = node->parent;
		Node* grand = parent->parent;
		Node* uncle = (grand->lchild == parent) ? grand->rchild : grand->lchild;
		if (uncle != nullptr && uncle->color == Red)
		{
			//���2�����ڵ����ڵ㶼Ϊ��ɫ
			parent->InvertColor();
			grand->InvertColor();
			if (uncle != nullptr)
				uncle->InvertColor();
			if (grand == root)
				grand->InvertColor();
			else
				Balance(grand);//�ݹ�
		}
		else
		{
			//���3�����ڵ�죬��ڵ��
			//������ϸ������ 1��ү���ӹ��� 2��ү���Ӳ�����
			//�ַ���ߺ��ұ߹� 2x2=4��
			if (grand->lchild == parent)
			{
				//�������
				if (parent->lchild == node)
				{
					//����
					parent->InvertColor();
					grand->InvertColor();
					RightRotate(grand);
				}
				else
				{
					//������
					LeftRotate(parent);
					node->InvertColor();
					grand->InvertColor();
					RightRotate(grand);
				}
			}
			else
			{
				//�����ұ�
				if (parent->rchild == node)
				{
					//����
					parent->InvertColor();
					grand->InvertColor();
					LeftRotate(grand);
				}
				else
				{
					//������
					RightRotate(parent);
					node->InvertColor();
					grand->InvertColor();
					LeftRotate(grand);
				}
			}
		}
	}
}

//��������node������������ɫ��������ͬ��ɵĲ�ƽ��
//leftLack==true��ʾ������ȱһ��ڣ�ȱʧ��ĺ���һ���Ǻڽڵ�
//node��������nullptr
void RBT::Adjust(Node* node, bool leftLack)
{
	//���ȸ�ȱ�ಹ��һ��ڽڵ㣬����ɹ���ƽ��ɹ�
	//��������ٿ��Ǹ�����ȥ��һ��ڣ�ʹ������ƽ�⣬����ʱ���þֲ���������һ�㣬����Ҫ����һ��ݹ����
	//ע�����ϲ����У�����þֲ����ĸ�ԭ���Ǻڵģ������վֲ���Ҳֻ���Ǻڵ�
	//�������Է�ֹͿ�쵼����ֲ������ϲ��ͻ���������죩�������޷������ݹ飨��Ϊ�ú���Ҫ��ȱʧ��ĺ���һ���Ǻڽڵ㣩

	if (leftLack == true)
	{
		Node* n0 = node;
		Node* n1 = node->lchild;//ȱ��
		Node* n2 = node->rchild;//����
		Node* n3 = n2->rchild;//����Զ����ڵ�
		Node* n4 = n2->lchild;//���������ڵ�

		//���1�����ຢ��Ϊ��ڵ�
		//����˼·��������ת�������ڵ��һ������ת��ȱ�࣬��ʱ�ֻ����ȱ���ڲ���ƽ�⣬��Ҫ�ݹ�
		if (n2->color == Color::Red)
		{
			LeftRotate(n0);
			n0->InvertColor();
			n2->InvertColor();
			Adjust(n0, true);
		}
		//���2��3�����ຢ��Ϊ�ڽڵ㣬���������ӽڵ��Ϊ�ڽڵ�
		else if (n3->color == Color::Black && n4->color == Color::Black)
		{
			//���2���ֲ���Ϊ��ڵ�
			//ֱ�Ӹ�ɫ����ƽ��
			if (n0->color == Color::Red)
			{
				n0->InvertColor();
				n2->InvertColor();
			}
			//���3���ֲ���Ϊ�ڽڵ�
			//ֱ�Ӹ�ɫ�ɾֲ�ƽ�⣬��������һ���ɫ����ݹ�
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
		//���4��5�����ຢ��Ϊ�ڽڵ㣬���������ӽڵ㲻ȫΪ�ڽڵ�
		else
		{
			//���4��Զ����ڵ�Ϊ��ڵ�
			//ͨ����ת����ȱ��һ��ڣ���ά�־ֲ�����ɫ���䣬�����ٵ�һ�����Զ����ڵ��ڲ�����
			//������ƽ��
			if (n3->color = Color::Red)
			{
				LeftRotate(n0);
				RBT::Node::ExchangeColor(n0, n2);
				n3->InvertColor();
			}
			//���5��Զ����ڵ�Ϊ�ڽڵ�
			//ͨ����ת������4
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
		Node* n1 = node->rchild;//ȱ��
		Node* n2 = node->lchild;//����
		Node* n3 = n2->lchild;//����Զ����ڵ�
		Node* n4 = n2->rchild;//���������ڵ�

		//���1�����ຢ��Ϊ��ڵ�
		//����˼·��������ת�������ڵ��һ������ת��ȱ�࣬��ʱ�ֻ����ȱ���ڲ���ƽ�⣬��Ҫ�ݹ�
		if (n2->color == Color::Red)
		{
			RightRotate(n0);
			n0->InvertColor();
			n2->InvertColor();
			Adjust(n0, false);
		}
		//���2��3�����ຢ��Ϊ�ڽڵ㣬���������ӽڵ��Ϊ�ڽڵ�
		else if (n3->color == Color::Black && n4->color == Color::Black)
		{
			//���2���ֲ���Ϊ��ڵ�
			//ֱ�Ӹ�ɫ����ƽ��
			if (n0->color == Color::Red)
			{
				n0->InvertColor();
				n2->InvertColor();
			}
			//���3���ֲ���Ϊ�ڽڵ�
			//ֱ�Ӹ�ɫ�ɾֲ�ƽ�⣬��������һ���ɫ����ݹ�
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
		//���4��5�����ຢ��Ϊ�ڽڵ㣬���������ӽڵ㲻ȫΪ�ڽڵ�
		else
		{
			//���4��Զ����ڵ�Ϊ��ڵ�
			//ͨ����ת����ȱ��һ��ڣ���ά�־ֲ�����ɫ���䣬�����ٵ�һ�����Զ����ڵ��ڲ�����
			//������ƽ��
			if (n3->color = Color::Red)
			{
				RightRotate(n0);
				RBT::Node::ExchangeColor(n0, n2);
				n3->InvertColor();
			}
			//���5��Զ����ڵ�Ϊ�ڽڵ�
			//ͨ����ת������4
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
		//���������ӣ�����ֱ��ɾ����Ӧ�����������������ڵ㽻��
		//����ֻ�Ǽ򵥽�����ֵ������ڵ�������ݽϴ������ͨ��ָ��������֯�ķ�ʽ����������ݿ���
		Node* n = node->lchild;
		while (n->rchild != nullptr)
			n = n->rchild;
		node->element = n->element;
		Delete(n);
		return;
	}

	//����ֱ��ɾ������������
	//��һ���ࣺɾ����ڵ㣬��ɾ���ڽڵ㣬�����к�ɫ�ӽڵ㣬��Ϊ��

	//ע�⣬child����Ϊnullptr
	Node* child = (node->lchild == nullptr) ? node->rchild : node->lchild;
	if (node->color == Color::Red)
	{
		//ɾ�����Ǻ�ڵ�
		//�����ƻ�ƽ�⣬ֱ�ӽ���
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
		//ɾ�����Ǻڽڵ㣬�������ӽڵ��Ǻ��
		//�ú�ڵ��ڲ���һ���ڽڵ㣬����ƽ��
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

	//�ڶ����ࣺɾ���ڽڵ㣬�����ӽڵ�Ҳ�Ǻ�ɫ�ģ����������Ϊ���ӣ���Ҫ�ݹ�
	//ע���ӽڵ����Ϊnullptr
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