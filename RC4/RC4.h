#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <ctype.h>
using namespace std;

/*

����˵��
SBoxΪS��
KBoxΪK��
ZBoxΪ��Կ��
bitLength��ÿ���ֵĳ���
boxLength�Ǻ��ӵĴ�С

*/
class RC4 {

public:

	//RC4���캯����bitLengthĬ��Ϊ8����Կ�ַ���key�����ṩ
	RC4(string &key, const int & bitLength = 8) : Key(key), bitLength(bitLength), boxLength(1 << bitLength)
	{
		init_SBox(SBox, boxLength);			//��ʼ��S��
		init_KBox(KBox, boxLength, Key);	//��ʼ��K��
		KSA(SBox, KBox);					//KSA�㷨������S��
	}
	
	void RC4_en(string &input, string &output) {
		output.clear();						//�������ַ���
		RC4_clear(ZBox);					//���Z��
		PRGA(SBox, ZBox, input.size());		//PRGA�㷨������Z��
		RC4_en(input, output, ZBox);		//���ַ�����λ�����������output��
	}
	void RC4_de(string &output, string &source) {
		source.clear();						//�������ַ���
		RC4_de(output, source, ZBox);		//���ַ������ܣ���������source��
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

	//����Z�У�ʹ������ظ�ʹ��
	void RC4_clear(vector<int> &ZBox);

	//��ʼ��S�У�S�д�СΪ2^bitLength�����������λ�ķ�ʽ����
	void init_SBox(vector<int> &SBox, const int & boxLength);

	//��ʼ��K�У�K�д�СΪ2^bitLength���������λ�Ƶķ�ʽ����
	void init_KBox(vector<int> &KBox, const int & boxLength, string &Key);

	//KSA�㷨
	void KSA(vector<int> &SBox, vector<int> &KBox);

	//PRGA�㷨
	void PRGA(vector<int> &SBox, vector<int> &ZBox, const int & intputLength);

	//����
	void RC4_en(string &input, string &output, vector<int> &ZBox);

	//����
	void RC4_de(string &input, string &output, vector<int> &ZBox);

	//��ӡS��
	void print_SBox(vector<int> & SBox);

	//��ӡK��
	void print_KBox(vector<int> & KBox);

	//��ӡZ��
	void print_ZBox(vector<int> & ZBox);

};

//����Z�У�ʹ������ظ�ʹ��
void RC4::RC4_clear(vector<int> &ZBox) {
	ZBox.clear();
}

//��ʼ��S�У�S�д�СΪ2^bitLength�����������λ�ķ�ʽ����
void RC4::init_SBox(vector<int> &SBox, const int & boxLength) {
	for (int i = 0; i < boxLength; i++)
		SBox.push_back(i);
}

//��ʼ��K�У�K�д�СΪ2^bitLength���������λ�Ƶķ�ʽ����
void RC4::init_KBox(vector<int> &KBox, const int & boxLength, string &Key) {
	string::const_iterator Key_itr = Key.cbegin();
	string::const_iterator Key_itr_end = Key.cend();
	for (int i = 0; i < boxLength; i++) {
		if (isdigit(*Key_itr))
			KBox.push_back(*Key_itr - '0');
		else
			KBox.push_back(static_cast<int>(*Key_itr));		//��Key����ĵ�������ֵǿ������ת��������KBox��
		Key_itr++;										//����������
		if (Key_itr == Key_itr_end)						//�����ʱ������Ϊβ����������������ع�ͷԪ��
			Key_itr = Key.cbegin();
	}
}

//KSA�㷨
void RC4::KSA(vector<int> &SBox, vector<int> &KBox) {
	int boxLength = SBox.size();
	int j = 0;
	for (int i = 0; i < boxLength; i++) {
		j = (j + SBox[i] + KBox[i]) % boxLength;
		swap(SBox[i], SBox[j]);							//����SBox[i]��SBox[j]
	}
}

//PRGA�㷨
void RC4::PRGA(vector<int> &SBox, vector<int> &ZBox, const int & intputLength) {
	int boxLength = SBox.size();
	int i = 0, j = 0, t = 0;
	for (int k = 0; k < intputLength; k++) {
		i = (i + 1) % boxLength;
		j = (j + SBox[i]) % boxLength;
		swap(SBox[i], SBox[j]);							//����SBox[i]��SBox[j]
		t = (SBox[i] + SBox[j]) % boxLength;
		ZBox.push_back(SBox[t]);
	}
}

//����
void RC4::RC4_en(string &input, string &output, vector<int> &ZBox) {
	for (int i = 0; i < input.size(); i++) {
		output.push_back(input[i] ^ ZBox[i]);
	}
}

//����
void RC4::RC4_de(string &input, string &output, vector<int> &ZBox) {
	for (int i = 0; i < input.size(); i++) {
		output.push_back(input[i] ^ ZBox[i]);
	}
}

//��ӡS��
void RC4::print_SBox(vector<int> & SBox) {
	cout << "[+] ---------- S�� ----------" << endl;
	for (int i = 0; i < SBox.size(); i++) {
		cout << "[" << i << "] " << SBox[i] << "    ";
		if (i!=0 && i % 6 == 0)									//ÿ������
			cout << endl;
	}
	cout << "\n[+] ---------- S�� ----------\n" << endl;
}

//��ӡK��
void RC4::print_KBox(vector<int> & KBox) {
	cout << "[+] ---------- K�� ----------" << endl;
	for (int i = 0; i < KBox.size(); i++) {
		cout << "[" << i << "] " << KBox[i] << "    " ;
		if (i!=0 && i % 6 == 0)									//ÿ������
			cout << endl;
	}
	cout << "\n[+] ---------- K�� ----------\n" << endl;
}

//��ӡZ��
void RC4::print_ZBox(vector<int> & ZBox) {
	cout << "[+] ---------- Z�� ----------" << endl;
	for (int i = 0; i < ZBox.size(); i++){
		cout << "[" << i << "] " << ZBox[i] << "    " ;
		if (i!=0 && i % 6 == 0)									//ÿ������
			cout << endl;
	}

	cout << "\n[+] ---------- Z�� ----------\n" << endl;
}