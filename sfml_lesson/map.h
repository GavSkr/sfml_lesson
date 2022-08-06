#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 19;//размер карты высота
const int WIDTH_MAP = 19;//размер карты ширина 


sf::String TileMap[HEIGHT_MAP] = {
	"sssssssssssssssssss",
	"s  000000         s",
	"s   s   0         s",
	"s       0         s",
	"s    0000         s",
	"s    00000        s",
	"s       00        s",
	"s       00        s",
	"s       00000     s",
	"s       00000     s",
	"s                 s",
	"s              s  s",
	"s                 s",
	"s                 s",
	"s                 s",
	"s                 s",
	"s                 s",
	"s                 s",
	"sssssssssssssssssss"
};



#endif // MAP_H