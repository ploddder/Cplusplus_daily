#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <queue>

class Matrix {
public:
	Matrix(int rows, int cols) 
		:data(rows, std::vector<int>(cols, 0))
	{}
	Matrix(std::vector<std::vector<int>>& v)
		:data(v)
	{}

	void setMatrix();
	void printMatrix();								//打印矩阵
	std::vector<std::vector<int>> getNumberEdge();  //获得边集合 通过关联矩阵
	bool isContented(std::vector<std::vector<int>>& mr);  //判断是不是连通图
	std::vector<std::vector<int>> getNumberEdgesByAdjacencyMatrix(std::vector<std::vector<int>> matrix);  //针对相邻矩阵给每个边生成序号 并且记录两头的结点
	bool isEveryEdgeDisjoint(std::vector<std::vector<int>>& adjMatrix);  //判断每个点是不是1度
	std::vector<std::vector<int>> getAdjacencyMatrixByNumber(std::vector<std::vector<int>>& number); //通过边集合获得相邻矩阵
	void dfs2(int u, std::vector<int>& isVisted, std::vector<std::vector<int>>& numberEdge, std::vector<std::vector<int>>& allMatching);  //获得最大匹配的dfs
	std::vector<std::vector<int>> getMaxMatching();				//获得最大匹配集
	std::vector<std::vector<int>> getMaxMatching(std::vector<std::vector<int>>& numberEdge); //找出边集合的最大匹配
	int shortestPath(const std::vector<std::vector<int>>& adjMatrix, int start, int end);//返回两个点的最短路径长度
	bool isEulerianGraph();           //判断是不是欧拉图
	std::vector<int> findEulerianCircuit(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& numberEdge);  //寻找欧拉回路
	std::vector<int> ansPostman();  //输出中国邮递员问题的结果
	
private:
	std::vector<std::vector<int>> data;
};