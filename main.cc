#include <iostream>
#include "cpu.hpp"
#include "bus.hpp"
// #include <SDL.h>

using namespace std;

int main(int argc, char* argv[]){

//    SDL_Init(SDL_INIT_EVERYTHING);
//
//    SDL_Window* window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
//
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//
//    SDL_RenderClear(renderer);
//
//    SDL_RenderPresent(renderer);
//
//    SDL_Delay(3000);
//
//    SDL_DestroyWindow(window);
//    SDL_DestroyRenderer(renderer);
//    SDL_Quit();
    
    Bus bus;
    CPU cpu = CPU(bus);
    // CPU cpu2 = CPU(bus);
    if(!cpu.setup())
        return -1;

    cpu.reset();


    cpu.PC = 0x0C000;
    cpu.run();
    uint8_t lower = cpu.ram[0x2];
    uint8_t upper = cpu.ram[0x3];
    cout << "0x2h: " << hex << uppercase << (int)lower << endl;
    cout << "0x3h: " << hex << uppercase << (int)upper << endl;


    return 0;
}