#include <iostream>

class Animal {
  private:
    int food, weight;
  
  public:
    void set_animal(int _food, int _weight) {
      food = _food;
      weight = _weight;
    }

    void increase_animal(int inc) {
      food += inc;
      weight += (inc / 3);
    }

    void view_stat() {
      std::cout << "animal's food     : " << food << std::endl;
      std::cout << "animal's weight   : " << weight << std::endl;
    }
};

int main() {
  Animal animal;

  animal.set_animal(100, 50);
  animal.increase_animal(30);

  animal.view_stat();
  return 0;
}