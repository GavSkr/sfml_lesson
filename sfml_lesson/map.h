#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 19;//размер карты высота
const int WIDTH_MAP = 19;//размер карты ширина 


sf::String TileMap[HEIGHT_MAP] = {
	"sssssssssssssssssss",
	"s  0000           s",
	"s  0              s",
	"s  0000           s",
	"s     0           s",
	"s  0000           s",
	"s                 s",
	"s  0  0   000     s",
	"s  00 0  0  0     s",
	"s  0 00  0  0     s",
	"s  0  0  0000     s",
	"s  0  0  0  0     s",
	"s                 s",
	"s  0  0  0000     s",
	"s  0 0   0        s",
	"s  00    0000     s",
	"s  0 0   0        s",
	"s  0  0  0000     s",
	"sssssssssssssssssss"
};



#endif // MAP_H