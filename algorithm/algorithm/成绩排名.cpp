#include <cstdio>
#include <malloc.h>
#include <vector>

struct Student
{
	int math;
	int algorithm;
	char name[11];//ԭʼ����
	char name_[10];//���������
};

int main()
{
	int n;
	scanf_s("%d", &n);
	
	Student* student = new Student[n];
	int* index = new int[n];//�������������򣬱���������ݿ���

	for (int i = 0;i < n;i++)
	{
		scanf_s("%d%d", &student[i].algorithm, &student[i].math);
		scanf_s("%s", student[i].name, 11);

		index[i] = i;
	}
	for (int i = 0;i < n;i++)//��nameԤ����
	{
		bool empty = false;
		for (int j = 0;j < 10;j++)
		{
			if (empty == true)
			{
				student[i].name_[j] = (char)96;
			}
			else
			{

				if (student[i].name[j] == '\0')
				{
					empty = true;
					student[i].name_[j] = (char)96;
				}
				else
				{
					student[i].name_[j] = student[i].name[j];
				}

			}
		}
	}
	
	{
		std::vector<int>* buckets = new std::vector<int>[27];//�ֱ��empty(96),a(97),b(98),....,z(122)
		for (int i = 9;i >= 0;i--)//��10����ĸѭ��
		{
			for (int j = 0;j < n;j++)//������ѧ��ѭ��,��Ͱ
			{
				buckets[(int)student[index[j]].name_[i] - 96].push_back(index[j]);
			}
			int basePos = 0;
			for (int j = 0;j < 27;j++)//������Ͱѭ��,��Ͱ
			{
				for (int k = 0;k < (int)buckets[j].size();k++)//��һ��Ͱ������Ԫ��ѭ��
				{
					index[basePos + k] = buckets[j][k];
				}
				basePos += buckets[j].size();
				buckets[j].clear();
			}
		}
		//delete[] buckets;
	}

	{
		std::vector<int>* buckets = new std::vector<int>[101];//�ֱ�洢0~100��

		int basePos = 0;
		//math
		for (int j = 0;j < n;j++)//������ѧ��ѭ��,��Ͱ
		{
			buckets[student[index[j]].math].push_back(index[j]);
		}
		for (int j = 100;j >= 0; j--)//������Ͱѭ��,��Ͱ
		{
			for (int k = 0;k < (int)buckets[j].size();k++)//��һ��Ͱ������Ԫ��ѭ��
			{
				index[basePos + k] = buckets[j][k];
			}
			basePos += buckets[j].size();
			buckets[j].clear();
		}
		//algorithm
		basePos = 0;
		for (int j = 0;j < n;j++)//������ѧ��ѭ��,��Ͱ
		{
			buckets[student[index[j]].algorithm].push_back(index[j]);
		}
		for (int j = 100;j >= 0; j--)//������Ͱѭ��,��Ͱ
		{
			for (int k = 0;k < (int)buckets[j].size();k++)//��һ��Ͱ������Ԫ��ѭ��
			{
				index[basePos + k] = buckets[j][k];
			}
			basePos += buckets[j].size();
			buckets[j].clear();
		}

		//delete[] buckets;
	}

	for (int i = 0;i < n;i++)
	{
		printf("%s\n",student[index[i]].name);
	}
}