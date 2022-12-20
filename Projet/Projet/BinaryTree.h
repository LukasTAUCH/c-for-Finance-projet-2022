#pragma once
#include <vector>
#include <iostream>

template <typename T>
class BinaryTree {
private:
	std::vector<std::vector<T>> _tree;

public:
	int _depth;
	//BinaryTree() { };
	~BinaryTree() {};
	
	void setDepth(int depth)
	{
		_depth = depth;
		_tree.clear();
		PascalTriangle(_depth);
	}

	void PascalTriangle(int numRows)
	{
		for (int i = 0; i <= numRows; i++)
		{
			std::vector<T> temp(i + 1, 1);
			for (int j = 1; j < temp.size() - 1; j++)
				temp[j] = _tree[i - 1][j - 1] + _tree[i - 1][j];
			_tree.push_back(temp);
		}
	}

	void setNode(int i, int j, T value)
	{
		_tree[i][j] = value;
	}

	T getNode(int i, int j) {
		return _tree[i][j];
	}

	void display()
	{
		for (int i = 0; i <= _depth; i++)
		{
			for (auto it = _tree[i].begin();it != _tree[i].end(); it++)
			{
				std::cout << *it << " ";
			}
			std::cout << std::endl;

		}

		
		std::cout << std::endl;


		int coef = getNode(0, 0);
		for (int i = 0; i <= _depth; i++)
		{
			for (int space = 1; space <= _depth - i; space++)
				std::cout << "  ";


			for (int j = 0; j <= i; j++)
			{

				if (j == 0 || i == 0)
					coef = getNode(0, 0);
				else
					coef = getNode(i, j);

				std::cout << coef << "    ";
			}
			std::cout << std::endl;
			if (i == _depth - 1)
				break;

				

			/*
			for (int space = 1; space < _depth - i; space++)
				std::cout << "  ";
			for (int space = 0; space <= i; space++)
				if (i <= 4)
					std::cout << " /" << "  \\";
				else
					std::cout << " / " << " \\ ";
			*/

		}
		
	}
};
