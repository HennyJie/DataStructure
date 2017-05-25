#include "String.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//判断数组元素是否为字符型
bool String::IsChar(char c)
{
	if ((c >= 'A'&&c <= 'Z') || (c >= 'a'&&c <= 'z'))
	{
		return true;
	}
	else
		return false;
}

//构造自定义的String类
String::String(string para)
{
	int i;
	maxSize = para.length();
	ch = new char[maxSize + 1];
	if (!ch)
	{
		cout << "Allocation error!" << endl;
		exit(1);
	}
	length = para.length();
	for (i = 0; i < para.length()+1; i++)
	{
		ch[i] = para[i];
	}
}

//计算next(j)的算法
void String::SetNext()
{
	int j = 0, k = -1, lengthP = length;
	next[0] = -1;
	while (j < lengthP)
	{
		if (k == -1 || ch[j] == ch[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else k = next[k];
	}
}

//朴素模式匹配BF算法，在段落中检索关键字key出现的次数
int String::BF_Find(String& key)
{
	int i, j, count=0;
	for (i = 0; i < length - key.GetLength(); i++)//段落长度
	{
		int flag = 0;
		for (j = 0; j < key.GetLength(); j++)//key长度
		{
			if (ch[i + j] != key.ch[j])//如出现不相符则标志为“1”
			{
				flag = 1;
				break;
			}
		}
		//若连续key.GetLength()位一直相等，则计数器加一，同时i向后移动j位
		if ( !flag && j == key.GetLength() && IsChar(ch[i+j])==false )
		{
				count++;
				i += j;
		}
	}
	return count;//返回出现次数
}

//改进模式匹配KMP算法，在段落中检索关键字key出现的次数
int String::KMP_Find(String& key,int next[])
{
	int posP = 0, posT = 0;//两个串的扫描指针
	int count = 0;//计数
	int lengthT = length;//模式与目标串的长度
	int lengthP = key.GetLength();
	while (posT < lengthT - lengthP)
	{
		while (posP < lengthP && posT < lengthT)//对两串扫描
		{
			if (posP == -1 || key.ch[posP] == ch[posT])//对应字符匹配
			{
				posP++;
				posT++;
			}
			else posP = next[posP];
		}
		if (posP >= lengthP && IsChar(ch[posT]) == false)//匹配成功
			count++;
		posP = 0;//模式指针回到起点
	}
	return count;
}

//重载输入运算符，输入自定义的字符串类
istream& operator >> (istream &is, String &str)
{
	char temp[10000];
	is >> temp;
	str.SetLength (strlen(temp));
	str.ch = new char[str.GetLength() + 1];
	strcpy(str.ch, temp);
	return is;
}

//重载输出运算符<<,输出自定义的字符串类
ostream& operator <<(ostream &os, String &str)
{
	os << str.ch;
	return os;
}


int main()
{
	char fname[100];
	char temp[100];
	int result,wordSize;
	string paragraph,key;
	int choice;
	cout << "关键字检索系统：\n" << endl;
	cout << "请输入文件名：";
	cin >> fname;
	cout << "请输入一段英文：" << endl;
	
	ofstream outfile(fname);//输出流
	ifstream infile(fname);//输入流
	getchar();
	getline(cin, paragraph);//读入检索段落
	outfile << paragraph;//输出到以fname命名的文件中
	outfile.close();
	String passage(paragraph);//构造自定义的字符串类

	cout << "\n本段文本已保存在文件\"" << fname << "\"中!" << endl;
	cout << "\n请输入要查找的关键字：";
	cin >> key;
	String keyWord(key);//构造自定义的字符串类

	cout << "\n请选择字符串匹配的算法(1代表朴素模式匹配B-F算法，2代表改进模式匹配KMP算法）：";//两种算法实现模式匹配操作
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "\n显示源文件\"" << fname << "\" :" << endl;
		cout << paragraph;
		result = passage.BF_Find(keyWord);//调用朴素模式匹配BF算法
		break;

	case 2:
		cout << "\n显示源文件\"" << fname << "\" :" << endl;
		cout << paragraph;
		passage.SetNext();//计算next(j)
		result = passage.KMP_Find(keyWord,passage.GetNext());//调用改进模式匹配KMP算法
		break;

	default:
		break;
	}
	cout << "\n"<<endl;
	cout << "在源文件中共找到" << result << "个" << "\"" << key << "\"" << endl;

	getchar();
	getchar();
	return 0;
}