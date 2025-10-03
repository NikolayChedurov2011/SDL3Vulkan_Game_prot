#include "Game.h"
#include "SDL3_image/SDL_image.h"
#include <string>

bool Game::postInitialize() {
	int w{ 0 }, h{ 0 };
	getWindowSize(&w, &h);
	terrain = std::make_unique<Terrain>(getRenderer(), round(w / pixelRatio), round(h / pixelRatio));

	
	//std::string path{ "../spritesheet.bmp" };
	//SDL_Surface* suf = SDL_LoadBMP(path.c_str());
	//if (!suf) {
	//	std::cout << SDL_GetError() << std::endl;
	//}
	//spriteSheet = SDL_CreateTextureFromSurface(renderer, suf);
	//SDL_SetTextureBlendMode(spriteSheet, SDL_BLENDMODE_BLEND);
	//SDL_SetTextureScaleMode(spriteSheet, SDL_SCALEMODE_NEAREST);
	//SDL_DestroySurface(suf);

	//animation.frames = {
	//	{0, 0, 32, 32, 6.f},
	//	{32, 0, 32, 32, 6.f},
	//	{64, 0, 32, 32, 6.f}
	//};
	//animation.currentFrame = 0;
	//animation.timer = 0.0f;

	const char* name{ "/background.png" };
	const char* folder{ "/assets" };
	std::string path{ SDL_GetBasePath() + std::string(folder) + std::string(name)};
	bG = IMG_LoadTexture(getRenderer(), path.c_str());


	if (!bG) {
		SDL_Log(SDL_GetError());
	}
	SDL_SetTextureBlendMode(bG, SDL_BLENDMODE_BLEND);
	SDL_SetTextureScaleMode(bG, SDL_SCALEMODE_NEAREST);


	if (terrain) {
		return true;
	}

	return false;
}

void Game::update() {
	terrain->update();
}

void Game::render() {
	SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(getRenderer());

	// Render game objects here
	SDL_RenderTexture(getRenderer(), bG, nullptr, nullptr);
	terrain->draw(getRenderer());

	
	

	//animation.timer += dT;
	//std::cout << "Animation timer: " << animation.timer << std::endl;
	//std::cout << "Animation duration: " << animation.frames[animation.currentFrame].duration << std::endl;
	//if (animation.timer >= animation.frames[animation.currentFrame].duration) {
	//	animation.timer = 0;//-= animation.frames[animation.currentFrame].duration;
	//	animation.currentFrame = (animation.currentFrame + 1) % animation.frames.size();
	//}

	//SDL_FRect srcRect = {
	//	animation.frames[animation.currentFrame].x,
	//	animation.frames[animation.currentFrame].y,
	//	animation.frames[animation.currentFrame].w,
	//	animation.frames[animation.currentFrame].h
	//};
	//SDL_FRect dstRect = { 0, 0, 128, 128 };

	//SDL_RenderTexture(getRenderer(), spriteSheet, &srcRect, &dstRect);


	SDL_RenderPresent(getRenderer());
}

void Game::handleEvents(SDL_Event& event) {
	switch (event.type) {
	case SDL_EVENT_QUIT:
		setGameIsRunning(false);
		break;

	case SDL_EVENT_KEY_DOWN:
		if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
			setGameIsRunning(false);
		}
		break;

	case SDL_EVENT_KEY_UP:
		break;

	case SDL_EVENT_MOUSE_MOTION:
		break;

	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mouseDownStatus = SDL_BUTTON_LEFT;
			break;
		case SDL_BUTTON_RIGHT:
			mouseDownStatus = SDL_BUTTON_RIGHT;
			break;
		}
		break;

	case SDL_EVENT_MOUSE_BUTTON_UP:
		mouseDownStatus = 0;
		break;
	}

	// Handle other inputs
	if (mouseDownStatus) {
		float mouseX{ 0.f }, mouseY{ 0.f };
		SDL_GetMouseState(&mouseX, &mouseY);
		mouseX = (int)round(mouseX / pixelRatio);
		mouseY = (int)round(mouseY / pixelRatio);

		switch (mouseDownStatus) {
		case SDL_BUTTON_LEFT:
			terrain->addPixels(mouseX, mouseY, 4);
			break;

		case SDL_BUTTON_RIGHT:
			terrain->removePixels(mouseX, mouseY, 3);
			break;
		}
	}
}