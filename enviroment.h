#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <iostream>
#include <vector>

using namespace std;

enum TEXTURE{
    GROUND,
    ROAD,
    AIR,
    PALM,
    CAR,
    SEA,
    SAND,
    STAR,
};

enum DIRECTION{
    ZERO = 0,
    UP = 119,
    DOWN = 115,
    LEFT = 97,
    RIGHT = 100
};

class Car
{
    int x, y;
public:
    Car(): x(0), y(0) {}
    Car(int a, int b): x(a), y(b) {}
    void moveUp(){ x--; }
    void moveDown(){ x++; }
    void moveLeft(){ y--; }
    void moveRight(){ y++; }
    int getx() const { return x; }
    int gety() const { return y; }
};

class Map
{
    vector<vector<int>> background;
    vector<vector<int>> buffer;
    vector<vector<string>> screen;
    int v_length, h_length;
    int centeringPixel;
    Car playerCar;
public:
    Map() {}
    Map(int _length, int _width);
    void getControl(int control);

    bool isPlayer(int i, int j) const {return (i == playerCar.getx()) && (j == playerCar.gety() || j == playerCar.gety()+1);}
    bool isPlayerAlive() const {return background[playerCar.getx()][playerCar.gety()] == ROAD && background[playerCar.getx()][playerCar.gety()+1] == ROAD;}

    void fillBuffer();

    void Update(){
        fillBuffer();
        background = buffer;
    }

    void setScreen();
    void setScreen2();

    void printScreen();

    friend std::ostream& operator<< (std::ostream &out, const Map& M);
};

string texture(int tile);

#endif // ENVIROMENT_H
