#pragma once
#include <iostream>
#include <vector>
#include <algorithm>


class Matrix {
public:
	Matrix(const int& rows, const int& cols)
		: data(rows, std::vector<int>(cols, 0))    //��ʼ�� a * b �ľ���
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
	
	int GetRows() const;          //Ϊʲô����Ҫ��const  ������ �ǵø�ϰC++������
	int GetCols() const;
	void SetContent();            //�������ʼ��
	void PrintMatrix();           //��ӡ����
	std::vector<std::vector<int>> FindSpanningTree(); //Ѱ�Ҹþ����һ��������
	int GetSpanningTreeNum();				//����������������
	std::vector<std::vector<int>> numberEdges();  //��ÿ����������� ���Ҽ�¼��ͷ�Ľ��
	std::vector<std::vector<int>> FindFundamentalCircuit(); //�ҳ�������·ϵͳ
	std::vector<std::vector<int>> FindFundamentalCutSet();  //�ҳ������ϵͳ
	std::vector<std::vector<int>> FindCycleSpace();         //�ҳ���·�ռ�
	std::vector<std::vector<int>> FindCutSetSpace();            //�ҳ��ϼ��ռ�


private:
	std::vector<std::vector<int>> data;
};

std::vector<std::vector<int>> FindMatrixByNumber(std::vector<std::vector<int>>& number); //ͨ���߼����Ҿ���
bool isContented(std::vector<std::vector<int>>& mr); //�ж�ͼ�Ƿ���ͨ
