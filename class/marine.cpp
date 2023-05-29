#include <iostream>
#include <string.h>

class Marine {
  static int total_marine_num;
  
  int hp; // marine_hp
  int coord_x, coord_y; // marine_pos
  bool is_dead; // check_dead
  
  const int default_damage; // marine_attack_damage

  char* name; // marine_name

  public:
    Marine();
    Marine(int x, int y, int default_damage);
    Marine(int x, int y, const char* marine_name);
    ~Marine();
    int attack() const;
    Marine& be_attacked(int damage_earn);
    void move(int x, int y);

    void show_status();
    static void show_total_marine();
};

int Marine::total_marine_num = 0;
void Marine::show_total_marine() {
  std::cout << "Total Marine!! : " << total_marine_num << std::endl;
}
Marine::Marine() : hp(50) , coord_x(0), coord_y(0), default_damage(5), is_dead(false) {
  total_marine_num++;
}

Marine::Marine(int x, int y, int default_damage) : hp(50) , coord_x(x), coord_y(y), default_damage(default_damage), is_dead(false) {
  total_marine_num++;
}

Marine::Marine(int x, int y, const char* marine_name) : hp(50), coord_x(x), coord_y(y), default_damage(5) {
  name = new char[strlen(marine_name) + 1];
  strcpy(name, marine_name);
  total_marine_num++;
}

Marine::~Marine() {
  total_marine_num--;
}

int Marine::attack() const {
  return default_damage;
}

Marine& Marine::be_attacked(int damage_earn) {
  this->hp -= damage_earn;
  if(this->hp <= 0) {
    this->is_dead = true;
  }

  return* this;
}

void Marine::move(int x, int y) {
  coord_x = x;
  coord_y = y;
}

void Marine::show_status() {
  std::cout << " *** Marine *** " << std::endl;
  std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
  std::cout << "HP : " << hp << std::endl;
  show_total_marine();
}

void create_marine() {
  Marine marine3(10, 10, 4);
  // marine3.show_status();
  Marine::show_total_marine();
}

int main() {
  // Marine* marines[100];

  // marines[0] = new Marine(2, 3, 10);
  // (*marines[0]).show_status();
  // marines[1] = new Marine(3, 5, 10);
  // (*marines[1]).show_status();
  
  Marine marine1(3, 4, 10);
  // marine1.show_status();
  Marine::show_total_marine();
  Marine marine2(8, 3, 10);
  // marine2.show_status();
  Marine::show_total_marine();
  create_marine();
  Marine::show_total_marine();
  
  std::cout << "Marine2 attacked twice Marine1!!" << std::endl;

  // (*marines[0]).be_attacked((*marines[1]).attack());
  marine1.be_attacked(marine2.attack()).be_attacked(marine2.attack()); 
  // (*marines[0]).show_status();
  // (*marines[1]).show_status();
  marine1.show_status();
  marine2.show_status();

  // delete marines[0];
  // delete marines[1];

  return 0;
}
