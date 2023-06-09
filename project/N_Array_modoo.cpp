#include <iostream>
#include <string.h>

// 전체 class를 MyArray라는 namespace로 감쌌다.
// 이를 통해 다른 라이브러리에서 Array라는 class가 정의되어있더라도 문제 없이 사용 가능하다.
// 또한 두 개의 class를 한 파일에서 사용하기 때문에 class의 정의 순서가 매우 중요하다.
// 아래의 코드를 보면 MyArray namespace의 최상단에 미리 Array와 Int class를 선언한 것을 알 수 있다.
// 이는 Array class에서 Int class를 friend 키워드로 선언했는데, 만약 Int class를 최상단에서 미리 선언하지 않았다면
// 컴파일러 입장에서는 Int class가 존재하는지 알 수 없기 때문에 오류가 날 수 있다.

// 그렇다고 Array class 안에서 실제 Int class의 내부 정보를 이용할 수는 없다.
// 선언만 된 상태에서는 friend나 class의 포인터를 정의하는 등의 Int class의 내부 정보가 필요없는 것들에 한해서만 사용 가능하다.
// 실제 Int class의 내부 정보를 이용하여 동작하는 멤버 함수같은 것을 작성할려면 Int class의 정의가 선행되어야만 한다.
namespace MyArray
{
  class Array;
  class Int;

  // N차원 배열을 생성하는 class
  class Array
  {
  private:
    const int dim; // 몇 차원 배열인지
    int *size;     // size[0] * size[1] * size[2] ... size[dim - 1] 크기의 배열

    friend Int;

    // class 안에는 구조체뿐만 아니라 다른 class도 넣을 수 있다.
    // 따라서 구조체의 정의 자체를 Array class 안에 넣어놨다.
    // 구조체의 정의 자체를 class 안에 넣어놓은 이유는 Array class의 인스턴스가 내부적으로 어떻게 작동
    // 하는지 공개하고 싶지 않고, 또 내부 정보에 접근하는 것을 원치 않기 때문이다.
    // C++ 구조체는 모든 멤버 함수, 변수가 디폴트로 public인 class라고 생각하면 된다.
    typedef struct Address
    {
      int level;
      void *next;
    } Addr;

    // Array class로 만든 인스턴스의 Addr 구조체 포인터 Top의 모든 배열의 원소들에 순차적으로 접근할 수 있는 반복자(iterator)를 만들었다.
    // 이 Iterator class는 배열의 특정한 원소에 대한 포인터라고 생각하면 된다.
    // C 언어에서 배열의 어떤 원소를 가리키고 있는 포인터 ptr에 ptr++를 했다면 다음 원소를 가리켰듯이, 반복자 itr이
    // Array의 어느 원소를 가리키고 있을 때 itr++를 하면 그 다음 원소를 가리키게 된다.
    // 따라서 사용자는 N 중 for 문을 사용해서 전체 원소를 참조하는 방법보다는 단순히 itr을 이용해서 
    // Array의 첫 원소부터 itr++을 통해 마지막 원소까지 가리킬 수 있게 할 수 있다.
    // 이를 위해서, Iterator class에 현재 Iterator가 어떤 원소를 가리키고 있는지에 대한 정보를 멤버 변수로 가져야 한다.
    // 이는 int *location에 배열로 보관된다.
    // 예를 들어 3차원 배열인 arr의 임의의 원소 arr[1][2][3]을 Iterator가 가리키고 있다면, location 배열의 원소는
    // {1, 2, 3}가 된다.
    class Iterator
    {
      private:
        int* location;
        Array* arr;
      
      public:
        Iterator& operator++()
        {
          if (location[0] >= arr->size[0]) return (*this);

          bool carry = false;
          int i = arr->dim -1;

          do {
            location[i]++;
            if (location[i] >= arr->size[i] && i >= 1)
            {
              location[i] -= arr->size[i];
              carry = true;
              i--;
            }

            else
            {
              carry = false;
            }
          } while (i >= 0 && carry);

          return (*this);
        }

        Iterator operator++(int x)
        {
          Iterator itr(*this);
          ++(*this);
          return itr;
        }

