#ifndef __BIGINT
#define __BIGINT

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
 
 
class INT
{
	public:
 
	INT();
	template <class T>
	INT(T a);
	INT(const string & s);
	INT(const  INT &a);
	INT(const char * s);
 
	template <class T>
	INT & operator=(const T obj);
	INT & operator=(const INT & obj);
 
	friend istream & operator>>(istream & in , INT &a);
	friend ostream & operator<<(ostream & out , INT &a);
 
	operator bool();
 
	friend INT operator+(INT a,INT b);
	friend INT operator-(INT a,INT b);
	friend INT operator*(INT a,INT b);
	friend INT operator/(INT a,INT b);
	friend INT operator%(INT a,INT b);
	template <class T1>
	friend INT operator+(T1 a,INT b);
	template <class T1>
	friend INT operator-(T1 a,INT b);
	template <class T1>
	friend INT operator*(T1 a,INT b);
	template <class T1>
	friend INT operator/(T1 a,INT b);
	template <class T1>
	friend INT operator%(T1 a,INT b);
	template <class T2>
	friend INT operator+(INT a,T2 b);
	template <class T2>
	friend INT operator-(INT a,T2 b);
	template <class T2>
	friend INT operator*(INT a,T2 b);
	template <class T2>
	friend INT operator/(INT a,T2 b);
	template <class T2>
	friend INT operator%(INT a,T2 b);
 
	friend bool operator<(INT a,INT b);
	friend bool operator>(INT a,INT b);
	friend bool operator<=(INT a,INT b);
	friend bool operator>=(INT a,INT b);
	friend bool operator!=(INT a,INT b);
	friend bool operator==(INT a,INT b);
 
	template <class T>
	inline INT& operator+=(T b);
	template <class T>
	inline INT& operator-=(T b);
	template <class T>
	inline INT& operator*=(T b);
	template <class T>
	inline INT& operator/=(T b);
	template <class T>
	inline INT& operator%=(T b);
 
	inline INT& operator++();
	inline INT& operator--();
	inline INT operator++(int);
	inline INT operator--(int);
	inline INT operator-();
 
	private:
 
	vector<int> data;
	bool sign;
	static const long long int BIT=100000000;
	static const short int BITb=8;
 
	void print();
	void clear();//去除多余的前导0
};
INT Null(0);
INT::INT(const  INT &a)
{
	data=a.data;
	sign=a.sign;
}
INT::INT()
{
	data.resize(1);
	sign=1;
}
INT::INT(const string & s)
{
	int p=0,no=0;
	data.resize(1);
	sign=1;
	for(int i=s.length()-1;i>=0;i--)
	{
		if(s[i]=='-')
		{
			sign=0;
			continue;
		}
		no++;
		int t=(s[i]-'0');
		for(int j=1;j<no;j++)t*=10;
		data[p]+=t;
		if(no>=BITb)
		{
			data.push_back(0);
			p++;
			no=0;
		}
	}
	clear();
}
INT::INT(const  char * s)
{
	int p=0,no=0;
	data.resize(1);
	sign=1;
	for(int i=strlen(s)-1;i>=0;i--)
	{
		if(s[i]=='-')
		{
			sign=0;
			continue;
		}
		no++;
		int t=(s[i]-'0');
		for(int j=1;j<no;j++)t*=10;
		data[p]+=t;
		if(no>=BITb)
		{
			data.push_back(0);
			p++;
			no=0;
		}
	}
	clear();
}
template <class T>
INT::INT(T a)
{
	if(a<0)
	{
		sign=0;
		a=-a;
	}
	else sign=1;
	for(short int p=0;a>0;p++)
	{
		data.push_back(0);
		data[p]=a%BIT;
		a/=BIT;
	}
	clear();
}
 
ostream & operator<<(ostream & out , INT &a)
{
	a.print();
	return out;
}
 
istream & operator>>(istream & in , INT &a)
{
	string s;
	cin>>s;
	a=s;
	return in;
}
INT & INT::operator=(const INT & obj)
{
	if(this !=&obj)
	{
		data=obj.data;
		sign=obj.sign;
	} 
	return *this;
}
 
