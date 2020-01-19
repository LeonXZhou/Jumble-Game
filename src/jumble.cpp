/*
 * 	jumble.cpp
 *
 *  Created on: November 15, 2018
 *      Author: Leon Zhou (10177892;14lz21)
 *      Implementation code for jumble puzzle game for CMPE 320 ASSIGNMENT 4
 */

#include <iostream>
#include "jumble.h"
#include <iostream>
#include <ctime>
using namespace std;

BadJumbleException::BadJumbleException(const string& s)
{
	ER = s;
}
string BadJumbleException::what()
{
	return ER;
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& J)
{
	int i, j;
	//for loops copy J.Jmatrix into this->Jmatrix
	this->Jmatrix = new charArrayPtr[J.size];
	for (i = 0; i < J.size; i ++)
	{
		this->Jmatrix[i] = new char[J.size];
	}
	for (i = 0; i < J.size; i++)
	{
			for (j = 0; j < J.size; j++)
			{
				this->Jmatrix[i][j] = J.Jmatrix[i][j];
			}
	}
	size = J.getSize();
	rowPos = J.getRowPos();
	colPos = J.getColPos();
	Direction = J.getDirection();
	Diff = J.getDiff();
	hiddenWord = J.hiddenWord;

}
JumblePuzzle::JumblePuzzle(const string &word, const string &difficulty)
{
	int seed = static_cast<int>(time(nullptr));
	srand(seed);
	int i,j;
	int d;
	bool fits;
	hiddenWord = word;
	if (word.length()<3)
	{
		throw BadJumbleException("Your word is too short");
	}
	else if (word.length()>10)
	{
		throw BadJumbleException("Your word is too big");
	}
	if (difficulty.at(0) == 'e' || difficulty.at(0) == 'E')
	{
		Diff = 2;
	}
	else if (difficulty.at(0) == 'm' || difficulty.at(0) == 'M')
	{
		Diff = 3;
	}
	else if (difficulty.at(0) == 'h' || difficulty.at(0) == 'H')
	{
		Diff = 4;
	}
	else
	{
		throw BadJumbleException("Invalid Difficulty Selection");
	}
	size = Diff * word.length();
	Jmatrix = new charArrayPtr[size];
	for (int i = 0; i <size; i ++)
	{
		Jmatrix[i] = new char[size];
	}
	//generate random letters
	for (i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			Jmatrix[i][j] = 97 + rand()%26;
		}
	}

	fits = false;
	//randomly try to find a fit for the hidden word
	while(!fits)
	{
		rowPos = rand()%size;
		colPos = rand()%size;
		d = rand()%4;
		if (d == 0 )
		{
			Direction = 'n';
			if (static_cast<int>(rowPos - word.length()) >= -1)
			{
				fits = true;
				hideWord();
			}
		}
		else if (d == 1)
		{
			Direction = 'e';
			if (static_cast<int>(colPos + word.length()) <= size)
			{
				fits = true;
				hideWord();
			}
		}
		else if (d == 2)
		{
			Direction = 's';
			if (static_cast<int>(rowPos + word.length()) <= size)
			{
				fits = true;
				hideWord();
			}
		}
		else
		{
			Direction = 'w';
			if (static_cast<int>(colPos - word.length()) >= -1)
			{
				fits = true;
				hideWord();
			}
		}
	}
}

JumblePuzzle::~JumblePuzzle()
{
	deleteJmatrix();
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& J) {
	int i,j;
	if (this != &J) {
		deleteJmatrix();
		//for loops copy J.Jmatrix into this->Jmatrix
		this->size = J.getSize();
		this->Jmatrix = new charArrayPtr[J.size];
		for (i = 0; i < J.size; i ++)
		{
			this->Jmatrix[i] = new char[J.size];
		}
		for (i = 0; i < J.size; i++)
		{
				for (j = 0; j < J.size; j++)
				{
					this->Jmatrix[i][j] = J.Jmatrix[i][j];
				}
		}
	}
	return *this;
}

charArrayPtr* JumblePuzzle::getJumble() const
{
	int i, j;
	//for loops copy J.Jmatrix into jumble
	charArrayPtr* jumble = new charArrayPtr[size];
	for (i = 0; i < size; i ++)
	{
		jumble[i] = new char[size];
	}
	for (i = 0; i < size; i++)
	{
			for (j = 0; j < size; j++)
			{
				jumble[i][j] = Jmatrix[i][j];
			}
	}
	return jumble;

}
int JumblePuzzle::getSize() const
{
	return size;
}
int JumblePuzzle::getRowPos() const
{
	return rowPos;
}
int JumblePuzzle::getColPos() const
{
	return colPos;
}
char JumblePuzzle::getDirection() const
{
	return Direction;
}
char JumblePuzzle::getDiff() const
{
	if (Diff == 2)
	{
		return 'e';
	}
	else if(Diff == 3)
	{
		return 'm';
	}
	else
	{
		return 'h';
	}

}

void JumblePuzzle::deleteJmatrix()
{
	for(int i = 0; i < this->size; i++)
		delete[] Jmatrix[i];
	delete[] Jmatrix;
	Jmatrix = nullptr;
}
void JumblePuzzle::hideWord()
{
	//hides the word based on the direction
	int i;
	if (Direction =='n')
	{
		for(i = 0; i < static_cast<int>(hiddenWord.length()); i++)
		{
			Jmatrix[rowPos - i][colPos] = hiddenWord.at(i);
		}
	}
	else if (Direction == 'e')
	{
		for(i = 0; i < static_cast<int>(hiddenWord.length()); i++)
		{
			Jmatrix[rowPos][colPos+i] = hiddenWord.at(i);
		}
	}
	else if (Direction == 's')
	{
		for(i = 0; i < static_cast<int>(hiddenWord.length()); i++)
		{
			Jmatrix[rowPos + i][colPos] = hiddenWord.at(i);
		}
	}
	else
	{
		for(i = 0; i < static_cast<int>(hiddenWord.length()); i++)
		{
			Jmatrix[rowPos][colPos-i] = hiddenWord.at(i);
		}
	}
}
