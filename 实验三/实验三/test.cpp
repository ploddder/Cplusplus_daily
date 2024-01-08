#define _CRT_SECURE_NO_WARNINGS 1
#include "task3.h"

void test();


int main() {
	test();

}
void test() {
	int m = 0, n = 0;
	std::cout << "请输入关联矩阵的行数和列数:";
	std::cin >> m >> n;
	puts("");
	Matrix matrix(m, n);
	matrix.setMatrix();

	puts("");

	std::cout << "最大匹集为:" << std::endl;
	std::vector<std::vector<int>> res1 = matrix.getMaxMatching();
	for (int i = 0; i < res1.size(); i++) {
		std::cout << "{";
		for (int j = 0; j < res1[0].size(); j++) {
			std::cout << res1[i][j] << " ,";
		}
		std::cout << "\b\b}";
		puts("");
	}
	puts("");


	std::cout << "最短路径为:" << std::endl;
	std::vector<int> res2 = matrix.ansPostman();
	for (auto& C : res2) {
		std::cout << "e" << C + 1 << " ";
	}
}
