#pragma once

// Add your code here

class SudokuPuzzle {
public:
	SudokuPuzzle();

	void solve(const char filenameIn[]);

	// Add your code here

private:
	void output() const;

	void readPuzzle(const char filenameIn[]) const;

	// Add your code here

};