        Int operator*();
    };

    Addr *Top;

  public:
    Array(int dim, int *array_size) : dim(dim)
    {
      size = new int[dim];
      for (int i = 0; i < dim; i++)
      {
        size[i] = array_size[i];
      }

      Top = new Addr;
      Top->level = 0;

      InitAddr(Top);
    }

    Array(const Array &arr) : dim(arr.dim)
    {
      size = new int[dim];
      for (int i = 0; i < dim; i++)
      {
        size[i] = arr.size[i];
      }

      Top = new Addr;
      Top->level = 0;

      InitAddr(Top);

      // 배열의 내용 복사
      CopyAddr(Top, arr.Top);
    }

    // 소멸자 호출
    // Top 뿐만이 아니라 size에 대해서도 해제를 해주어야 한다.
    // 모든 동적으로 할당된 메모리에 대해서 해제하는 것을 잊지 말자.
    ~Array()
    {
      std::cout << "Destructor is called!!" << std::endl;
      DelAddr(Top);
      delete[] size;
    }

    void InitAddr(Addr *Current);
    void DelAddr(Addr *Del);
    void CopyAddr(Addr *dst, Addr *src);
    Int operator[](const int idx);
  };

  class Int
  {
  private:
    void *Data;

    int level;
    Array *array;

  public:
    // 인자에 미리 대입한 값을 디폴트 인자(Default argument)라고 한다.
    // 함수에 값을 전달하지 않는다면 해당 인자에 기본적으로 이 값들이 들어가게 된다.
    // 주의할 점은 디폴트 인자들은 함수의 가장 마지막 인자부터 '연속적으로'만 사용할 수 있다.
    // 중간 중간 디폴트 인자를 지정하지 않으면 어떤 인자에 디폴트 인자가 들어갈 지 컴파일러가 알 수 없기 때문이다.
    Int(int index, int _level = 0, void *_Data = NULL, Array *_array = NULL) : level(_level), Data(_Data), array(_array)
    {
      // 오류가 발생하였을 경우를 대비한 예외 처리 구문이다.
      // class를 구현할 때는 항상 사용자가 어떤 짓을 하더라도 프로그램이 다운되지 않도록 대처할 수 있는 코드를 짜는 것이 중요하다.
      // 아래의 코드처럼 정상적인 입력값만을 기대하기보다는 발생할 수 있는 오류값들에 대해 꼼꼼하게 대처할 수 있도록 하자.
      if (_level < 1 || index >= array->size[_level - 1])
      {
        Data = NULL;
        return;
      }

      if (level == array->dim)
      {
        // 이제 Data에 int 자료형을 저장하도록 해야 한다.
        Data = static_cast<void *>((static_cast<int *>(static_cast<Array::Addr *>(Data)->next) + index));
      }

      else
      {
        // 그렇지 않을 경우 Data에 다음 Addr을 넣어준다.
        Data = static_cast<void *>(static_cast<Array::Addr *>(static_cast<Array::Addr *>(Data)->next) + index);
      }
    }

    Int operator[](const int idx);
    Int &operator=(const int i);
    operator int();
  };

  // 임의의 N 차원 배열을 생성하기 위해서 재귀 함수를 이용할 수 있다.
  // 재귀 함수를 이용할 때는 다음의 두 가지 과정을 머리에 새기고 있으면 된다.
  // 1. 함수에서 처리하는 것, 즉 현재 단계에서 다음 단계로 넘어가는 과정은 무엇인가?
  // 2. 재귀 함수의 호출이 종료되는 조건은 무엇인가?

  // 1. 함수에서 처리하는 것, 즉 현재 단계에서 다음 단계로 넘어가는 과정은 무엇인가?
  // -> 현재 n 레벨의 Addr 배열이라면, 이 배열들의 next에는 다음 레벨인 n + 1 레벨의 Addr 배열들의 시작 주소
  //    를 각각 할당해주고, 이 각각의 배열들에 대해 다시 재귀 함수를 호출해주는 식으로 처리하면 된다.
  // 2. 재귀 함수의 호출이 종료되는 조건은 무엇인가?
  // -> 재귀 함수 호출이 종료되기 위한 조건은 현재 처리하고 있는 Addr 배열의 레벨이 (dim -1)이 되는 것이다.
  // -> Addr 배열의 레벨이 (dim - 1)이면, 이 배열의 원소들((dim - 1) 레벨을 가진 Addr 배열들)의 next에는
  //    int 배열의 시작 주소를 할당해주고 재귀 호출이 끝나게 된다.

