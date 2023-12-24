#define _CRT_SECURE_NO_WARNINGS 1
#include "task2.h"

void test1();
void test2();

int main() {
	
	test1();
	return 0;
}

void test1() {
	std::cout << "请输入矩阵的阶数:" << std::endl;
	int n; std::cin >> n;

	Matrix matrix(n, n);                                             //question1
	std::cout << "请初始化矩阵:" << std::endl;
	matrix.SetContent();            //给矩阵初始化
	puts("");

	std::cout << "该图的一个生成树t的相邻矩阵为:" << std::endl;       //question2
	std::vector<std::vector<int>> treeMatrix = matrix.FindSpanningTree();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << treeMatrix[i][j] << " ";
		}
		puts("");
	}
	puts("");

																	 //question3
	std::cout << "此图可生成" << matrix.GetSpanningTreeNum() << "棵不同的树。" << std::endl;
	puts("");

	std::cout << "为该图的每条边编号:" << std::endl;
	std::vector<std::vector<int>> number = matrix.numberEdges();
	for (int i = 0; i < number.size(); i++) {
		std::cout << "节点 v" << number[i][1] + 1 << "和节点 v" << number[i][2] + 1 << " 之间的边，编号为：" << number[i][0] + 1;
		puts("");
	}
	puts("");

	std::cout << "该生成树t对应的基本回路系统为:" << std::endl;
	std::cout << "{ ";
	std::vector<std::vector<int>> fundamentalCircuit = matrix.FindFundamentalCircuit();
	for (int i = 0; i < fundamentalCircuit.size(); i++) {
		for (auto& C : fundamentalCircuit[i]) {
			std::cout << "e" << C + 1;
		}
		std::cout << ", ";
	}
	std::cout << "\b\b}";
	puts("");

	std::cout << "该生成树t对应的环路空间为:" << std::endl;
	std::cout << "{ ";
	std::vector<std::vector<int>> cycleSpace = matrix.FindCycleSpace(); 
	std::cout << "None, ";
	for (int i = 0; i < cycleSpace.size() - 1; i++) {
		for (auto& C : cycleSpace[i]) {
			std::cout << "e" << C + 1;
		}
		std::cout << ", ";
	}
	std::cout << "\b\b}";
	puts("");
	puts("");

	std::cout << "该生成树t对应的基本割集系统为:" << std::endl;
	std::cout << "{ ";
	std::vector<std::vector<int>> fundamentalCutSet = matrix.FindFundamentalCutSet();
	for (int i = 0; i < fundamentalCutSet.size(); i++) {
		std::cout << "{";
		for (auto& C : fundamentalCutSet[i]) {
			std::cout << "e" << C + 1 << ", ";
		}
		std::cout << "}, ";
	}
	std::cout << "\b\b}";
	puts("");

	std::cout << "该生成树t对应的断集空间为:" << std::endl;
	std::cout << "{ ";
	std::vector<std::vector<int>> cutSetSpace = matrix.FindCutSetSpace();
	std::cout << "None, ";
	for (int i = 0; i < cutSetSpace.size() - 1; i++) {
		std::cout << "{";
		for (auto& C : cutSetSpace[i]) {
			std::cout << "e" << C + 1 << ", ";
		}
		std::cout << "}, ";
	}
	std::cout << "\b\b}";
	puts("");
}

//void test2() {
//	
//	std::vector<std::vector<int>> v = {
//		{0, 1, 0, 0, 1},
//		{1, 0, 1, 0, 1},
//		{0, 1, 0, 1, 0},
//		{0, 1, 1, 0, 1},
//		{1, 1, 0, 1, 0},
//	};
//	Matrix m(v);

	//std::vector<std::vector<int>> v5 = m.FindFundamentalCircuit();
	//for (int i = 0; i < v5.size(); i++) {
	//	for (auto& C : v5[i]) {
	//		std::cout << C << " ";
	//	}
	//	puts("");
	//}

	//puts("");
	//puts("");
	//std::vector<std::vector<int>> v4 = m.FindCycleSpace();

	//for (int i = 0; i < v4.size(); i++) {
	//	for (auto& C : v4[i]) {
	//		std::cout << C << " ";
	//	}
	//	puts("");
	//}

	//std::vector<std::vector<int>> v5 = m.FindFundamentalCutSet();
	//for (int i = 0; i < v5.size(); i++) {
	//	for (auto& C : v5[i]) {
	//		std::cout << C << " ";
	//	}
	//	puts("");
	//}

	//puts("");
	//puts("");
	//std::vector<std::vector<int>> v4 = m.FindCutSetSpace();

	//for (int i = 0; i < v4.size(); i++) {
	//	for (auto& C : v4[i]) {
	//		std::cout << C << " ";
	//	}
	//	puts("");
	//}
	/*std::vector<std::vector<int>> v2 = m.numberEdges();
	for (int i = 0; i < v2.size(); i++) {
		for (auto C : v2[i]) {
			std::cout << C << " ";
		}
		puts("");
	}
	puts("");
	puts("");
	std::vector<std::vector<int>> v3 = FindMatrixByNumber(v2);
	for (int i = 0; i < v3.size(); i++) {
		for (int j = 0; j < v3[0].size(); j++) {
			std::cout << v3[i][j] << " ";
		}
		puts("");
	}*/
	//std::vector<std::vector<int>> tree = m.FindSpanningTree();

	//std::vector<std::vector<int>> edge = m.numberEdges();  //返回边集合
	//
	//for (int i = 0; i < edge.size(); i++) {
	//	for (int j = 0; j < edge[0].size(); j++) {
	//		std::cout << edge[i][j] << " ";
	//	}
	//	puts("");
	//}
	//puts("");
	//puts("");
	//puts("");

	//std::vector<std::vector<int>> edge2 = m.FindFundamentalCircuit();  //返回边集合
	//for (int i = 0; i < edge2.size(); i++) {
	//	for (int j = 0; j < edge2[0].size(); j++) {
	//		std::cout << edge2[i][j] << " ";
	//	}
	//	puts("");
	//}
//}