template <class T>
INT & INT::operator=(const T obj)
{
	*this=INT(obj);
	return *this;
}
 
INT operator+(INT a,INT b)
{
	if(a.sign==0&&b.sign==0)
	{
		a.sign=b.sign=1;
		INT t=a+b;
		t.sign=0;
		return t;
	}
	if(a.sign==1&&b.sign==0)
	{
		b.sign=1;
		return a-b;
	}
	if(a.sign==0&&b.sign==1)
	{
		a.sign=1;
		return b-a;
	}
	INT ans;
	if(a.data.size()<b.data.size())return (b+a);
	for(int i=0;i<b.data.size();i++)
	{
		ans.data.push_back(0);
		ans.data[i]+=(a.data[i]+b.data[i])%INT::BIT;
		ans.data[i+1]+=(a.data[i]+b.data[i])/INT::BIT;
	}
	for(int i=b.data.size();i<a.data.size();i++)
	{
		ans.data.push_back(0);
		ans.data[i]+=a.data[i];
	}
	ans.clear();
	return ans;
}
INT operator-(INT a,INT b)
{
	if(a.sign==1&&b.sign==0)
	{
		b.sign=1;
		return a+b;
	}
	if(a.sign==0&&b.sign==1)
	{
		a.sign=1;
		INT t=a+b;
		t.sign=0;
		return t;
	}
	if(a.sign==0&&b.sign==0)
	{
		a.sign=b.sign=1;
		return b-a;
	}
	if(a<b)
	{
		INT t=b-a;
		t.sign=0;
		return t;
	}
	INT ans;
	if(a==b)return ans;
	for(int i=1;i<a.data.size();i++)ans.data.push_back(0);
	for(int i=0;i<a.data.size();i++)
	{
		ans.data[i]+=a.data[i]-b.data[i];
		if(ans.data[i]<0)
		{
			ans.data[i]+=INT::BIT;
			a.data[i+1]--;
		}
	}
	ans.clear();
	return ans;
}
INT operator*(INT a,INT b)
{
	if(a.sign==1&&b.sign==0)
	{
		b.sign=1;
		INT t=a*b;
		t.sign=0;
		return t;
	}
	if(a.sign==0&&b.sign==1)
	{
		a.sign=1;
		INT t=a*b;
		t.sign=0;
		return t;
	}
	if(a.sign==0&&b.sign==0)
	{
		a.sign=b.sign=1;
		return a*b;
	}
	INT ans;
	if(a==INT(0)||b==INT(0))return ans;
	for(int i=1;i<=a.data.size()+b.data.size();i++)ans.data.push_back(0);
	for(int i=0;i<a.data.size();i++)
	{
		for(int j=0;j<b.data.size();j++)
		{
			long long t=(long long)a.data[i]*b.data[j];
			ans.data[i+j]+=t%INT::BIT;
			ans.data[i+j+1]+=t/INT::BIT;
		}
	}
	ans.clear();
	return ans;
}
//能跑，但是有极大优化空间，但是懒得优化了，有空再说
INT operator/(INT a,INT b)
{
	if(a.sign==0&&b.sign==0)
	{
		a.sign=b.sign=1;
		return a/b;
	}
	if(a.sign==0&&b.sign==1)
	{
		a.sign=1;
		INT t=a/b;
		t.sign=0;
		return t;
	}
	if(a.sign==1&&b.sign==0)
	{
		b.sign=1;
		INT t=a/b;
		t.sign=0;
		return t;
	}
	INT ans;
	while(a-b>Null)
	{
		a=a-b;
		ans++;
	}
	return ans;
}
 
