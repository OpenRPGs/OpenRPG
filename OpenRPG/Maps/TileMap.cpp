﻿#include "stdafx.h"
#include "TileMap.h"


void TileMap::clear()
{
	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < maxSize.x; x++)
	{
		for (size_t y = 0; y < maxSize.y; y++)
		{
			this->map[x].push_back(std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
		throw "TileMap load failed";
}


TileMap::~TileMap()
{
	this->clear();
}

const sf::Texture * TileMap::getTileSheet() const
{

	return &this->tileSheet;
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget & target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto *z : y)
			{
				if (z != nullptr)
					z->render(target);
			}
		}
	}
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect)
{
	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL) //비어있을때만 타일을 삽입한다.
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect);
			std::cout << "DEBUG: 타일이 추가되었습니다!" << std::endl;
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL) //비어있을때만 타일을 삽입한다.
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
			std::cout << "DEBUG: 타일이 삭제되었습니다!" << std::endl;
		}
	}
}

void TileMap::saveToFile(const std::string fileName)
{
	//타일맵을 텍스트파일로 저장한다.
	/*
	Format:
	Basic:
	Size x y
	girdSize
	layers
	texture file

	All tiles:
	gridPos x y layers
	Texture rect x y 
	collision 
	type
	*/

	std::ofstream out_file;

	out_file.open(fileName);

	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this->maxSize.y << '\n'
			<< this->gridSizeU << '\n'
			<< this->layers << '\n'
			<< this->textureFile << '\n';


		for (size_t x = 0; x < maxSize.x; x++)
		{
			for (size_t y = 0; y < maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if (this->map[x][y][z])
						out_file << x << " " << y << " " << z << " " << 
						this->map[x][y][z]->getAsString() 
						<< " ";//남은 공간은 저장하지않도록 처리할예정.
				}
			}
		}

	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILNAME: " << fileName << std::endl;
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string fileName)
{
	std::ifstream in_file;

	in_file.open(fileName);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;



		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
		for (size_t x = 0; x < maxSize.x; x++)
		{
			for (size_t y = 0; y < maxSize.y; y++)
			{
				this->map[x].push_back(std::vector<Tile*>());
				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			throw "TileMap load failed";

		//모든 타일 불러오기
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(
				x, y,
				this->gridSizeF, 
				this->tileSheet, 
				sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
				collision,
				type);
		}

	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILNAME: " << fileName << std::endl;
	}

	in_file.close();
}
