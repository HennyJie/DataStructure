//=====================================================自定义的字符串类===========================================================
#ifndef _STRING_H_
#define _STRING_H_

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

//自定义字符串类
class String
{
private:
	char *ch;//存储字符串的数组
	int next[2000];
	int length;//当前长度
	int maxSize;//最大长度
public:
	String(){}//默认构造函数
	String(string passage);//用读进来的字符串构造自定义的字符串类
	~String() { delete[]ch; }//析构函数
	void SetNext();//计算next(j)的算法
	int* GetNext() { return next; }//获取next数组
	char* GetString(){ return ch; }//取出字符串
	int GetLength() { return length; }//获得当前长度
	void SetLength(int len) { length = len; }//设置当前长度
	int BF_Find(String& key);//使用朴素模式匹配BF算法检索目标出现次数
	int KMP_Find(String& key,int next[]);//使用朴素模式匹配BF算法检索目标出现次数
	bool IsChar(char c);//判断是否为字符型
	friend istream& operator >> (istream &is, String &str);//重载输入运算符
	friend ostream& operator <<(ostream &os, String &str);//重载输出运算符
};
#endif

