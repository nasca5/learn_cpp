#include <iostream>
#include <string.h>
#include <stdlib.h>

class string
{
  static int i;
  char *str;
  int len;

public:
  string(char c, int n);
  string(const char *s);
  string(const string &s);
  ~string();

  void add_string(const string &s);
  void copy_string(const string &s);
  int cmp_string(const string &s);
  int cmp_size_string(const string &s);
  void show_string();
  int length();
};
int string::i = 0;

string::string(char c, int n)
{
  i = 0;
  str = new char[1000];
  len = n;
  for (i = 0; i < len; i++)
  {
    *(str + i) = c;
  }
  *(str + i) = '\0';
}

string::string(const char *s)
{
  str = new char[1000];
  strcpy(str, s);
  len = strlen(str);
}

string::string(const string &s) : len(s.len)
{
  str = new char[1000];
  strcpy(str, s.str);
}

string::~string()
{
  if (str)
    delete[] str;
}

void string::add_string(const string &s)
{
  i = 0;

  while (*(str + i + len) = *(s.str + i))
  {
    i++;
  }

  len += s.len;
  *(str + len) = '\0';
}

void string::copy_string(const string &s)
{
  i = 0;

  while (*(str + i) = *(s.str + i))
    i++;

  *(str + i) = '\0';
  len = s.len;
}

int string::cmp_string(const string &s)
{
  i = 0;

  while (*(s.str + i) != '\0')
  {
    if (*(str + i) != *(s.str + i))
    {
      return -1;
    }
    i++;
  }

  if (*(str + i) == '\0')
  {
    return 1;
  }

  return -1;
}

int string::cmp_size_string(const string &s)
{
  i = 0;
  while (*(s.str + i) != '\0')
  {
    if (*(str + i) > *(s.str + i))
    {
      return 1;
    }
    else if (*(str + i) < *(s.str + i))
    {
      return -1;
    }
    i++;
  }
  if (*(str + i) == '\0')
  {
    return 0;
  }
  return 1;
}

int string::length()
{
  return len;
}

void string::show_string()
{
  std::cout << "Len    : " << len << std::endl;
  std::cout << "String : " << str << std::endl;
}

int main()
{
  int res1, res2;
  string str1("hello");
  string str2("world!");
  string str3('c', 34);
  string str4(str2);
  str3.show_string();

  str1.add_string(str2);
  str3.copy_string(str2);

  str1.show_string();
  str3.show_string();

  res1 = str4.cmp_string(str2);
  res2 = str4.cmp_size_string(str2);
  std::cout << res1 << std::endl;
  std::cout << res2 << std::endl;
  res1 = str4.cmp_string(str1);
  res2 = str4.cmp_size_string(str1);
  std::cout << res1 << std::endl;
  std::cout << res2 << std::endl;

  int a;

  std::cin >> a;

  return 0;
}
