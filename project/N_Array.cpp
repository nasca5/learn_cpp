#include <iostream>
#include <string.h>

// N차원 배열을 제공하는 class 만들기

// N은 객체 생성시에 사용자가 입력한다.
// 입력받은 N개의 차원을 가지는 배열을 생성하는 멤버 함수를 가진 class
// 각 차원은 10개의 원소를 가진다.
// 배열의 모든 원소는 0으로 초기화된다.
// 배열에 접근하는 방법은 일반적으로 배열에 접근할 때와 같이 첨자를 이용해 접근한다.
// 예를 들어 2차원 배열이라면 arr[2][3], 3차원 배열이라면 arr[1][2][3]과 같은 식으로 접근할 수 있다.

// 구현해야 할 기능

// 1. N을 입력받는 멤버 함수 GetN();
// -> 입력받은 N을 NA class의 멤버 변수인 N에 할당한다.
// 2. 멤버 변수인 N의 값을 토대로 N차원 배열을 생성하는 멤버 함수 void MakeNArray();
// 3. 멤버 변수인 배열의 특정값에 접근할 수 있게 해주는 멤버 함수 int GetNArrayValue();
// -> 크기가 미리 정해지지 않았으므로

unsigned long int pow(int Root, int NI)
{
  unsigned long int Result = 1;
  for (int i = 0; i < NI; i++)
  {
    Result *= Root;
  }

  return Result;
}

class NA
{
private:
  int temp;
  int tempR;
  int Result;
  int N;
  int *MultiArray;

public:
  NA()
  {
    std::cout << "Input N to make Array : ";
    std::cin >> N;
    temp = N;
    tempR = 0;
    Result = 0;
    MakeNArray(N);
  }

  NA(const int n)
  {
    temp = n;
    tempR = 0;
    N = n;
    Result = 0;
    MakeNArray(n);
  }

  NA(const NA &na)
  {
    temp = na.N;
    tempR = 0;
    N = na.N;
    Result = 0;
    MakeNArray(na.N);
  }

  ~NA()
  {
    std::cout << "Destructor called!!" << std::endl;
    delete[] MultiArray;
  }
  void MakeNArray(int n);
  int GetValue();
  int GetDimension() const;
  NA &operator[](const int idx);
  NA &operator=(const int value);
};

void NA::MakeNArray(const int n)
{
  if (n <= 0)
  {
    std::cout << "n is lower than zero. please check again." << std::endl;
    MultiArray = NULL;
  }

  MultiArray = new int[pow(10, n)];

  memset(MultiArray, 0, 4000);
}

int NA::GetValue()
{
  return MultiArray[tempR];
}

int NA::GetDimension() const
{
  return N;
}

NA &NA::operator[](const int idx)
{
  Result += (pow(10, N--) / 10) * idx;

  if (N == 0)
  {
    N = temp;
    tempR = Result;
    Result = 0;
  }

  return (*this);
}

NA &NA::operator=(const int value)
{
  MultiArray[tempR] = value;

  return (*this);
}

int main()
{

  NA a(3);

  a[3][2][1] = 15;

  std::cout << "a[3][2][1] : " << a[3][2][1].GetValue() << std::endl;

  std::cout << a.GetDimension() << std::endl;
  // std::cout << a.Result << std::endl;

  return 0;
}
