#pragma once
#include <iostream>
#include <vector>
#include <algorithm>


class Matrix {
public:
	Matrix(const int& rows, const int& cols)
		: data(rows, std::vector<int>(cols, 0))    //初始化 a * b 的矩阵
	{}
	Matrix(std::vector<std::vector<int>> v)
		: data(v.size(), std::vector<int>(v[0].size(), 0))
	{
		for (int i = 0; i < v.size(); i++)
		{
			for (int j = 0; j < v[0].size(); j++) {
				data[i][j] = v[i][j];
			}
		}
	}
	
	int GetRows() const;          //为什么后面要加const  忘记了 记得复习C++！！！
	int GetCols() const;
	void SetContent();            //给矩阵初始化
	void PrintMatrix();           //打印矩阵
	std::vector<std::vector<int>> FindSpanningTree(); //寻找该矩阵的一颗生成树
	int GetSpanningTreeNum();				//返回生成树的数量
	std::vector<std::vector<int>> numberEdges();  //给每个边生成序号 并且记录两头的结点
	std::vector<std::vector<int>> FindFundamentalCircuit(); //找出基本回路系统
	std::vector<std::vector<int>> FindFundamentalCutSet();  //找出基本割集系统
	std::vector<std::vector<int>> FindCycleSpace();         //找出环路空间
	std::vector<std::vector<int>> FindCutSetSpace();            //找出断集空间


private:
	std::vector<std::vector<int>> data;
};

std::vector<std::vector<int>> FindMatrixByNumber(std::vector<std::vector<int>>& number); //通过边集合找矩阵
bool isContented(std::vector<std::vector<int>>& mr); //判断图是否连通
