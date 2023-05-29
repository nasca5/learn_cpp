#include <iostream>
#include <string.h>
#include <stdlib.h>


class string {
  char* str;
  int len;

  public:
    string(char c, int n);
    string(const char* s);
    string(const string& s);
    ~string();

    void add_string(const string& s);
    void copy_string(const string& s);
    void show_string();
    int length();
};

string::string(char c, int n) {
  int i;
  str = new char[100];
  len = n;
  for(i = 0; i < len; i++) {
    *(str + i) = c;
  }
  *(str + i) = '\0';
}

string::string(const char* s) {
  str = new char[100];
  strcpy(str, s);
  len = strlen(str);
}

string::string(const string& s) {
  str = new char[100];
  strcpy(str, s.str);
  len = s.len;
}

string::~string() {
  if(str)
    delete[] str;
}

void string::add_string(const string& s) {
  int i = 0;

  while(*(str + i + len) = *(s.str + i)) {
    i++;
  }

  len += s.len;
  *(str + len) = '\0';
}

void string::copy_string(const string& s) {
  int i = 0;

  while(*(str + i) = *(s.str + i)) i++;

  *(str + i) = '\0';
  len = s.len;
}

int string::length() {
  return len;
}

void string::show_string() {
  std::cout << "Len    : " << len << std::endl;
  std::cout << "String : " << str << std::endl;
}

int main() {
  string str1("hello");
  string str2("world!");
  string str3('c', 34);

  str3.show_string();

  str1.add_string(str2);
  str3.copy_string(str2);
  
  str1.show_string();
  str3.show_string();
  
  std::cout << str3.length() << std::endl;

  return 0;
}
