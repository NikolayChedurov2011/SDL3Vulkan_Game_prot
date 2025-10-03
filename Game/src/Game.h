#pragma once
#include "Game_Base.h"
#include <memory>
#include <vector>

#include "Terrain.h"

class Game : public Game_Base {
private:
	/*struct Frame {
		int x, y, w, h;
		float duration;
	};

	struct Animation {
		std::vector<Frame> frames;
		int currentFrame;
		float timer;
	};
	SDL_Texture* spriteSheet{nullptr};
	Animation animation;*/
	SDL_Texture* bG{ nullptr };

public:
	virtual bool postInitialize() override;
	virtual void handleEvents(SDL_Event& event) override;
	virtual void update() override;
	virtual void render() override;

private:
	int mouseDownStatus{ 0 };
	const float pixelRatio{13.f};
	std::unique_ptr<Terrain> terrain{ nullptr };



	SDL_PixelFormatDetails* packFormat{ nullptr };
	uint32_t colorBuffer[];
};