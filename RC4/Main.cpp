#include "stdafx.h"
#include "RC4.h"

int main() {
	cout << "[+] 现代密码学实验 -- RC4加密算法" << endl;
	cout <<"[+] 作者：高鸣飞" << endl;
	while (true) {
	menu:cout << "\n[+] 是否进行实验？\n" << "1) 进行实验\t2) 退出系统\t3) 从文件读入数据（请将文件命名为data.txt）（未实现）" << endl;

		//读入操作数并将第一个字符做为操作数
		string op_input;

		cin.clear();
		getline(cin, op_input);
		int op = op_input[0] - '0';


		//1） 开始实验
		if (op == 1) {
			RC4 *myRC4 = NULL;
			string key;							//密钥
			string bitLengthStr;				//字长输入字符串
			string word;						//待加密字符串
			string output;						//加密结果字符串
			string result;						//解密结果字符串
			string oper_input;					//判断是否继续加密的输入
			int bitLength = 0;
			int oper = 0;

			cout << "\n[+] ---------- 请输入密钥 ----------" << endl;
			getline(cin, key);
			cout << "\n[+] ---------- 请输入字长（默认为8，最大值为16） ----------" << endl;
			getline(cin, bitLengthStr);
			bitLength = bitLengthStr[0] - '0';
			cout << "\n[+] ---------- 检测到您输入的密钥为 ----------" << endl;
			cout << key << endl;
			cout << "\n[+] ---------- 检测到您输入的字长为 ----------" << endl;
			if (bitLength>0 && bitLength<16)
				cout << bitLength << endl;
			else
				cout << "默认值8" << endl;


			cout << "\n[+] ---------- 正在初始化RC4算法 ----------" << endl;
			if (bitLength>0 && bitLength<16)
				myRC4 = new RC4(key, bitLength);
			else
				myRC4 = new RC4(key);
			cout << "\n[+] ---------- 初始化完毕 ----------" << endl;


			input:cout << "\n[+] ---------- 请输入加密字符串 ----------" << endl;
			getline(cin, word);
			cout << "\n[+] ---------- 检测到您输入的待加密字符串为 ----------" << endl;
			cout << word << endl;
			cout << "\n[+] ---------- 开始加密，将显示过程 ----------" << endl;
			myRC4->RC4_en(word, output);
			myRC4->print_SBox();
			myRC4->print_KBox();
			myRC4->print_ZBox();
			cout << "\n[+] ---------- 加密完毕，加密后的字符串为----------" << endl;
			cout << output << endl;

			myRC4->RC4_de(output, result);
			cout << "\n[+] ---------- 解密完毕，解密后的字符串为----------" << endl;
			cout << result << endl;




			cout << "\n[+] ---------- 请问是否继续？1) 继续  2)返回菜单 ----------" << endl;
			cin.clear();
			getline(cin, oper_input);
			oper = oper_input[0] - '0';
			if (oper == 1)
				goto input;
			else if (oper == 2)
				goto menu;
			else
				cout << "[-]  ---------- 非法参数，请重试！ -----------" << endl;

		}
		//2） 退出系统
		else if (op == 2) {
			cout << "[+]  ---------- 感谢使用，再见。 ----------" << endl;
			exit(0);
		}

		//3） 从文件读入数据
		else if (op == 3) {
			//从文件读入数据
		}

		//非法参数
		else
			cout << "[-]  ---------- 非法参数，请重试！ -----------" << endl;
	}
	return 0;
}