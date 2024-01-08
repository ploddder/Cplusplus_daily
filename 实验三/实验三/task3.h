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
	void printMatrix();								//��ӡ����
	std::vector<std::vector<int>> getNumberEdge();  //��ñ߼��� ͨ����������
	bool isContented(std::vector<std::vector<int>>& mr);  //�ж��ǲ�����ͨͼ
	std::vector<std::vector<int>> getNumberEdgesByAdjacencyMatrix(std::vector<std::vector<int>> matrix);  //������ھ����ÿ����������� ���Ҽ�¼��ͷ�Ľ��
	bool isEveryEdgeDisjoint(std::vector<std::vector<int>>& adjMatrix);  //�ж�ÿ�����ǲ���1��
	std::vector<std::vector<int>> getAdjacencyMatrixByNumber(std::vector<std::vector<int>>& number); //ͨ���߼��ϻ�����ھ���
	void dfs2(int u, std::vector<int>& isVisted, std::vector<std::vector<int>>& numberEdge, std::vector<std::vector<int>>& allMatching);  //������ƥ���dfs
	std::vector<std::vector<int>> getMaxMatching();				//������ƥ�伯
	std::vector<std::vector<int>> getMaxMatching(std::vector<std::vector<int>>& numberEdge); //�ҳ��߼��ϵ����ƥ��
	int shortestPath(const std::vector<std::vector<int>>& adjMatrix, int start, int end);//��������������·������
	bool isEulerianGraph();           //�ж��ǲ���ŷ��ͼ
	std::vector<int> findEulerianCircuit(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& numberEdge);  //Ѱ��ŷ����·
	std::vector<int> ansPostman();  //����й��ʵ�Ա����Ľ��
	
private:
	std::vector<std::vector<int>> data;
};