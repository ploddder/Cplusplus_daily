#define _CRT_SECURE_NO_WARNINGS 1
#include "task2.h"

void test1();
void test2();

int main() {
	
	test1();
	return 0;
}

void test1() {
	std::cout << "���������Ľ���:" << std::endl;
	int n; std::cin >> n;

	Matrix matrix(n, n);                                             //question1
	std::cout << "���ʼ������:" << std::endl;
	matrix.SetContent();            //�������ʼ��
	puts("");

	std::cout << "��ͼ��һ��������t�����ھ���Ϊ:" << std::endl;       //question2
	std::vector<std::vector<int>> treeMatrix = matrix.FindSpanningTree();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << treeMatrix[i][j] << " ";
		}
		puts("");
	}
	puts("");

																	 //question3
	std::cout << "��ͼ������" << matrix.GetSpanningTreeNum() << "�ò�ͬ������" << std::endl;
	puts("");

	std::cout << "Ϊ��ͼ��ÿ���߱��:" << std::endl;
	std::vector<std::vector<int>> number = matrix.numberEdges();
	for (int i = 0; i < number.size(); i++) {
		std::cout << "�ڵ� v" << number[i][1] + 1 << "�ͽڵ� v" << number[i][2] + 1 << " ֮��ıߣ����Ϊ��" << number[i][0] + 1;
		puts("");
	}
	puts("");

	std::cout << "��������t��Ӧ�Ļ�����·ϵͳΪ:" << std::endl;
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

	std::cout << "��������t��Ӧ�Ļ�·�ռ�Ϊ:" << std::endl;
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

	std::cout << "��������t��Ӧ�Ļ����ϵͳΪ:" << std::endl;
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

	std::cout << "��������t��Ӧ�Ķϼ��ռ�Ϊ:" << std::endl;
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

	//std::vector<std::vector<int>> edge = m.numberEdges();  //���ر߼���
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

	//std::vector<std::vector<int>> edge2 = m.FindFundamentalCircuit();  //���ر߼���
	//for (int i = 0; i < edge2.size(); i++) {
	//	for (int j = 0; j < edge2[0].size(); j++) {
	//		std::cout << edge2[i][j] << " ";
	//	}
	//	puts("");
	//}
//}
