#include <time.h>
#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include "./getch.h"
#include "./enviroment.h"

using namespace std;

char input;
bool isMuscicOn;
bool isSettingsOn;

void clearScreen(){
    system(" printf \"\033c\" ");
}

string colorSwitch(char color){
    if(color == 's') return texture(AIR);
    if(color == 'r') return texture(CAR);
    if(color == 'g') return texture(SEA);
    else return texture(STAR);
}

void printPlanet(){
    ifstream title("/home/lucretiaxd/Coding/QT Projects/racinggame/saturn.txt");
    string titleLine;
    while(getline(title,titleLine)){
        for(size_t i = 0; i < titleLine.size(); i++) cout << colorSwitch(titleLine[i]);
        cout << endl;
    }
    title.close();
}

void printSettings(Map* SMap){
    cout << "Music: " << isMuscicOn << endl;
    if(isMuscicOn == true) cout << "true"; else cout << "false";
    cout << endl << "To turn on/off the music press \"m\"." << endl;
    cout << *SMap << endl;
}

void getControl(Map* SMap){
    while(input != 'e' && SMap->isPlayerAlive()){
        input = getchar();
        SMap->getControl(input);
        if(input == 'c'){
            isSettingsOn^=1;
            input = ' ';
        }
        if(input == 'm'){
            isMuscicOn^=1;
            input = ' ';
        }
    }
}

void mapUpdate(Map* SMap){
    int i = 0;
    while(input != 'e' && SMap->isPlayerAlive()){
        clearScreen();
        cout << "Distance: " << i << endl;
        SMap->Update();
        i++;
        printPlanet();
        SMap->printScreen();
        if(isSettingsOn) printSettings(SMap);
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    cout << "You lose :)" << endl;
}

class MPlayer{
public:
    void playA(){
        system("ffplay -f lavfi -i \"sine=frequency=440:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playB(){
        system("ffplay -f lavfi -i \"sine=frequency=493:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playC(){
        system("ffplay -f lavfi -i \"sine=frequency=523:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playD(){
        system("ffplay -f lavfi -i \"sine=frequency=587:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playE(){
        system("ffplay -f lavfi -i \"sine=frequency=659:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playF(){
        system("ffplay -f lavfi -i \"sine=frequency=698:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playG(){
        system("ffplay -f lavfi -i \"sine=frequency=783:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playA2(){
        system("ffplay -f lavfi -i \"sine=frequency=880:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playB2(){
        system("ffplay -f lavfi -i \"sine=frequency=987:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playC2(){
        system("ffplay -f lavfi -i \"sine=frequency=1046:duration=0.5\" -autoexit -nodisp -loglevel panic");
    }
    void playPause(int length){
        this_thread::sleep_for(chrono::milliseconds(length));
    }
};

void musicPlayer(Map* SMap){
    MPlayer mp;
    while(input != 'e' && SMap->isPlayerAlive()){
        if(isMuscicOn == true){
            if(isMuscicOn == false || input == 'e') continue;
        mp.playE();
        mp.playA2();
        mp.playC2();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playE();
        mp.playA2();
        mp.playC2();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playE();
        mp.playA2();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playD();
        mp.playG();
        mp.playB2();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playD();
        mp.playG();
        mp.playB2();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playD();
        mp.playG();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playC();
        mp.playF();
        mp.playA2();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playC();
        mp.playF();
        mp.playA2();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playC();
        mp.playF();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playD();
        mp.playF();
        mp.playA2();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playD();
        mp.playF();
        mp.playA2();
            if(isMuscicOn == false || input == 'e') continue;
        mp.playD();
        mp.playF();
            if(isMuscicOn == false || input == 'e') continue;
        }
    }
}

int main()
{
    time_t t = time(nullptr);
    srand(t);
    isMuscicOn = 1;
    isSettingsOn = 0;
    Map* SMap = new Map(20, 13);

    cout << "Press \"C\" to see the settings." << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));

    set_keypress();

    thread control(getControl, SMap);
    thread render(mapUpdate, SMap);
    thread music(musicPlayer, SMap);
    render.join();
    control.join();
    music.join();

    reset_keypress();
    return 0;
}
