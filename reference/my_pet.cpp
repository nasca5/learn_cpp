#include <iostream>
#include <vector>

typedef struct Animal {
  char name[30];
  int age, health, food, clean;
}Animal;

void create_animal(Animal* animal) {
  animal->food = 50;
  animal->clean = 50;
  animal->health = 100;
  std::cout << "what's the name? : " << std::endl;
  std::cin >> animal->name;
  std::cout << "how old is animal? : " << std::endl;
  std::cin >> animal->age;
  std::cout << "food : " << animal->food << std::endl;
  std::cout << "clean : " << animal->clean << std::endl;
  std::cout << "health : " << animal->health << std::endl;
};
void feed_animal(Animal* animal) {
  animal->health += 10;
  animal->food -= 5;
};
void show_stat(Animal* animal) {
  std::cout << "******stat******" << std::endl;
  std::cout << "name : " << animal->name << std::endl;
  std::cout << "age : " << animal->age << std::endl;
  std::cout << "food : " << animal->food << std::endl;
  std::cout << "health : " << animal->health << std::endl;
  std::cout << "clean : " << animal->clean << std::endl;
};

void one_day_passed(Animal* animal) {
  animal->health -= 10;
  animal->clean -= 10;
  animal->food -= 10;
}

int main() {
  Animal* list[10];
  int choose;
  int animal_num = 0;

  while(true) {
    std::cout << "choose" << std::endl;
    std::cout << "1 : " << "new animal" << std::endl;
    std::cout << "2 : " << "feed" << std::endl;
    std::cout << "3 : " << "stat" << std::endl;
    std::cout << "4 : " << "quit" << std::endl;
    std::cin >> choose; 

    switch (choose) {
      int feed;
      case 1:
        list[animal_num] = new Animal;
        create_animal(list[animal_num]);
        animal_num++;
        break;
      case 2:
        std::cout << "what animal you want to feed? : " << std::endl;
        std::cin >> feed;
        if(feed <= animal_num) {
          feed_animal(list[feed]);
        }
        break;
      case 3:
        std::cout << "what animal you want to see? : " << std::endl;
        std::cin >> feed;
        if(feed <= animal_num) {
          show_stat(list[feed]);
        }
        break;
      case 4:
        exit(1);
      default:
        std::cout << "choose 1~3" << std::endl;
        break;
    }
    for(int i = 0; i < animal_num; i++) {
      if(list[i]->health <= 0) {
        std::cout << list[i]->name << "is dead.." << std::endl;
      }
      one_day_passed(list[i]);
    }
  }

  for(int i = 0; i != animal_num; i++) {
    delete list[i];
  }
  return 0;
}