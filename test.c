#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
//动态内存管理与释放(malloc,calloc,realloc,free)
//1. void* malloc (size_t size);(向系统申请空间) 
//int main()
//{
//	int *p =(int*) malloc(40);//向系统申请40个字节的空间
//	int i = 0;
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));//如果开辟失败 返回错误信息
//	}
//	else
//	{
//		for (i = 0; i < 10; i++)
//		{
//			*(p + i) = i;//调试可知 malloc申请空间但不初始化空间
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", *(p + i));
//		}
//	}
//	free(p);//释放p的空间  避免空间的浪费
//	p = NULL;
//	return 0;
//}————————————————————————————————————
//void* calloc (size_t num, size_t size);
//int main()
//{
//	int *p = (int) calloc(10, sizeof(int));
//	int i = 0;
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));//如果开辟失败 返回错误信息
//	}
//	else
//	{
//		for (i = 0; i < 10; i++)
//		{
//			*(p + i) = i;//调试可知 calloc申请空间且初始化空间为0
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", *(p + i));
//		}
//	}
//	free(p);//释放p的空间  避免空间的浪费
//	p = NULL;//将指针化为0
//	return 0;
//}
//总结：malloc和calloc的区别与联系
//联系：1.malloc与calloc都可以开辟空间并且返回开辟空间的首地址 2.都与free联用
//区别：1.申请方式不同（malloc直接申请字节，calloc看上面的定义）2.calloc申请字节并且将申请的空间初始化为0，
//malloc不将空间初始化 因为malloc不用初始化 所以申请速度更快
//——————————————————————————————————————————
//void* realloc (void* ptr, size_t size); //拓展字节（前期申请的字节数不够）
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
//	//realloc(p, 100);//将P拓展到100个字节 若p后还有60个字节，则直接向后开辟空间，若p后不足60个空间，则会另找一块足够大的空间，并将首元素地址赋给p
//	//但若找不到如此大的空间 则返回NULL，导致p丢失 所以一般不这么用(注：realloc也不初始化空间的值)
//	//示范
//	int *p1 ;
//	p1 = realloc(p, 100);//如果p为空指针 则realloc作用与malloc作用相同
//	if (p1 != NULL)
//	{
//		p = p1;
//	}
//	free(p);
//	p = NULL;
//	return 0;
//}————————————————————————————
//使用free的几点注意事项：
//1.不可释放非动态空间（如int a; 这种的 malloc的申请的是动态空间）
//2.不可只释放以开辟空间的一部分 如：
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
//			*p++ = i;//相当于p指针位置改变 而*(p+i)=i;这种模式P的位置没变 只是访问的位置发生改变
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", *(p - i-1));//9 8 7 6 5 4 3 2 1 0
//		}
//	}
//	free(p);//直接挂掉 因为p的
//	p = NULL;
//	return 0;
//}
//char* getmemory()
//{
//	/*static*/ char p[] = "hello world";//加一个static就行了
//	return p;//变量存放在栈区
//}
//void test()
//{
//	char* str = NULL;
//	str = getmemory();//str虽然得到了p的地址，但p指向的空间还给了操作系统，其中的值也会被系统重置
//	printf(str);//还可以这样搞  答案是随机值
//}
//int main()
//{
//	test();
//	return 0;
//}
//小结：变量可以放在栈区，堆区，静态区 
//栈区：由系统自动分配与释放 用于存放局部变量，参数和返回值
//堆区：由malloc,calloc 等申请开辟的空间，使用完后须用free释放（防止内存泄漏） 并将指针置为空指针（避免产生野指针）
//静态区 用于存放static修饰的变量（包括全局静态变量和局部静态变量），和全局变量
//void getmemory(char* p)//p中接收到的是空指针 且p为局部变量 出了函数则被销毁
//{
//	p = (char*)malloc(40);
//}
//void test()
//{
//	char* arr = NULL;
//	getmemory(arr);//将arr的值传过去
//	strcpy(arr, "hallo world");//此时arr中仍为空指针
//	printf(arr);//程序崩溃
//}
//int main()
//{
//	test();
//	return 0;
//}
//改进1
//void getmemory(char** p)
//{
//	*p = (char*)malloc(40);//注：一定是*p而不是p
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
//改进2
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
//}————————————————————————————
//void test()
//{
//	char* p = NULL;
//	p = (char*)malloc(40);
//	free(p);
//	strcpy(p, "hello world");
//	printf(p);//虽然成功打印 但有问题 p为野指针 这样相当于非法访问
//}
//int main()
//{
//	test();
//	return 0;
//}————————————————————————-
//柔性数组（不常见，但可以了解）
//struct stu
//{
//	int a;
//	int arr[];
//};
//int main()
//{
//	//struct stu s;
//	//printf("%d\n", sizeof(s));//4 说明int arr[]不占空间
//	//给柔性数组申请空间
//	struct stu* p = (struct stu*)malloc(4 + 10 * sizeof(int));//给arr申请10个整形的空间
//	int i = 0;
//	if (p != NULL)
//	{
//		for (i = 0; i < 10; i++)
//		{
//			p->arr[i] = i;
//		}
//		for (i = 0; i < 10; i++)
//		{
//			printf("%d ", p->arr[i]);//0 1 2 3 4 5 6 7 8 9  可以使用
//		}
//	}
//  free(p);
//  p = NULL;
//	return 0;
//}
//如果第一次申请的空间不够还可以调整（realloc）
//使用柔性数组
//int main()
//{
//	struct stu* p = (struct stu*)malloc(4 + 5 * sizeof(int));
//	//如果不够
//	struct stu* p1 = realloc(p, 44);
//	if (p1 != NULL)
//	{
//		p = p1;//防止地址丢失
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
//			printf("%d ", p->arr[i]);//0 1 2 3 4 5 6 7 8 9 可以调整
//		}
//	}
//  free(p);
//  p = NULL;
//	return 0;
//}
//不适用柔性数组
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
//	//如果不够
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
//		这样也可以，但这样存在一个间接查找，速度较慢
//		*/
//	}
//	free(p->arr);
//	p->arr = NULL;//注意先释放p->arr，再释放p 因为先释放p会使p->arr找不到
//	free(p);
//	p = NULL;
//	return 0;
//}
