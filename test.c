#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
//��̬�ڴ�������ͷ�(malloc,calloc,realloc,free)
//1. void* malloc (size_t size);(��ϵͳ����ռ�) 
//int main()
//{
//	int *p =(int*) malloc(40);//��ϵͳ����40���ֽڵĿռ�
//	int i = 0;
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));//�������ʧ�� ���ش�����Ϣ
//	}
//	else
//	{
//		for (i = 0; i < 10; i++)
//		{
//			*(p + i) = i;//���Կ�֪ malloc����ռ䵫����ʼ���ռ�
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", *(p + i));
//		}
//	}
//	free(p);//�ͷ�p�Ŀռ�  ����ռ���˷�
//	p = NULL;
//	return 0;
//}������������������������������������������������������������������������
//void* calloc (size_t num, size_t size);
//int main()
//{
//	int *p = (int) calloc(10, sizeof(int));
//	int i = 0;
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));//�������ʧ�� ���ش�����Ϣ
//	}
//	else
//	{
//		for (i = 0; i < 10; i++)
//		{
//			*(p + i) = i;//���Կ�֪ calloc����ռ��ҳ�ʼ���ռ�Ϊ0
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", *(p + i));
//		}
//	}
//	free(p);//�ͷ�p�Ŀռ�  ����ռ���˷�
//	p = NULL;//��ָ�뻯Ϊ0
//	return 0;
//}
//�ܽ᣺malloc��calloc����������ϵ
//��ϵ��1.malloc��calloc�����Կ��ٿռ䲢�ҷ��ؿ��ٿռ���׵�ַ 2.����free����
//����1.���뷽ʽ��ͬ��mallocֱ�������ֽڣ�calloc������Ķ��壩2.calloc�����ֽڲ��ҽ�����Ŀռ��ʼ��Ϊ0��
//malloc�����ռ��ʼ�� ��Ϊmalloc���ó�ʼ�� ���������ٶȸ���
//������������������������������������������������������������������������������������
//void* realloc (void* ptr, size_t size); //��չ�ֽڣ�ǰ��������ֽ���������
//int main()
//{
//	int i = 0;
//	int *p = (int*)calloc(10,sizeof(int));
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));
//	}
//	else
//	{
//		for (i = 0; i < 10; i++)
//		{
//			*(p + i) = i;
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", *(p + i));
//		}
//	}
//	//realloc(p, 100);//��P��չ��100���ֽ� ��p����60���ֽڣ���ֱ����󿪱ٿռ䣬��p����60���ռ䣬�������һ���㹻��Ŀռ䣬������Ԫ�ص�ַ����p
//	//�����Ҳ�����˴�Ŀռ� �򷵻�NULL������p��ʧ ����һ�㲻��ô��(ע��reallocҲ����ʼ���ռ��ֵ)
//	//ʾ��
//	int *p1 ;
//	p1 = realloc(p, 100);//���pΪ��ָ�� ��realloc������malloc������ͬ
//	if (p1 != NULL)
//	{
//		p = p1;
//	}
//	free(p);
//	p = NULL;
//	return 0;
//}��������������������������������������������������������
//ʹ��free�ļ���ע�����
//1.�����ͷŷǶ�̬�ռ䣨��int a; ���ֵ� malloc��������Ƕ�̬�ռ䣩
//2.����ֻ�ͷ��Կ��ٿռ��һ���� �磺
//int main()
//{
//	int *p = malloc(40);
//	int i = 0;
//	if (p == NULL)
//	{
//		return 0;
//	}
//	else
//	{
//		for (i = 0; i < 10; i++)
//		{
//			*p++ = i;//�൱��pָ��λ�øı� ��*(p+i)=i;����ģʽP��λ��û�� ֻ�Ƿ��ʵ�λ�÷����ı�
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", *(p - i-1));//9 8 7 6 5 4 3 2 1 0
//		}
//	}
//	free(p);//ֱ�ӹҵ� ��Ϊp��
//	p = NULL;
//	return 0;
//}
//char* getmemory()
//{
//	/*static*/ char p[] = "hello world";//��һ��static������
//	return p;//���������ջ��
//}
//void test()
//{
//	char* str = NULL;
//	str = getmemory();//str��Ȼ�õ���p�ĵ�ַ����pָ��Ŀռ仹���˲���ϵͳ�����е�ֵҲ�ᱻϵͳ����
//	printf(str);//������������  �������ֵ
//}
//int main()
//{
//	test();
//	return 0;
//}
//С�᣺�������Է���ջ������������̬�� 
//ջ������ϵͳ�Զ��������ͷ� ���ڴ�žֲ������������ͷ���ֵ
//��������malloc,calloc �����뿪�ٵĿռ䣬ʹ���������free�ͷţ���ֹ�ڴ�й©�� ����ָ����Ϊ��ָ�루�������Ұָ�룩
//��̬�� ���ڴ��static���εı���������ȫ�־�̬�����;ֲ���̬����������ȫ�ֱ���
//void getmemory(char* p)//p�н��յ����ǿ�ָ�� ��pΪ�ֲ����� ���˺���������
//{
//	p = (char*)malloc(40);
//}
//void test()
//{
//	char* arr = NULL;
//	getmemory(arr);//��arr��ֵ����ȥ
//	strcpy(arr, "hallo world");//��ʱarr����Ϊ��ָ��
//	printf(arr);//�������
//}
//int main()
//{
//	test();
//	return 0;
//}
//�Ľ�1
//void getmemory(char** p)
//{
//	*p = (char*)malloc(40);//ע��һ����*p������p
//}
//void test()
//{
//	char* p = NULL;
//	getmemory(&p);
//	strcpy(p, "hello world");
//	printf(p);
//}
//int main()
//{
//	test();
//	return 0;
//}
//�Ľ�2
//char* getmemory()
//{
//	char* p;
//	p = (char*)malloc(40);
//	return p;
//}
//void test()
//{
//	char* p = NULL;
//	p = getmemory();
//	strcpy(p, "hello world");
//	printf(p);
//  free(p)
//  p=NULL;
//}
//int main()
//{
//	test();
//	return 0;
//}��������������������������������������������������������
//void test()
//{
//	char* p = NULL;
//	p = (char*)malloc(40);
//	free(p);
//	strcpy(p, "hello world");
//	printf(p);//��Ȼ�ɹ���ӡ �������� pΪҰָ�� �����൱�ڷǷ�����
//}
//int main()
//{
//	test();
//	return 0;
//}������������������������������������������������-
//�������飨���������������˽⣩
//struct stu
//{
//	int a;
//	int arr[];
//};
//int main()
//{
//	//struct stu s;
//	//printf("%d\n", sizeof(s));//4 ˵��int arr[]��ռ�ռ�
//	//��������������ռ�
//	struct stu* p = (struct stu*)malloc(4 + 10 * sizeof(int));//��arr����10�����εĿռ�
//	int i = 0;
//	if (p != NULL)
//	{
//		for (i = 0; i < 10; i++)
//		{
//			p->arr[i] = i;
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", p->arr[i]);//0 1 2 3 4 5 6 7 8 9  ����ʹ��
//		}
//	}
//  free(p);
//  p = NULL;
//	return 0;
//}
//�����һ������Ŀռ䲻�������Ե�����realloc��
//ʹ����������
//int main()
//{
//	struct stu* p = (struct stu*)malloc(4 + 5 * sizeof(int));
//	//�������
//	struct stu* p1 = realloc(p, 44);
//	if (p1 != NULL)
//	{
//		p = p1;//��ֹ��ַ��ʧ
//	}
//	int i = 0;
//	if (p != NULL)
//	{
//		for (i = 0; i < 10; i++)
//		{
//			p->arr[i] = i;
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", p->arr[i]);//0 1 2 3 4 5 6 7 8 9 ���Ե���
//		}
//	}
//  free(p);
//  p = NULL;
//	return 0;
//}
//��������������
//struct stu
//{
//	int a;
//	int* arr;
//};
//int main()
//{
//	struct stu* p = (struct stu*)malloc(sizeof(struct stu));
//	p->arr = (int*)malloc(20);
//	int i = 0;
//	for (i = 0; i < 5; i++)
//	{
//		p->arr[i] = i;
//	}
//	//�������
//	int* p1 = realloc(p->arr, 40);
//	if (p1 != NULL)
//	{
//		p->arr = p1;
//	}
//	for (i = 5; i < 10; i++)
//	{
//		p->arr[i] = i;
//	}
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", p->arr[i]);//0 1 2 3 4 5 6 7 8 9
//		/*
//		����Ҳ���ԣ�����������һ����Ӳ��ң��ٶȽ���
//		*/
//	}
//	free(p->arr);
//	p->arr = NULL;//ע�����ͷ�p->arr�����ͷ�p ��Ϊ���ͷ�p��ʹp->arr�Ҳ���
//	free(p);
//	p = NULL;
//	return 0;
//}
