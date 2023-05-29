#include <iostream>
#include <cmath>

class Point {
public:
  int x, y;

  Point(int pos_x, int pos_y) {
    x = pos_x;
    y = pos_y;
  }
};

class Geometry {
  Point** point_array;
  int num_points;

public:
  Geometry() {
    num_points = 0;
  } 

  void AddPoint(int x, int y) {
    point_array[num_points++] = new Point(x, y);
  }

  // 모든 점들 간의 거리를 출력하는 함수
  void PrintDistance() {
    int disX, disY;
    for(int i = 0; i < num_points - 1; i++) {
      disX = std::pow((*point_array[i + 1]).x - (*point_array[i]).x, 2);
      disY = std::pow((*point_array[i + 1]).y - (*point_array[i]).y, 2);
      std::cout << sqrt(disX + disY) << std::endl;
    }
  }

  void PrintNumMeets() {
    double slope;
    int rootX, rootY;
    int x1, y1, x2, y2;
    int cnt = 0;
    for(int i = 0; i != num_points - 1; i++) {
      rootX = (*point_array[i]).x;
      rootY = (*point_array[i]).y;
      for(int k = i + 1; k != num_points; k++) {
        for(int j = i; j < num_points - 1; j++) {
          x1 = (*point_array[j]).x;
          y1 = (*point_array[j]).y;
          for(int r = k; r < num_points; r++) {
            if((j == i && r == k) || j >= r) {
              continue;
            }

            x2 = (*point_array[r]).x;
            y2 = (*point_array[r]).y;

            if((*point_array[k]).x - (*point_array[i]).x != 0) {
              slope = (double)((*point_array[k]).y - (*point_array[i]).y) / ((*point_array[k]).x - (*point_array[i]).x);
            }
            else {
              slope = 1;
              y1 = rootY;
              y2 = rootY;
            }

            if((slope*x1 - slope*rootX + rootY - y1)*(slope*x2 - slope*rootX + rootY - y2) <= 0) {
              cnt++;
            }
          }
        }
      }
    }
    std::cout << "meet : " << cnt << std::endl;
  }

  // ShowPos 함수를 public으로 추가
  void ShowPos(int idx) {
    std::cout << (*point_array[idx]).x << std::endl;
    std::cout << (*point_array[idx]).y << std::endl;
  }
};

int main() {
  Geometry g;

  g.AddPoint(2, 8);
  // g.AddPoint(2, 4);
  g.AddPoint(6, 6);
  g.AddPoint(6, 3);

  // g.ShowPos(0);
  // g.ShowPos(2);
  // g.ShowPos(1);

  g.PrintDistance();
  g.PrintNumMeets();
  return 0;
}
