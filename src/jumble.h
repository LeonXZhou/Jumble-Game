/*
 * 	jumble.h
 *
 *  Created on: November 15, 2018
 *      Author: Leon Zhou (10177892;14lz21)
 *      Header file for code for jumble puzzle game for CMPE 320 ASSIGNMENT 4
 */
#pragma once
using namespace std;

typedef char* charArrayPtr;

class JumblePuzzle
{
public:
	//Constructors and Destructors
	JumblePuzzle(const string &word, const string &difficulty);
	JumblePuzzle(const JumblePuzzle&);
	~JumblePuzzle();
	// overload assignment operator
	JumblePuzzle& operator=(const JumblePuzzle&);
	// return a copy of the jumble matrix
	charArrayPtr* getJumble() const;
	// return size of puzzle (puzzle is a size x size matrix)
	int getSize() const;
	// return the row position of the hidden word
	int getRowPos() const;
	// return the column position of the hidden word
	int getColPos() const;
	// return the direction the hidden word is written in
	char getDirection() const;
	// return the difficulty of the word
	char getDiff() const;
private:
	int size;
	int rowPos;
	int colPos;
	char Direction;
	string W;
	int Diff;
	charArrayPtr *Jmatrix; // matrix for jumble puzzle
	void hideWord(); //hides the entered word in the puzzle.
	string hiddenWord;
	void deleteJmatrix(); // removes the matrix from heap
};

class BadJumbleException
{
public:
	//Constructor accepts the address of a string (pass by reference)
	BadJumbleException(const string& s);

	//function to display string ER
	string what();
private:
	//ER = s
	string ER;
};

