#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;

sf::Clock deltaClock;

void DrawPixel(int x, int y, sf::Color color, sf::RenderWindow& window) {
	sf::RectangleShape pixel(sf::Vector2f(1, 1));
	pixel.setOutlineThickness((float)0.2);
	pixel.setOutlineColor(color);
	pixel.setFillColor(color);
	pixel.setPosition((float)x, (float)y);

	window.draw(pixel);
}

void DrawLine(sf::Vector2f A, sf::Vector2f B, float thickness, sf::Color color, sf::RenderWindow& window) {
	sf::Vertex vertices[4];

	sf::Vector2f direction = B - A;
	sf::Vector2f unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
	sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

	sf::Vector2f offset = (thickness / 2.f)*unitPerpendicular;

	vertices[0].position = A + offset;
	vertices[1].position = B + offset;
	vertices[2].position = B - offset;
	vertices[3].position = A - offset;

	for (int i = 0; i<4; ++i)
		vertices[i].color = color;
	window.draw(vertices, 4, sf::Quads);
}

namespace ImGui {
	namespace SFML {
		void Start(sf::RenderWindow& window) {
			ImGui::SFML::Update(window, deltaClock.restart());
		}
	}
}
