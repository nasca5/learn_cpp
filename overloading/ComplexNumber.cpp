#include <iostream>
#include <cstdlib>

int strlen(const char *str)
{
  int i = 0;
  while (str[i] != '\0')
  {
    i++;
  }
  return i;
}

int isdigit(const char c)
{
  if (c >= '0' && c <= '9')
  {
    return 1;
  }

  return 0;
}

class Complex
{
private:
  double real, img;

  double get_number(const char *str, int from, int to);

public:
  Complex(double real, double img) : real(real), img(img) {}
  Complex(const Complex &c) : real(c.real), img(c.img) {}
  Complex(const char *str);

  // Complex operator+(const Complex &c) const;
  // Complex operator+(const char *str) const;

  // Complex operator-(const Complex &c) const;
  // Complex operator-(const char *str) const;

  // Complex operator*(const Complex &c) const;
  // Complex operator*(const char *str) const;

  // Complex operator/(const Complex &c) const;
  // Complex operator/(const char *str) const;

  Complex &operator=(const Complex &c);

  Complex &operator+=(const Complex &c);
  Complex &operator-=(const Complex &c);
  Complex &operator*=(const Complex &c);
  Complex &operator/=(const Complex &c);

  friend Complex operator+(const Complex &a, const Complex &b);
  friend Complex operator-(const Complex &a, const Complex &b);
  friend Complex operator*(const Complex &a, const Complex &b);
  friend Complex operator/(const Complex &a, const Complex &b);

  friend std::ostream &operator<<(std::ostream &os, const Complex &c);

  void print();
};

Complex::Complex(const char *str)
{
  int begin = 0;
  int end = strlen(str);
  real = 0.0;
  img = 0.0;

  int pos_i = -1;
  int i = begin, j = begin;

  bool minus = false;

  for (; i <= end; i++)
  {
    if (str[i] == 'i')
    {
      pos_i = i;
      break;
    }
  }

  char *str_real = new char[pos_i - begin];
  char *str_img = new char[end - pos_i];

  for (; j < pos_i; j++)
  {
    str_real[j - begin] = str[j];
  }

  if (pos_i == -1)
  {
    real = atof(str_real);
    return;
  }

  else
  {
    for (j += 1; j < end; j++)
    {
      str_img[j - pos_i - 1] = str[j];
    }

    real = atof(str_real);
    img = atof(str_img);
  }

  if (pos_i >= 1 && str[pos_i - 1] == '-')
  {
    minus = true;
  }

  if (minus)
  {
    img *= -1.0;
  }

  delete[] str_real;
  delete[] str_img;

  // if (pos_i == -1)
  // {
  //   real = get_number(str, begin, end - 1);
  //   return;
  // }

  // else
  // {
  //   real = get_number(str, begin, pos_i - 1);
  //   img = get_number(str, pos_i + 1, end - 1);
  // }

  // if (pos_i >= 1 && str[pos_i - 1] == '-')
  // {
  //   img *= -1.0;
  // }
}

// Complex Complex::operator+(const Complex &c) const
// {
//   Complex temp(real + c.real, img + c.img);
//   return temp;
// }

// Complex Complex::operator-(const Complex &c) const
// {
//   Complex temp(real - c.real, img - c.img);
//   return temp;
// }

// Complex Complex::operator*(const Complex &c) const
// {
//   Complex temp(real * c.real - img * c.img, real * c.img + c.real * img);
//   return temp;
// }

// Complex Complex::operator/(const Complex &c) const
// {
//   Complex temp((real * c.real + img * c.img) / (c.real * c.real + c.img * c.img), (img * c.real - c.img * real) / (c.real * c.real + c.img * c.img));
//   return temp;
// }

Complex &Complex::operator=(const Complex &c)
{
  real = c.real;
  img = c.img;
  return *this;
}

Complex &Complex::operator+=(const Complex &c)
{
  (*this) = (*this) + c;
  return *this;
}
Complex &Complex::operator-=(const Complex &c)
{
  (*this) = (*this) - c;
  return *this;
}
Complex &Complex::operator*=(const Complex &c)
{
  (*this) = (*this) * c;
  return *this;
}
Complex &Complex::operator/=(const Complex &c)
{
  (*this) = (*this) / c;
  return *this;
}

// Complex Complex::operator+(const char *str) const
// {
//   Complex temp(str);
//   return (*this) + temp;
//}

// Complex Complex::operator-(const char *str) const
// {
//   Complex temp(str);
//   return (*this) - temp;
// }

// Complex Complex::operator*(const char *str) const
// {
//   Complex temp(str);
//   return (*this) * temp;
// }

// Complex Complex::operator/(const char *str) const
// {
//   Complex temp(str);
//   return (*this) / temp;
// }

double Complex::get_number(const char *str, int from, int to)
{
  bool minus = false;
  bool int_part = true;

  double num = 0.0;
  double decimal = 1.0;

  if (from > to)
  {
    return 0;
  }
  if (str[from] == '-')
  {
    minus = true;
    from++;
  }
  if (str[from] == '+')
  {
    from++;
  }

  for (int i = from; i <= to; i++)
  {
    if (isdigit(str[i]) && int_part)
    {
      num *= 10;
      num += (str[i] - '0');
    }
    else if (str[i] == '.')
    {
      int_part = false;
    }
    else if (isdigit(str[i]) && !int_part)
    {
      decimal /= 10.0;
      num += ((str[i] - '0') * decimal);
    }
    else
    {
      break;
    }
  }

  if (minus)
  {
    num *= -1.0;
  }

  return num;
}

void Complex::print()
{
  std::cout << "(" << real << " , " << img << ")" << std::endl;
}

Complex operator+(const Complex &a, const Complex &b)
{
  Complex temp(a.real + b.real, a.img + b.img);
  return temp;
}

Complex operator-(const Complex &a, const Complex &b)
{
  Complex temp(a.real - b.real, a.img - b.img);
  return temp;
}

Complex operator*(const Complex &a, const Complex &b)
{
  Complex temp(a.real * b.real - a.img * b.img, a.real * b.img + b.real * a.img);
  return temp;
}

Complex operator/(const Complex &a, const Complex &b)
{
  Complex temp((a.real * b.real + a.img * b.img) / (b.real * b.real + b.img * b.img),
               (a.img * b.real - b.img * a.real) / (b.real * b.real + b.img * b.img));
  return temp;
}

std::ostream &operator<<(std::ostream &os, const Complex &c)
{
  os << "(" << c.real << " , " << c.img << ")";
  return os;
}

int main()
{
  Complex a(0, 0);
  // a = "-1.1 + i3.923" + a;
  a = a + "-1.1 + i3.932";
  Complex b(a);
  a = a + b + "-2.5 + i3.354";
  std::cout << "a's value is " << a << "!" << std::endl;
  // a.print();
  // a = a + "-1.1 + i3.923";
  // a.print();
  // a = a - "1.2 -i1.823";
  // a.print();
  // a = a * "2.3+i22";
  // a.print();
  // a = a / "-12+i55";
  // a.print();
  // Complex a(0.0, 0.0);
  // Complex b(3.0, -2.0);
  // Complex c(0.0, 0.0);

  // a += b;
  // c = a * b + a / b + a + b;

  // a = a + "-1.1 + i3.923";
  // a.print();
  // b.print();

  return 0;
}