INT operator%(INT a,INT b)
{
	if(a.sign==0||b.sign==0)
	{
		cout<<"error,未定义负数的求模运算"<<endl;
		return INT(-1);
	}
	else
	{
		while(a-b>Null)
			a=a-b;
		return a;
	}
}
template <class T1>
INT operator+(T1 a,INT b)
{
	INT A(a);
	return A+b;
}
template <class T1>
INT operator-(T1 a,INT b)
{
	INT A(a);
	return A-b;
}
template <class T1>
INT operator*(T1 a,INT b)
{
	INT A(a);
	return A*b;
}
template <class T1>
INT operator/(T1 a,INT b)
{
	INT A(a);
	return A/b;
}
template <class T1>
INT operator%(T1 a,INT b)
{
	INT A(a);
	return A%b;
}
template <class T2>
INT operator+(INT a,T2 b)
{
	INT B(b);
	return a+B;
}
template <class T2>
INT operator-(INT a,T2 b)
{
	INT B(b);
	return a-B;
}
template <class T2>
INT operator*(INT a,T2 b)
{
	INT B(b);
	return a*B;
}
template <class T2>
INT operator/(INT a,T2 b)
{
	INT B(b);
	return a/B;
}
template <class T2>
INT operator%(INT a,T2 b)
{
	INT  B(b);
	return a%B;
}
 
bool operator<(INT a,INT b)
{
	if(a.sign==1&&b.sign==0)return false;
	if(a.sign==0&&b.sign==1)return true;
	if(a.sign==0&&b.sign==0)
	{
		a.sign=b.sign=1;
		return b<a;
	}
	if(a.data.size()>b.data.size())return false;
	else if(a.data.size()<b.data.size())return true;
	if(a.data.size()==1&&a.data[0]==b.data[0]&&a.data[0]==0)return false;
	for(int i=a.data.size()-1;i>=0;i--)
	{
		if(a.data[i]<b.data[i])return true;
		if(a.data[i]>b.data[i])return false;
	}
	return false;
}
bool operator==(INT a,INT b)
{
	if(a.sign!=b.sign)
	{
		if(a.data[0]==b.data[0]&&a.data[0]==0&&a.data.size()==b.data.size()&&a.data.size()==1)
			return 1;
		else
			return 0;
	}
	if(a.data.size()!=b.data.size())return 0;
	for(int i=0;i<a.data.size();i++)
		if(a.data[i]!=b.data[i])
			return 0;
	return 1;
}
bool operator!=(INT a,INT b)
{
	return !(a==b);
}
bool operator>(INT a,INT b)
{
	return a>=b&&a!=b;
}
bool operator<=(INT a,INT b)
{
	return (a<b||a==b);
}
bool operator>=(INT a,INT b)
{
	return !(a<b);
}
 
template <class T>
inline INT& INT::operator+=(T b)
{
	*this=*this+INT(b);
	return *this;
}
template <class T>
inline INT& INT::operator-=(T b)
{
	*this=*this-INT(b);
	return *this;
}
template <class T>
inline INT& INT::operator*=(T b)
{
	*this=*this*INT(b);
	return *this;
}
template <class T>
inline INT& INT::operator/=(T b)
{
	*this=*this/INT(b);
	return *this;
}
template <class T>
inline INT& INT::operator%=(T b)
{
	*this=*this%INT(b);
	return *this;
}
 
 
 
inline INT& INT::operator++()
{
	*this=*this+INT(1);
	return *this;
}
inline INT& INT::operator--()
{
	*this=*this-INT(1);
	return *this;
}
inline INT INT::operator++(int)
{
	INT t= *this;
	*this=*this+INT(1);
	return t;
}
inline INT INT::operator--(int)
{
	INT t=*this;
	*this=*this+INT(1);
	return t;
}
 
void INT::print()
{
	if(data.size()==1&&data[0]==0||data.size()==0)
	{
		cout<<0;
		return;
	}
	if(sign==0)cout<<'-';
	clear();
	cout<<data.back();
	for(int i=data.size()-2;i>=0;i--)
	{
		if(data[i]==0)for(int i=1;i< BIT ;i*=10)cout<<'0';
		else
		{
			int x=0;
			for(int t=data[i];t>0;t/=10)x++;
			for(int i=1;i<=8-x;i++)cout<<'0';
			cout<<data[i];
		}
	}
}
void INT::clear()
{
	while(data.size()>1&&data.back()==0)
		data.pop_back();
}
INT::operator bool()
{
	
	if(data.size()==1&&data[0]==0||data.size()==0)
		return false;	
	else
		return true;
}
inline INT INT::operator-()
{
	INT newthis(*this);
	if(newthis.sign==0)newthis.sign=1;
	else newthis.sign=0;
	return newthis;
}

#endif