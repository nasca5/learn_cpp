#include <iostream>
#include <string.h>

class Photon_Cannon {
  int hp, shield;
  int coord_x, coord_y;
  int damage;

  char* name;

  public:
    Photon_Cannon();
    Photon_Cannon(int x, int y, const char* name);
    Photon_Cannon(const Photon_Cannon& pc);
    ~Photon_Cannon();

    void show_status();
};

Photon_Cannon::Photon_Cannon() {
  std::cout << "default instructor is called!!" << std::endl;
  hp = shield = 100;
  coord_x = coord_y = 0;
  damage = 20;

  name = NULL;
}

Photon_Cannon::Photon_Cannon(int x, int y, const char* cannon_name) {
  std::cout << "instructor is called!!" << std::endl;
  hp = shield = 100;
  coord_x = x;
  coord_y = y;
  damage = 20;

  name = new char[strlen(cannon_name) + 1];
  strcpy(name, cannon_name);
}

Photon_Cannon::~Photon_Cannon() {
  std::cout << "destructor is called!!" << std::endl;
  if(name)
    delete[] name;
}

Photon_Cannon::Photon_Cannon(const Photon_Cannon& pc) {
  std::cout << "copy instructor is called!!" << std::endl;
  hp = pc.hp;
  shield = pc.shield;
  coord_x = pc.coord_x;
  coord_y = pc.coord_y;
  damage = pc.damage;
  name = new char[strlen(pc.name) + 1];
  strcpy(name, pc.name);
}

void Photon_Cannon::show_status() {
  std::cout << name << std::endl;
  std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) " << std::endl;
  std::cout << " HP : " << hp << std::endl;
}

int main() {
  Photon_Cannon pc1(2, 3, "Cannon 1");
  Photon_Cannon pc2(pc1);
  Photon_Cannon pc3 = pc2;

  pc1.show_status();
  pc2.show_status();
  pc3.show_status();
  
  return 0;
}
