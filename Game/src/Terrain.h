#pragma once
#include "SDL3/SDL.h"
#include <memory>

class Terrain {
private:


public:
	Terrain(SDL_Renderer* renderer, int setWidth, int setHeight);
	~Terrain();
	void draw(SDL_Renderer* renderer);
	void addPixels(int posX, int posY, int size);
	void removePixels(int posX, int posY, int size);
	void update();

private:
	int width, height;
	SDL_Texture* screenTextue{ nullptr };

	size_t colorDataWorldParticlesSize{ 0 };
	unsigned char* colorDataWorldParticles{ nullptr };
	uint32_t* pixelBuffer{ nullptr };

	void addPixel(int posX, int posY);
	void removePixel(int posX, int posY);
	void movePixel(int oldPosX, int oldPosY, int newPosX, int newPosY);
	bool isSpotEmpty(int posX, int posY);
	bool isSpotInBounds(int posX, int posY);
	bool isSpotInBoundsAndEmpty(int posX, int posY);
};