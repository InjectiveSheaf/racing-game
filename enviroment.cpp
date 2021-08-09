#include "enviroment.h"
#include <cmath>

string texture(int tile){
    switch (tile) {
    case CAR:
        return "\033[1;31;40m▓\033[0m";
        break;
    case GROUND:
        return "\033[1;32;40m▓\033[0m";
    break;
    case ROAD:
        return "\033[1;30;40m▓\033[0m";
    break;
    case PALM:
        return "\033[1;33;42m░\033[0m";
    break;
    case SEA:
        return "\033[1;34;40m▓\033[0m";
    break;
    case SAND:
        return "\033[1;33;40m▓\033[0m";
    break;
    case AIR:
        return "\033[1;35;45m▓\033[0m";
    break;
    case STAR:
        return "\033[1;37;47m▓\033[0m";
    break;
    default:
        return " ";
    break;
    }
}

Map::Map(int _length, int _width){
    screen =  vector<vector<string>>(30, vector<string>(80, " "));
    v_length = _length;
    h_length = _width;
    background = vector<vector<int>>(v_length, vector<int>(h_length, GROUND));
    buffer = background;

    for(int i = 0; i < v_length; i++){
        for(int j = h_length / 2 + 4; j < h_length; j++)
            background[i][j] = SEA;

        for(int j = h_length / 2 - 2; j <= h_length / 2 + 2; j++)
            background[i][j] = ROAD;

        background[i][h_length / 2 + 3] = SAND;
    }

    playerCar = Car(v_length / 4, h_length / 2);
    centeringPixel = h_length / 2;
}

void Map::getControl(int control){
    switch (control) {
    case UP:
        if(playerCar.getx() > 1) playerCar.moveUp();
        break;
    case DOWN:
        if(playerCar.getx() < v_length/2 + 3) playerCar.moveDown();
        break;
    case LEFT:
        if(playerCar.gety() > 0) playerCar.moveLeft();
        break;
    case RIGHT:
        if(playerCar.gety() < h_length - 1) playerCar.moveRight();
        break;
    }
}

void Map::fillBuffer(){
    if (centeringPixel < h_length - 2 && centeringPixel > 2) centeringPixel += rand() % 3 - 1;
    if (centeringPixel >= h_length - 2) centeringPixel -= rand() % 2;
    if (centeringPixel <= 2) centeringPixel += rand() % 2;

    for (int i = 0; i < h_length; i++){
        if (i > centeringPixel - 3 && i < centeringPixel + 3) buffer[0][i] = ROAD;
        else if (rand() % 80 == 1 && i < centeringPixel - 3) buffer[0][i] = PALM;
        else if (i > centeringPixel + 3) buffer[0][i] = SEA;
        else if (i == centeringPixel + 3) buffer[0][i] = SAND;
        else buffer[0][i] = GROUND;
    }

    for (int i = 0; i < v_length-1; i++)
        for (int j = 0; j < h_length; j++)
            buffer[i+1] = background[i];
}

void Map::setScreen(){
    int a,b;
    for(size_t i = 0; i < screen.size(); i++){
        for(size_t j = 0; j < screen[0].size(); j++){
            a = i/2;
            b = j/6;
            !isPlayer(a,b) ? screen[i][j] = texture(background[a][b]) : screen[i][j] = texture(CAR);
        }
    }
}

void Map::setScreen2(){
    int a,b;
    for(size_t i = 0; i < screen.size(); i++){
        for(size_t j = 0; j < screen[0].size(); j++){
            a = 18 - 1/(i+1);
            b = j/6;
            !isPlayer(a,b) ? screen[i][j] = texture(background[a][b]) : screen[i][j] = texture(CAR);
        }
    }
}

void Map::printScreen(){
    setScreen();
    for(size_t i = 0; i < screen.size()/2; i++){
        for(size_t j = 0; j < screen[0].size(); j++)
            cout << screen[i][j];
        cout << endl;
    }
}

std::ostream& operator<< (std::ostream &out, const Map& M){
    cout << "Car:" << M.playerCar.getx() << ", " << M.playerCar.gety() << endl;
    for(int i = 0; i < M.v_length; i++){
        for(int j = 0; j < M.h_length; j++)
          !M.isPlayer(i,j) ? out << texture(M.background[i][j]) : out << texture(CAR);
        out << endl;
    }
    return out;
}
