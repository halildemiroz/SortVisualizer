#include <SDL.h>

#include <iostream>
#include <random>
#include <algorithm>
#include <ranges>

void draw_state(std::vector<int>& v, SDL_Renderer* renderer, unsigned int red, unsigned int blue) {

	unsigned int index = 0;

	for (int i : v) {
		// eğer index kırmızıysa o bloğu kırmızıya boyuyor diğerleri için de aynısı geçerli
		if(index == red)
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		else if(index == blue)
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		else 
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, index, 99, index, i);
		index += 1;
	}

}


int main(int argc, char* argv[]) {

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_CreateWindowAndRenderer(100*5, 5*100, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_RenderSetScale(renderer, 5, 5);

	//Random sayı oluşturma 1-99 arası
	//
	std::random_device rd;
	std::uniform_int_distribution d(1, 99);
	std::vector<int> v;

	// Oluşan random numaraları vector içine atma
	//
	for (int a = 0; a < 100; a++) {
		v.push_back(d(rd));
	}

	//Sorting algorithm
	//
	for (int i = 0; i < v.size(); i++) {

		for (int j = i; j < v.size(); j++) {

			if (v[j] < v[i]) {

				std::swap(v[j], v[i]);
			
			}
			// ekranı temizleme ve siyah yapma
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			// vectorümüzü renderlıyoruz
			draw_state(v, renderer, i, j);
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
		}
	}


	return 0;
}
