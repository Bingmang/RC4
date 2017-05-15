#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <ctype.h>
using namespace std;

/*

变量说明
SBox为S表
KBox为K表
ZBox为密钥流
bitLength是每个字的长度
boxLength是盒子的大小

*/
class RC4 {

public:

	//RC4构造函数，bitLength默认为8，密钥字符串key必需提供
	RC4(string &key, const int & bitLength = 8) : Key(key), bitLength(bitLength), boxLength(1 << bitLength)
	{
		init_SBox(SBox, boxLength);			//初始化S盒
		init_KBox(KBox, boxLength, Key);	//初始化K盒
		KSA(SBox, KBox);					//KSA算法，打乱S盒
	}
	
	void RC4_en(string &input, string &output) {
		output.clear();						//清空输出字符串
		RC4_clear(ZBox);					//清空Z盒
		PRGA(SBox, ZBox, input.size());		//PRGA算法，生成Z盒
		RC4_en(input, output, ZBox);		//对字符串按位异或，输出结果在output中
	}
	void RC4_de(string &output, string &source) {
		source.clear();						//清空输出字符串
		RC4_de(output, source, ZBox);		//对字符串解密，输出结果在source中
	}
	void print_SBox() {
		print_SBox(SBox);
	}
	void print_KBox() {
		print_KBox(KBox);
	}
	void print_ZBox() {
		print_ZBox(ZBox);
	}

private:

	const int bitLength;
	const int boxLength;
	string Key;
	vector<int> SBox, KBox, ZBox;

	//重置Z盒，使类可以重复使用
	void RC4_clear(vector<int> &ZBox);

	//初始化S盒，S盒大小为2^bitLength，这里采用移位的方式计算
	void init_SBox(vector<int> &SBox, const int & boxLength);

	//初始化K盒，K盒大小为2^bitLength，这里采用位移的方式计算
	void init_KBox(vector<int> &KBox, const int & boxLength, string &Key);

	//KSA算法
	void KSA(vector<int> &SBox, vector<int> &KBox);

	//PRGA算法
	void PRGA(vector<int> &SBox, vector<int> &ZBox, const int & intputLength);

	//加密
	void RC4_en(string &input, string &output, vector<int> &ZBox);

	//解密
	void RC4_de(string &input, string &output, vector<int> &ZBox);

	//打印S盒
	void print_SBox(vector<int> & SBox);

	//打印K盒
	void print_KBox(vector<int> & KBox);

	//打印Z盒
	void print_ZBox(vector<int> & ZBox);

};

//重置Z盒，使类可以重复使用
void RC4::RC4_clear(vector<int> &ZBox) {
	ZBox.clear();
}

//初始化S盒，S盒大小为2^bitLength，这里采用移位的方式计算
void RC4::init_SBox(vector<int> &SBox, const int & boxLength) {
	for (int i = 0; i < boxLength; i++)
		SBox.push_back(i);
}

//初始化K盒，K盒大小为2^bitLength，这里采用位移的方式计算
void RC4::init_KBox(vector<int> &KBox, const int & boxLength, string &Key) {
	string::const_iterator Key_itr = Key.cbegin();
	string::const_iterator Key_itr_end = Key.cend();
	for (int i = 0; i < boxLength; i++) {
		if (isdigit(*Key_itr))
			KBox.push_back(*Key_itr - '0');
		else
			KBox.push_back(static_cast<int>(*Key_itr));		//将Key数组的迭代器的值强制类型转换后填入KBox中
		Key_itr++;										//迭代器自增
		if (Key_itr == Key_itr_end)						//如果此时迭代器为尾迭代器，则迭代器回归头元素
			Key_itr = Key.cbegin();
	}
}

//KSA算法
void RC4::KSA(vector<int> &SBox, vector<int> &KBox) {
	int boxLength = SBox.size();
	int j = 0;
	for (int i = 0; i < boxLength; i++) {
		j = (j + SBox[i] + KBox[i]) % boxLength;
		swap(SBox[i], SBox[j]);							//交换SBox[i]和SBox[j]
	}
}

//PRGA算法
void RC4::PRGA(vector<int> &SBox, vector<int> &ZBox, const int & intputLength) {
	int boxLength = SBox.size();
	int i = 0, j = 0, t = 0;
	for (int k = 0; k < intputLength; k++) {
		i = (i + 1) % boxLength;
		j = (j + SBox[i]) % boxLength;
		swap(SBox[i], SBox[j]);							//交换SBox[i]和SBox[j]
		t = (SBox[i] + SBox[j]) % boxLength;
		ZBox.push_back(SBox[t]);
	}
}

//加密
void RC4::RC4_en(string &input, string &output, vector<int> &ZBox) {
	for (int i = 0; i < input.size(); i++) {
		output.push_back(input[i] ^ ZBox[i]);
	}
}

//解密
void RC4::RC4_de(string &input, string &output, vector<int> &ZBox) {
	for (int i = 0; i < input.size(); i++) {
		output.push_back(input[i] ^ ZBox[i]);
	}
}

//打印S盒
void RC4::print_SBox(vector<int> & SBox) {
	cout << "[+] ---------- S盒 ----------" << endl;
	for (int i = 0; i < SBox.size(); i++) {
		cout << "[" << i << "] " << SBox[i] << "    ";
		if (i!=0 && i % 6 == 0)									//每行六个
			cout << endl;
	}
	cout << "\n[+] ---------- S盒 ----------\n" << endl;
}

//打印K盒
void RC4::print_KBox(vector<int> & KBox) {
	cout << "[+] ---------- K盒 ----------" << endl;
	for (int i = 0; i < KBox.size(); i++) {
		cout << "[" << i << "] " << KBox[i] << "    " ;
		if (i!=0 && i % 6 == 0)									//每行六个
			cout << endl;
	}
	cout << "\n[+] ---------- K盒 ----------\n" << endl;
}

//打印Z盒
void RC4::print_ZBox(vector<int> & ZBox) {
	cout << "[+] ---------- Z盒 ----------" << endl;
	for (int i = 0; i < ZBox.size(); i++){
		cout << "[" << i << "] " << ZBox[i] << "    " ;
		if (i!=0 && i % 6 == 0)									//每行六个
			cout << endl;
	}

	cout << "\n[+] ---------- Z盒 ----------\n" << endl;
}