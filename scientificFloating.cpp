#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

void reverse(char* str){
  int len = strlen(str);
  for (int i = 0; i < len / 2; i++){
    char tmp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = tmp;
  } // end for
} // end reverse

char* dec(float dec){
	char* bin = new char[100];
  float mod = dec;
	float pro = 0;
	for (int i = 0; mod != 0; i++){
		pro = mod * 2;
    mod = pro - (int) pro;
    bin[i] = (int) pro + '0';
	} // end for
	reverse(bin);
	return bin;
}

char* whole(int val){
  char* bin = new char[100];
  int mod = val;
  int rem = 0;
  int i = 0;
  while (mod != 0){  
    rem = mod % 2;
    mod = mod / 2;
    bin[i++] = rem + '0';
  } // end while
  reverse(bin);
  return bin;
} // end vtoB

void fix(char* bin){
  int len = strlen(bin);
  int dec = 0;
  for (int i = 0; i < len; i++){
    if (bin[i] == '.'){
      dec = i;
      for (int j = i; j > 1; j--){
        bin[j] = bin[j - 1];
        bin[j - 1] = '.';
      } // end for
      break;
    } // edn if
  } // end for
  strcat(bin, "E");
  int sci = (dec + '0' - 1);
  char a = '\0';
  int mod = sci, rem = 0;
  for (int i = 0; mod != 0; i++){
    rem = mod % 10;
    mod = mod / 10;
    a = '0' + rem;
    strcat(bin, &a);
  }
}

char* science(int wh, float d){
	char* binary = new char[200];
  strcat(binary, whole(wh));
  strcat(binary, ".");
  strcat(binary, dec(d));
  fix(binary);
	return binary;
}

int main(){
	float fl = 0;
	cout << "Please enter a float: ";
	cin >> fl;
	
	int whole = (int) fl;
	float rem = fl - whole;
	cout << science(whole, rem);
	return 0;
}