  // 이러한 방식으로 함수를 재귀 호출하는 것은 '깊이 우선 탐색'을 하는 것과 동일하다.
  void Array::InitAddr(Addr *Current)
  {
    // Current가 NULL일 때를 대비한 예외 처리 구문
    if (!Current)
      return;

    // 재귀 함수 종료 조건
    if (Current->level == dim - 1)
    {
      Current->next = new int[size[Current->level]];
      return;
    }

    // 현재 Addr 구조체 배열들의 next에 각각 다음 Addr 구조체 배열의 시작 주소를 할당
    // 이때 다음 Addr 구조체 배열들의 레벨은 현재 Addr 구조체 배열들의 레벨 + 1 이다.
    Current->next = new Addr[size[Current->level]];

    for (int i = 0; i < size[Current->level]; i++)
    {
      (static_cast<Addr *>(Current->next))[i].level = Current->level + 1;

      InitAddr(static_cast<Addr *>(Current->next) + i);
    }
  }

  // 생성자를 만들었으므로, 소멸자도 비슷한 방식으로 만들면 된다.
  // 이때 주의할 점은 생성자는 위에서 아래로 메모리를 할당했지만
  // 소멸자는 아래에서 위로 메모리를 해제해나가야 한다는 점이다.
  // 만약 위의 메모리부터 해제한다면, 다음 메모리를 해제하려 할 때 이미 해제된 메모리에
  // 접근하려 하는 것과 같으므로 잘못된 방식이라고 할 수 있다.
  void Array::DelAddr(Addr *Current)
  {
    if (!Current)
      return;

    for (int i = 0; Current->level < dim - 1 && i < size[Current->level]; i++)
    {
      DelAddr(&static_cast<Addr *>(Current->next)[i]);
    }

    if (Current->level == dim - 1)
    {
      delete[] static_cast<int *>(Current->next);
    }

    delete[] static_cast<Addr *>(Current->next);
  }

  // 재귀 함수 형식으로 생성자를 통해 인자인 Array 인스턴스의 내용을 복사함
  void Array::CopyAddr(Addr *dst, Addr *src)
  {
    if (dst->level == dim - 1)
    {
      for (int i = 0; i < size[dst->level]; i++)
      {
        static_cast<int *>(dst->next)[i] = static_cast<int *>(src->next)[i];
      }
      return;
    }

    for (int i = 0; i < size[dst->level]; i++)
    {
      CopyAddr(&static_cast<Addr *>(dst->next)[i], &static_cast<Addr *>(src->next)[i]);
    }
  }

  Int Array::operator[](const int idx)
  {
    return Int(idx, 1, static_cast<void *>(Top), this);
  }

  Int Int::operator[](const int idx)
  {
    return Int(idx, level + 1, Data, array);
  }

  Int::operator int()
  {
    if (Data)
    {
      return *static_cast<int *>(Data);
    }

    return 0;
  }

  Int &Int::operator=(const int i)
  {
    if (Data)
    {
      *static_cast<int *>(Data) = i;
    }

    return (*this);
  }

  Int Array::Iterator::operator*()
  {
    Int start = arr->operator[](location[0]);
    for (int i = 1; i <= arr->dim - 1; i++)
    {
      start = start.operator[](location[i]);
    }
    return start;
  }
}

int main()
{
  int size[] = {2, 3, 4};
  MyArray::Array arr(3, size);

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        arr[i][j][k] = (i + 1) * (j + 1) * (k + 1);
      }
    }
  }

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        std::cout << i << " " << j << " " << k << " " << arr[i][j][k] << std::endl;
      }
    }
  }

  return 0;
}
