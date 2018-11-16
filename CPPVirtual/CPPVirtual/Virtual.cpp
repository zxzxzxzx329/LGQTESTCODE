// #include <iostream> 
//#include <cstdlib> 
//using namespace std;  
//
//class Base 
//{ 
//public:     
//	virtual void f() 
//	{
//		cout << "Base::f" << endl;
//	}     
//	virtual void g() 
//	{
//		cout << "Base::g" << endl;
//	}     
//	virtual void h() 
//	{
//		cout << "Base::h" << endl;
//	} 
//};  
//
//class Drive : public Base 
//{ 
//public:     
//	void f() 
//	{
//		cout << "Drived::f" << endl;
//	}     
//	virtual void f1() 
//	{
//		cout << "Drived::f1" << endl;
//	}     
//	virtual void g1() 
//	{
//		cout << "Drived::g1" << endl;
//	}     
//	virtual void h1() 
//	{
//		cout << "Drived::h1" << endl;
//	} 
//};  
//
//int main(void) 
//{     
//	typedef void (*Fun)(void);     
//	Base b;     
//	Fun pFun = NULL;      
//	cout << "虚函数表指针的地址：" << &b << endl;     
//	cout << "虚函数表的地址：" << *(int *)&b << endl;     
//	cout << "虚函数表中第一个函数的地址：" << *(int *)(*(int *)&b) << endl;      
//	pFun = (Fun)(*(int *)(*(int *)&b));      
//	pFun();     
//	pFun = (Fun)(*(int *)((*(int *)&b)+4));      
//	pFun();     
//	pFun = (Fun)(*(int *)((*(int *)&b)+8));      
//	pFun();      
//	cout << endl << "多态情况下：" << endl;  
//
//	Base *b2;
//	b2 = new Drive();      
//	pFun = (Fun)(*(int *)(*(int *)b2));      
//	pFun();     
//	pFun = (Fun)(*(int *)((*(int *)b2)+4));      
//	pFun();     
//	pFun = (Fun)(*(int *)((*(int *)b2)+8));      
//	pFun();     
//	pFun = (Fun)(*(int *)((*(int *)b2)+12));      
//	pFun();     
//	pFun = (Fun)(*(int *)((*(int *)b2)+16));      
//	pFun();     
//	pFun = (Fun)(*(int *)((*(int *)b2)+20));      
//	pFun();      
//	system("pause");     
//	return 0; 
//} 



#include <iostream>
using namespace std;

class Base1 {
public:
	virtual void f() { cout << "Base1::f" << endl; }
	virtual void g() { cout << "Base1::g" << endl; }
	virtual void h() { cout << "Base1::h" << endl; }

};

class Base2 {
public:
	virtual void f() { cout << "Base2::f" << endl; }
	virtual void g() { cout << "Base2::g" << endl; }
	virtual void h() { cout << "Base2::h" << endl; }
};

class Base3 {
public:
	virtual void f() { cout << "Base3::f" << endl; }
	virtual void g() { cout << "Base3::g" << endl; }
	virtual void h() { cout << "Base3::h" << endl; }
};


class Derive : public Base1, public Base2, public Base3 {
public:
	virtual void f() { cout << "Derive::f" << endl; }
	virtual void g1() { cout << "Derive::g1" << endl; }
};


typedef void(*Fun)(void);

int main()
{
	Fun pFun = NULL;

	Derive d;
	int** pVtab = (int**)&d;

	//Base1's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);
	pFun = (Fun)pVtab[0][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+1);
	pFun = (Fun)pVtab[0][1];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);
	pFun = (Fun)pVtab[0][2];
	pFun();

	//Derive's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);
	pFun = (Fun)pVtab[0][3];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[0][4];
	cout<<pFun<<endl;


	//Base2's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
	pFun = (Fun)pVtab[1][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
	pFun = (Fun)pVtab[1][1];
	pFun();

	pFun = (Fun)pVtab[1][2];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[1][3];
	cout<<pFun<<endl;



	//Base3's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
	pFun = (Fun)pVtab[2][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
	pFun = (Fun)pVtab[2][1];
	pFun();

	pFun = (Fun)pVtab[2][2];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[2][3];
	cout<<pFun<<endl;

	system("pause");

	return 0;
}