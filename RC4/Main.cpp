#include "stdafx.h"
#include "RC4.h"

int main() {
	cout << "[+] �ִ�����ѧʵ�� -- RC4�����㷨" << endl;
	cout <<"[+] ���ߣ�������" << endl;
	while (true) {
	menu:cout << "\n[+] �Ƿ����ʵ�飿\n" << "1) ����ʵ��\t2) �˳�ϵͳ\t3) ���ļ��������ݣ��뽫�ļ�����Ϊdata.txt����δʵ�֣�" << endl;

		//���������������һ���ַ���Ϊ������
		string op_input;

		cin.clear();
		getline(cin, op_input);
		int op = op_input[0] - '0';


		//1�� ��ʼʵ��
		if (op == 1) {
			RC4 *myRC4 = NULL;
			string key;							//��Կ
			string bitLengthStr;				//�ֳ������ַ���
			string word;						//�������ַ���
			string output;						//���ܽ���ַ���
			string result;						//���ܽ���ַ���
			string oper_input;					//�ж��Ƿ�������ܵ�����
			int bitLength = 0;
			int oper = 0;

			cout << "\n[+] ---------- ��������Կ ----------" << endl;
			getline(cin, key);
			cout << "\n[+] ---------- �������ֳ���Ĭ��Ϊ8�����ֵΪ16�� ----------" << endl;
			getline(cin, bitLengthStr);
			bitLength = bitLengthStr[0] - '0';
			cout << "\n[+] ---------- ��⵽���������ԿΪ ----------" << endl;
			cout << key << endl;
			cout << "\n[+] ---------- ��⵽��������ֳ�Ϊ ----------" << endl;
			if (bitLength>0 && bitLength<16)
				cout << bitLength << endl;
			else
				cout << "Ĭ��ֵ8" << endl;


			cout << "\n[+] ---------- ���ڳ�ʼ��RC4�㷨 ----------" << endl;
			if (bitLength>0 && bitLength<16)
				myRC4 = new RC4(key, bitLength);
			else
				myRC4 = new RC4(key);
			cout << "\n[+] ---------- ��ʼ����� ----------" << endl;


			input:cout << "\n[+] ---------- ����������ַ��� ----------" << endl;
			getline(cin, word);
			cout << "\n[+] ---------- ��⵽������Ĵ������ַ���Ϊ ----------" << endl;
			cout << word << endl;
			cout << "\n[+] ---------- ��ʼ���ܣ�����ʾ���� ----------" << endl;
			myRC4->RC4_en(word, output);
			myRC4->print_SBox();
			myRC4->print_KBox();
			myRC4->print_ZBox();
			cout << "\n[+] ---------- ������ϣ����ܺ���ַ���Ϊ----------" << endl;
			cout << output << endl;

			myRC4->RC4_de(output, result);
			cout << "\n[+] ---------- ������ϣ����ܺ���ַ���Ϊ----------" << endl;
			cout << result << endl;




			cout << "\n[+] ---------- �����Ƿ������1) ����  2)���ز˵� ----------" << endl;
			cin.clear();
			getline(cin, oper_input);
			oper = oper_input[0] - '0';
			if (oper == 1)
				goto input;
			else if (oper == 2)
				goto menu;
			else
				cout << "[-]  ---------- �Ƿ������������ԣ� -----------" << endl;

		}
		//2�� �˳�ϵͳ
		else if (op == 2) {
			cout << "[+]  ---------- ��лʹ�ã��ټ��� ----------" << endl;
			exit(0);
		}

		//3�� ���ļ���������
		else if (op == 3) {
			//���ļ���������
		}

		//�Ƿ�����
		else
			cout << "[-]  ---------- �Ƿ������������ԣ� -----------" << endl;
	}
	return 0;
}