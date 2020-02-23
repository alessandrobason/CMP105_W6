#include "Ball.h"

void Ball::update(float dt) {
	moveToTargets(dt);
	sf::Vector2f pos = step_velocity * dt + 0.5f*gravity*dt*dt;
	step_velocity += gravity * speed * dt;
	//spr.setPosition(spr.getPosition() + pos);
	spr.move(pos);
	
	if (spr.getPosition().y + spr.getGlobalBounds().height >= w->getSize().y) {
		spr.setPosition(spr.getPosition().x, w->getSize().y- spr.getGlobalBounds().height);
		step_velocity = sf::Vector2f(0, 0);
		is_on_ground = true;
	}
	else {
		is_on_ground = false;
	}
}

void Ball::moveToTargets(float dt) {
	if (targets.size() == 0) return;
	//std::cout << targets[0].x << "\n";
	//int back = targets.size() - 1;
	sf::Vector2f current_position = spr.getPosition() + sf::Vector2f(spr.getGlobalBounds().width/2, spr.getGlobalBounds().height/2);
	sf::Vector2f direction = *targets.begin() - current_position;
	direction = Vector::normalise(direction);
	step_velocity = direction * speed * 50.f;

	if (Vector::magnitude(*targets.begin() - current_position) < 10.f) {
		targets.erase(targets.begin());
	}
	
}

void Ball::handleInput(float dt) {
	if (input->isKeyDown(sf::Keyboard::Space)) {
		if (is_on_ground) {
			step_velocity = jumpForce;
		}
	}
	if (input->isMouseLDown() && input->isMouseRDown()) {
		if (input->getMouseY() + spr.getGlobalBounds().height < w->getSize().y) {
			spr.setPosition(input->getMouseX(), input->getMouseY());
		}
		else {
			spr.setPosition(input->getMouseX(), w->getSize().y - spr.getGlobalBounds().height);
		}
	}

	if (input->isMouseLDown()) {
		targets.push_back(sf::Vector2f(input->getMouseX(), input->getMouseY()));
	}

	if (input->isKeyDown(sf::Keyboard::Q)) {
		move_toward_targets = true;
	}
	else {
		move_toward_targets = false;
	}
}

void Ball::draw() {
	w->draw(spr);
	sf::VertexArray v;
	v.setPrimitiveType(sf::PrimitiveType::LineStrip);
	for (size_t i = 0; i < targets.size(); i++) {
		sf::RectangleShape r;
		r.setSize(sf::Vector2f(5.f, 5.f));
		r.setPosition( targets[i] - sf::Vector2f(2.5f, 2.5f));
		r.setFillColor(sf::Color::Transparent);
		r.setOutlineColor(sf::Color::Red);
		r.setOutlineThickness(1.f);
		sf::Vertex vertex;
		vertex.position = targets[i];
		v.append(vertex);
	}
	w->draw(v);
}