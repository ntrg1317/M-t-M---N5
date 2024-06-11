#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Mảng chứa 16 khoá
string round_keys[16];

string convertDectoBin(int decimal) {
    string binary;
    while(decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary; 
		decimal = decimal/2;
	}
	while(binary.length() < 4){
		binary = "0" + binary;
	}
    return binary;
}

int convertBintoDec(string binary) {
    int decimal = 0;
    int size = binary.length();
    for(int i = size - 1, j = 0; i >= 0; i--, j++) {
        if (binary[i] == '1') {
            decimal += pow(2, j);
        }
    }
    return decimal;
}

string convertBintoHex(string s)
{
	string hex = "";
	for (int i = 0; i < s.size(); i += 4)
	{
		string k = "";
		for (int j = i; j < i + 4; j++)
			k += s[j];
		if (k == "0000")
			hex += '0';
		else if (k == "0001")
			hex += '1';
		else if (k == "0010")
			hex += '2';
		else if (k == "0011")
			hex += '3';
		else if (k == "0100")
			hex += '4';
		else if (k == "0101")
			hex += '5';
		else if (k == "0110")
			hex += '6';
		else if (k == "0111")
			hex += '7';
		else if (k == "1000")
			hex += '8';
		else if (k == "1001")
			hex += '9';
		else if (k == "1010")
			hex += 'A';
		else if (k == "1011")
			hex += 'B';
		else if (k == "1100")
			hex += 'C';
		else if (k == "1101")
			hex += 'D';
		else if (k == "1110")
			hex += 'E';
		else if (k == "1111")
			hex += 'F';
	}
	return hex;
}

string convertHextoBin(string s)
{
	string bin = "";
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0': bin += "0000"; break;
		case '1': bin += "0001"; break;
		case '2': bin += "0010"; break;
		case '3': bin += "0011"; break;
		case '4': bin += "0100"; break;
		case '5': bin += "0101"; break;
		case '6': bin += "0110"; break;
		case '7': bin += "0111"; break;
		case '8': bin += "1000"; break;
		case '9': bin += "1001"; break;
		case 'A':
		case 'a': bin += "1010"; break;
		case 'B':
		case 'b': bin += "1011"; break;
		case 'C':
		case 'c': bin += "1100"; break;
		case 'D':
		case 'd': bin += "1101"; break;
		case 'E':
		case 'e': bin += "1110"; break;
		case 'F':
		case 'f': bin += "1111"; break;

		}
	}
	return bin;
}

string Dec_to_Bin(int n)
{
	string bin = "";
	while (n > 0)
	{
		bin = (char)(n % 2 + '0') + bin;
		n /= 2;
	}
	while (bin.size() < 4)
		bin = '0' + bin;
	return bin;
}

string shift_left_once(string a) {
    string shifted = "";
    for(int i = 1; i < 28; i++){
        shifted += a[i];
    }
    shifted += a[0];
    return shifted;
}

string shift_left_twice(string a) {
    return shift_left_once(shift_left_once(a));
}

string XOR(string a, string b) {
    string result = "";
    for (int i = 0; i < a.length(); i++) {
        if(a[i] == b[i]) {
            result += "0";
        } else {
            result += "1";
        }
    }
    return result;
}

// Hàm tạo khoá
void generate_keys(string key) {
    int PC_1[56] = {
    57,49,41,33,25,17,9, 
	1,58,50,42,34,26,18, 
	10,2,59,51,43,35,27, 
	19,11,3,60,52,44,36,		 
	63,55,47,39,31,23,15, 
	7,62,54,46,38,30,22, 
	14,6,61,53,45,37,29, 
	21,13,5,28,20,12,4 
    };

    int PC_2[48] = {
    14,17,11,24,1,5, 
	3,28,15,6,21,10, 
	23,19,12,4,26,8, 
	16,7,27,20,13,2, 
	41,52,31,37,47,55, 
	30,40,51,45,33,48, 
	44,49,39,56,34,53, 
	46,42,50,36,29,32 
    };

    // Hoán vị key theo bảng pc_1
    string perm_key = "";
    for(int i = 0; i < 56; i++) {
        perm_key += key[PC_1[i] - 1];
    }

    // Xác định giá trị C0 và D0
    string C = perm_key.substr(0, 28);
    string D = perm_key.substr(28, 28);

    for(int i = 0; i < 16; i++) {
        // Lần lặp thứ 1, 2, 9, 16 dịch trái 1 lần; những vị trí còn lại dịch trái 2 lần
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            C = shift_left_once(C);
            D = shift_left_once(D);
        } else {
            C = shift_left_twice(C);
            D = shift_left_twice(D);
        }

        string combined_key = C + D;

        string round_key = "";
        for(int j = 0; j < 48; j++) {
            round_key += combined_key[PC_2[j] - 1];
        }
        round_keys[i] = round_key; 
    }
}

