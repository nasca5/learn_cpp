// 요구 사항 분석 : 
// Date 클래스 : 년, 월, 일 변수와 SetDate 메소드, AddDay 메소드, AddMonth 메소드, AddYear 메소드, ShowDate 메소드를 가진다.
// year : 년도에 대한 정보를 담고 있다.
// month : 월에 대한 정보를 담고 있다. 1 ~ 12까지 있다.
// day : 날짜에 대한 정보를 담고 있다. 1 ~ 31까지 있다.
// 윤년 여부에 따라 2월의 마지막 날짜가 달라진다.
// SetDate() : 만들어진 객체의 년, 월, 일에 대한 정보를 초기화한다.
// AddDay() : 매개 변수로 전해진 숫자만큼 날짜를 더한다. 해당 월의 최대 날짜보다 높으면 month 변수에 1을 더하고
// day를 그에 맞게 다시 할당한다.
// AddMonth() : 매개 변수로 전해진 숫자만큼 월을 더한다. month가 12보다 높아지면 year을 1올리고
// month를 그에 맞게 재할당한다.
// AddYear() : 매개 변수로 전해진 숫자만큼 년도를 더한다.
// ShowDate() : 객체에 있는 년, 월, 일의 정보를 출력한다.

// 설계 :
// 
#include <iostream>

class Date {
  int year, month, day;

  public:
  // 생성자 정의
  Date(int _year, int _month, int _day) {
    year = _year;
    month = _month;
    day = _day;
  }

  // 디폴트 생성자 정의
  Date() {
    year = 2015;
    month = 3;
    day = 15;
  }

  void SetDate(int _year, int _month, int _day);
  void AddDay(int inc);
  void AddMonth(int inc);
  void AddYear(int inc);

  void ShowDate();
};

void Date::SetDate(int _year, int _month, int _day) {
  year = _year;
  month = _month;
  day = _day;
}

void Date::AddDay(int inc) {
  int last_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if((day += inc) <= last_days[month - 1]) {
    ;
  }
  else {
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
      last_days[1] = 29;
    }
    day -= last_days[month - 1];
    AddMonth(1);
    AddDay(0);
  }
}

void Date::AddMonth(int inc) {
  if((month += inc) <= 12) {
    ;
  }
  else {
    AddYear(1);
    month -= 12;
    AddMonth(0);
  }
}

void Date::AddYear(int inc) {
  year += inc;
}

void Date::ShowDate() {
  std::cout << year << "/" << month << "/" << day << std::endl;
}

int main() {
  Date date;
  Date date2(2015, 3, 22);
  Date date3;
  date3.SetDate(2012, 10, 24);
  // date.AddDay(359);
  date.ShowDate();
  date2.ShowDate();
  date3.ShowDate();
  
  return 0;
}
