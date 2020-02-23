#pragma once
#include <iostream>
#include <vector>
#include "Framework/GameObject.h"
#include "Framework/Vector.h"

class Ball : public GameObject {
	sf::RenderWindow* w;

	sf::Texture txt;
	sf::Sprite spr;

	sf::Vector2f step_velocity;
	const sf::Vector2f gravity = sf::Vector2f(0, 40.f);
	const float speed = 10.f;

	bool is_jumping = false;
	bool is_on_ground = false;
	sf::Vector2f jumpForce = sf::Vector2f(0, -45.f) * speed;

	std::vector<sf::Vector2f> targets;
	bool move_toward_targets = false;

public:
	Ball() {
		if (!txt.loadFromFile("gfx/Beach_Ball.png")) {
			std::cout << "Failed to load texture\n";
		}
		spr.setTexture(txt);
		spr.setScale(0.05f, 0.05f);
		//targets.push_back(sf::Vector2f(10.f, 10.f));
	}

	void setWindow(sf::RenderWindow* win) { w = win; }

	void handleInput(float dt) override;
	void update(float dt) override;
	void draw();

	void moveToTargets(float dt);
};