string f(string R, string round_key) {
    int E[48] = {
    32,1,2,3,4,5,4,5, 
	6,7,8,9,8,9,10,11, 
	12,13,12,13,14,15,16,17, 
	16,17,18,19,20,21,20,21, 
	22,23,24,25,24,25,26,27, 
	28,29,28,29,30,31,32,1
    };

    // selection function
    int S[8][4][16] = 
    {{ 
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
    }, 
    { 
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
    }, 
    { 
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
    }, 
    { 
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
    }, 
    { 
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
    }, 
    { 
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
    }, 
    { 
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
    }, 
    { 
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
    }};

    int P[32] = { 
	16,7,20,21,29,12,28,17, 
	1,15,23,26,5,18,31,10, 
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25 
	}; 

    // Hoán vị R
    string RE = "";
    for(int i = 0; i < 48; i++) {
        RE += R[E[i] - 1];
    }

    string xored = XOR(RE, round_key);
    string res = "";
    for(int i = 0; i < 8; i++) {
        string row_bin = xored.substr(i * 6, 1) + xored.substr(i * 6 + 5, 1);
        int row = convertBintoDec(row_bin);
        string col_bin = xored.substr(i * 6 + 1, 1) + xored.substr(i * 6 + 2, 1) + xored.substr(i * 6 + 3, 1) + xored.substr(i * 6 + 4, 1);
        int col = convertBintoDec(col_bin);

        int val = S[i][row][col];
        res += convertDectoBin(val);
    }

    string f = "";
    for(int i = 0; i < 32; i++) {
        f += res[P[i] - 1];
    }
    return f;
}

string DES(string plain_text) {

    int IP[64] = {
    58,50,42,34,26,18,10,2, 
	60,52,44,36,28,20,12,4, 
	62,54,46,38,30,22,14,6, 
	64,56,48,40,32,24,16,8, 
	57,49,41,33,25,17,9,1, 
	59,51,43,35,27,19,11,3, 
	61,53,45,37,29,21,13,5, 
	63,55,47,39,31,23,15,7
    };

    int inverse_IP[64] = {
    40,8,48,16,56,24,64,32, 
	39,7,47,15,55,23,63,31, 
	38,6,46,14,54,22,62,30, 
	37,5,45,13,53,21,61,29, 
	36,4,44,12,52,20,60,28, 
	35,3,43,11,51,19,59,27, 
	34,2,42,10,50,18,58,26, 
	33,1,41,9,49,17,57,25 
    };

    int E[48] = {
    32,1,2,3,4,5,4,5, 
	6,7,8,9,8,9,10,11, 
	12,13,12,13,14,15,16,17, 
	16,17,18,19,20,21,20,21, 
	22,23,24,25,24,25,26,27, 
	28,29,28,29,30,31,32,1
    };


    // Thực hiện hoán vị bản rõ
    string permutation = "";
    for(int i = 0; i < 64; i++) {
        permutation += plain_text[IP[i] - 1];
    }

    string L = permutation.substr(0, 32);
    string R = permutation.substr(32, 32);

    for(int i = 0; i < 16; i++) {
        string xored1 = XOR(L, f(R, round_keys[i]));
        L = xored1;
        if (i < 15) {
            string temp = R;
			R = xored1;
			L = temp;
        }
    }

    string combined_text = L + R;
    string ciphertext =""; 
	// Áp dụng bảng hoán vị IP-1
	for(int i = 0; i < 64; i++){ 
		ciphertext += combined_text[inverse_IP[i] - 1]; 
	}

	return ciphertext;
}

bool is_valid(string text, int length) {
	if (text.size() != length)
		return false;

	else
	{
		for (int i = 0; i < text.size(); i++)
			if (!((text[i] <= 'f' && text[i] >= 'a') ||
				(text[i] <= 'F' && text[i] >= 'A') ||
				(text[i] >= '0' && text[i] <= '9'))) {
				return false;
				break;
			}
	}
	return true;
}

void encrypt() {
    string plain_text;
    string key;
    system("cls");
    cout << "Nhap ban ro (16 ki tu): ";
    do {
        cin >> plain_text;
        if (!is_valid(plain_text, 16))
            cout << "Moi ban nhap lai ban ro : ";
    } while (!is_valid(plain_text, 16));

    cout << "Nhap khoa (16 ki tu): ";
    do {
        cin >> key;
        if (!is_valid(key, 16))
            cout << "Moi ban nhap lai ban ro : ";
    } while (!is_valid(key, 16));

    generate_keys(convertHextoBin(key));

    string ciphertext = DES(convertHextoBin(plain_text));
    cout <<  "Ban ro: " << plain_text << endl;
    cout << "Ban ma: " << convertBintoHex(ciphertext) << endl;
}

