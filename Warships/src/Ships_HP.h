#pragma once

class Ships_HP
{
public:
	int size_5 = 5;
	int size_4 = 4;
	int size_3 = 3;
	int size_2 = 2;
	int size_ir2 = 3;
	int size_ir3 = 6;

	// returns true if any of ships has HP left
	bool chceckhp() const;	
};

