#pragma once
enum TileType {
	Grass,    //0
	Rock,     //1
	Cheese,   //2
	Water,    //3
	Wall,     //4
	NumTypes, //5
};
const int MAP_WIDTH = 6;
const int MAP_HEIGHT = 6;
const unsigned char TILES[MAP_WIDTH * MAP_HEIGHT] = {
	4, 1, 1, 3, 3, 1, 
	4, 1, 1, 2, 2, 1, 
	4, 1, 1, 2, 2, 1, 
	4, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1,
	0, 0, 3, 3, 3, 3
};