void decrypt() {
    string ciphertext;
    string key;
    system("cls");

    cout << "Nhap ban ma (16 ki tu): ";
    do {
        cin >> ciphertext;
        if (!is_valid(ciphertext, 16))
            cout << "Moi ban nhap lai ban ro : ";
    } while (!is_valid(ciphertext, 16));

    cout << "Nhap khoa (16 ki tu): ";
    do {
        cin >> key;
        if (!is_valid(key, 16))
            cout << "Moi ban nhap lai ban ro : ";
    } while (!is_valid(key, 16));


    generate_keys(convertHextoBin(key));

	
	int i = 15;
	int j = 0;
	while(i > j)
	{
		string temp = round_keys[i];
		round_keys[i] = round_keys[j];
		round_keys[j] = temp;
		i--;
		j++;
	}

    string plaintext = DES(convertHextoBin(ciphertext));
    cout << "Ban ma: " << ciphertext << endl;
    cout << "Ban ro: " << convertBintoHex(plaintext) << endl;
} 

string nextHEX(string s) {
    int length = s.length();
    int carry = 1; // Biến nhớ để tăng số

    // Duyệt từ phải sang trái của chuỗi HEX
    for (int i = length - 1; i >= 0; i--) {
        int digit;
        if (s[i] >= '0' && s[i] <= '9') {
            digit = s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            digit = s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            digit = s[i] - 'A' + 10;
        } else {
            cout << "Chuỗi nhập vào không hợp lệ!\n";
            return s;
        }

        digit += carry;
        if (digit >= 16) {
            digit -= 16;
            carry = 1; // Tiếp tục tăng số ở vị trí cao hơn
        } else {
            carry = 0; // Không cần tăng số ở vị trí cao hơn
        }

        if (digit < 10) {
            s[i] = '0' + digit;
        } else {
            s[i] = 'a' + (digit - 10);
        }
    }

    // Nếu carry vẫn còn, chúng ta cần thêm '1' vào đầu chuỗi
    if (carry) {
        s.insert(s.begin(), '1');
    }

    return s;
}

void bruteforce() {
	bool found ;
	string plain_text ; 
    string ciphertext;
    string key ;  
	string keyleft;
	string keyright;
	int count = 0 ;
	string Key[1000] ;
    system("cls");
    cout << "Nhap ban ro (16 ki tu): ";
    do {
        cin >> plain_text;
        if (!is_valid(plain_text, 16))
            cout << "Moi ban nhap lai ban ro : ";
    } while (!is_valid(plain_text, 16));

    cout << "Nhap ban ma (16 ki tu): ";
    do {
        cin >> ciphertext;
        if (!is_valid(ciphertext, 16))
            cout << "Moi ban nhap lai ban ro : ";
    } while (!is_valid(ciphertext, 16));

	cout << "Nhap khoang cua khoa da biet gom 2 chuoi 16 ky tu theo thu tu tang:\n" ;
    cout << "Khoa trai (16 ky tu): ";
    do {
        cin >> keyleft;
        if (!is_valid(keyleft, 16))
            cout << "Moi ban nhap lai ban ro : ";
    } while (!is_valid(keyleft, 16));

	cout << "Khoa phai (16 ky tu): " ;
    do {
        cin >> keyright;
        if (!is_valid(keyright, 16))
            cout << "Moi ban nhap lai ban ro : ";
    } while (!is_valid(keyright, 16));

	key = keyleft ;
	found = false ;
	
	do  { 
	    cout << "Key: " << key << endl;
	   
	    generate_keys(convertHextoBin(key)) ; 
	    cout << "Ban ma: " << convertBintoHex(DES(convertHextoBin(plain_text))) << endl ;
		if(DES(convertHextoBin(plain_text)) == convertHextoBin(ciphertext)){
			found = true ;
			count++ ;
			Key[count] = key ;
		}
		key = nextHEX (key) ;

        } 
        while (key != keyright) ;
	    if (found == false) {
		    cout << "Khong tim thay khoa!" ;
	    }
	    if(found == true) 
	    {
	        cout << "Tim duoc " << count << " khoa duoi day: " << endl ;
	        for(int i=1; i<=count; i++)
	        {
	            cout << Key[i] << endl ;
	        }
	    }
    }