#include "Terrain.h"
#include <iostream>

Terrain::Terrain(SDL_Renderer* renderer, int setWidth, int setHeight) : width(setWidth), height(setHeight) {
	screenTextue = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	SDL_SetTextureBlendMode(screenTextue, SDL_BLENDMODE_BLEND);
	SDL_SetTextureScaleMode(screenTextue, SDL_SCALEMODE_NEAREST);

	//colorDataWorldParticlesSize = (size_t)width * height * 4;
	//colorDataWorldParticles = new unsigned char[colorDataWorldParticlesSize];
	//memset(colorDataWorldParticles, 0, colorDataWorldParticlesSize);

	pixelBuffer = new uint32_t[(size_t)width * height];
	memset(pixelBuffer, 0, width * height * sizeof(uint32_t));
}

Terrain::~Terrain() {
	if (screenTextue) {
		SDL_DestroyTexture(screenTextue);
		screenTextue = nullptr;
	}

	if (colorDataWorldParticles) {
		delete[] colorDataWorldParticles;
		colorDataWorldParticles = nullptr;
	}
}

void Terrain::draw(SDL_Renderer* renderer) {
	void* pixels{};
	int pitch{};

	SDL_LockTexture(screenTextue, nullptr, &pixels, &pitch);
	//memcpy(pixels, colorDataWorldParticles, colorDataWorldParticlesSize);

	for (int y = 0; y < height; ++y) {
		void* dstRow = (uint8_t*)pixels + y * pitch;
		memcpy(dstRow, pixelBuffer + y * width, width * sizeof(uint32_t));
	}

	SDL_UnlockTexture(screenTextue);

	SDL_RenderTexture(renderer, screenTextue, nullptr, nullptr);





	//SDL_Rect dstRect{ 0, 0, windowW, windowH };
   // SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
}

void Terrain::addPixel(int posX, int posY) {
	//SDL_Color color{ 70, 150, 150, 255 };
	//int index{ (posX + posY * width) * 4 };
	//std::cout << "Draw at index: " << index << std::endl;
	//memcpy(colorDataWorldParticles + index, &color, 4);


	if (posX < 0 || posY < 0 || posX >= width || posY >= height) {
		return;
	}

	uint32_t packed = (255 << 24) | (150 << 16) | (150 << 8) | 70; // ABGR8888
	//pixelBuffer[posX + posY * width] = packed;
	memcpy(pixelBuffer + (posX + posY * width), &packed, sizeof(packed));
}

void Terrain::removePixel(int posX, int posY) {
	if (posX < 0 || posY < 0 || posX >= width || posY >= height) {
		return;
	}

	uint32_t packed = (0 << 24); // ABGR8888
	pixelBuffer[posX + posY * width] = packed;
}

void Terrain::addPixels(int posX, int posY, int size) {
	for (int i{ -size }; i <= size; ++i) {
		for (int k{ -size }; k <= size; ++k) {
			if (isSpotInBoundsAndEmpty(posX + i, posY + k) && ((i * i) + (k * k) <= size * size)) {
				addPixel(posX + i, posY + k);
			}
		}
	}
}

void Terrain::removePixels(int posX, int posY, int size) {
	for (int i{ -size }; i <= size; ++i) {
		for (int k{ -size }; k <= size; ++k) {
			if (isSpotInBounds(posX + i, posY + k) && ((i * i) + (k * k) <= size * size)) {
				removePixel(posX + i, posY + k);
			}
		}
	}
}

void Terrain::update() {
	for (int h{ height - 1 }; h > -1; --h) {
		for (int w{ 0 }; w < width; ++w) {
			if (!isSpotEmpty(w, h)) {
				if (isSpotInBoundsAndEmpty(w, h + 1)) {
					movePixel(w, h, w, h + 1);
				}
			}
		}
	}
}

void Terrain::movePixel(int oldPosX, int oldPosY, int newPosX, int newPosY) {
	//pixelBuffer[newPosX + newPosY * width] = pixelBuffer[oldPosX + oldPosY * width];
	//removePixel(oldPosX, oldPosY);
	memmove(pixelBuffer + (newPosX + newPosY * width), pixelBuffer + (oldPosX + oldPosY * width), sizeof(uint32_t));
	removePixel(oldPosX, oldPosY);
}

bool Terrain::isSpotEmpty(int posX, int posY) {
	return (pixelBuffer[(posX + posY * width)] >> 24) == 0;
}

bool Terrain::isSpotInBounds(int posX, int posY)
{
	return (posX >= 0 && posX < width && posY >= 0 && posY < height);
}

bool Terrain::isSpotInBoundsAndEmpty(int posX, int posY)
{
	return (isSpotInBounds(posX, posY) && isSpotEmpty(posX, posY));
}
