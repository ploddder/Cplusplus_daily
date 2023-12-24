#define _CRT_SECURE_NO_WARNINGS 1
#include "task2.h"

void _dfs(std::vector<std::vector<int>>& mr, int u, std::vector<int>& isVisted) {
	isVisted[u] = true;                 //判断连通性
	int n = mr.size();
	for (int i = 0; i < n; i++) {
		if (mr[u][i] && !isVisted[i]) {
			_dfs(mr, i, isVisted);
		}
	}
}

bool isContented(std::vector<std::vector<int>>& mr) {
	std::vector<int> isVisted(mr.size());  //记录每个结点的访问情况

	_dfs(mr, 0, isVisted);

	for (auto iv : isVisted) {  //判断结点是否被访问过
		if (!iv) {
			return false;       //若存在没被访问过的，则不连通
		}	}
	return true;
}

int Matrix::GetRows() const {          //为什么后面要加const  忘记了 记得复习C++！！！
	return data.size();
}

int Matrix::GetCols() const {
	return data[0].size();
}

void Matrix::SetContent() {
	for (int i = 0; i < GetRows(); i++) {
		std::cout << "请输入第" << i + 1 << "行的各个元素:  ";
		for (int j = 0; j < GetCols(); j++) {
			std::cin >> data[i][j];
		}
	}
}

void Matrix::PrintMatrix() {
	for (int i = 0; i < GetRows(); i++) {
		for (int j = 0; j < GetCols(); j++) {
			std::cout << data[i][j] << "  ";
		}
		puts("");
	}
}

void dfs(int u, const std::vector<std::vector<int>>& m, std::vector<std::vector<int>>& tree, std::vector<bool>& visited) {
	visited[u] = true;               //找生成树的深搜

	for (int v = 0; v < m.size(); ++v) {
		if (m[u][v] && !visited[v]) {

			tree[u][v] = 1;
			tree[v][u] = 1;

			dfs(v, m, tree, visited);
		}
	}
}

std::vector<std::vector<int>> Matrix::FindSpanningTree() {
	int n = this->data.size();
	std::vector<std::vector<int>> m2(n, std::vector<int>(this->data[0].size(), 0));
	std::vector<bool> visited(n, false);

	dfs(0, this->data, m2, visited);

	return m2;
}




int valueOfMatrix(int n, std::vector<std::vector<int> >a)
{
	// 使用递归算法计算行列式的值
	if (n == 1)
	{
		return a[0][0];
	}
	else if (n == 2)
		return a[0][0] * a[1][1] - a[0][1] * a[1][0];
	else
	{
		int sum = 0;
		for (int k = 0; k < n; k++)
		{
			std::vector<std::vector<int> > b;
			for (int i = 1; i < n; i++)
			{
				std::vector<int>c;
				for (int j = 0; j < n; j++)
				{
					if (j == k)
						continue;
					c.push_back(a[i][j]);
				}
				b.push_back(c);
			}
			sum = k % 2 == 0 ? sum + a[0][k] * valueOfMatrix(n - 1, b) :
				sum - a[0][k] * valueOfMatrix(n - 1, b);
		}
		return sum;
	}
}








int Matrix::GetSpanningTreeNum() {
	std::vector<std::vector<int>> DegreeMatrix(this->data.size(), std::vector<int>(this->data[0].size(), 0));
	int rows = this->data.size();
	int cols = this->data[0].size();
	for (int i = 0; i < rows; i++) {
		int d = 0;
		for (int j = 0; j < cols; j++) {
			d += this->data[i][j];
		}
		DegreeMatrix[i][i] = d;
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			DegreeMatrix[i][j] -= data[i][j];
		}
	}
	return valueOfMatrix(rows - 1, DegreeMatrix);
}


std::vector<std::vector<int>> Matrix::numberEdges() {
	std::vector<std::vector<int>> edgeList;
	int edgeId = 0;

	for (int i = 0; i < data.size(); ++i) {
		for (int j = i + 1; j < data[i].size(); ++j) {
			if (data[i][j] == 1) {
				edgeList.push_back({ edgeId++, i, j });
			}
		}
	}

	return edgeList;
}

void dfs3(int head, int tail, std::vector<std::vector<int>>& tree, std::vector<bool>& invisted, std::vector<int>& Circuit, std::vector<std::vector<int>> numberTree) {
	if (head == tail) {
		/*for (int i = 0; i < Circuit.size(); i++) {
			std::cout << Circuit[i] << " ";
		}
		puts("");*/
		return;
	}
	for (int i = 0; i < tree.size(); i++) {
		if (tree[head][i] == 1 && !invisted[i]) {
			invisted[i] = true;

			for (int j = 0; j < numberTree.size(); j++) {
				if (numberTree[j][1] == head && numberTree[j][2] == i) {
					Circuit.push_back(numberTree[j][0]);
				}
			}
			
			dfs3(i, tail, tree, invisted, Circuit, numberTree);
			invisted[i] = false;
		}
	}
	return;
}

std::vector<int> dfs2(std::vector<int> chord, std::vector<std::vector<int>>& tree, std::vector<std::vector<int>>& numberTree) {
	int head = chord[1];
	int tail = chord[2];
	std::vector<bool> invisted(tree.size(), false);
	invisted[head] = true;

	std::vector<int> Circuit;
	dfs3(head, tail, tree, invisted, Circuit, numberTree);

	return Circuit;
}


std::vector<std::vector<int>> Matrix::FindFundamentalCircuit() {
	std::vector<std::vector<int>> tree = FindSpanningTree();  //生成树
	std::vector<std::vector<int>> chord(data.size(), std::vector<int>(data[0].size(), 0));//弦
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size(); j++) {
			chord[i][j] = data[i][j] - tree[i][j];
		}
	}

	std::vector<std::vector<int>> number = numberEdges();     //图的边集合
	std::vector<std::vector<int>> numberTree;				  //树枝的边集合
	std::vector<std::vector<int>> numberChord;				  //弦的边集合

	std::vector<std::vector<int>> fundamentalCircuit;         //基本回路集合

	for (int i = 0; i < tree.size(); ++i) {
		for (int j = i + 1; j < tree[i].size(); ++j) {
			if (tree[i][j] == 1) {
				int edgeId = 0;
				for (int k = 0; k < number.size(); k++) {
					if (number[k][1] == i && number[k][2] == j) {
						edgeId = number[k][0];
					}
				}
				numberTree.push_back({ edgeId, i, j });
			}
		}
	}

	for (int i = 0; i < chord.size(); ++i) {
		for (int j = i + 1; j < chord[i].size(); ++j) {
			if (chord[i][j] == 1) {
				int edgeId = 0;
				for (int k = 0; k < number.size(); k++) {
					if (number[k][1] == i && number[k][2] == j) {
						edgeId = number[k][0];
					}
				}
				numberChord.push_back({ edgeId, i, j });
			}
		}
	}

	for (int i = 0; i < numberChord.size(); i++) {
		
		std::vector<int> t = dfs2(numberChord[i], tree, numberTree);
		t.push_back(numberChord[i][0]);
		fundamentalCircuit.push_back(t);
	}
	
	return fundamentalCircuit;
}


std::vector<std::vector<int>> FindMatrixByNumber(std::vector<std::vector<int>>& number) {
	int n = 0;
	for (int i = 0; i < number.size(); i++) {
		n = std::max(std::max(number[i][1], number[i][2]), n);
	}
	n++;
	std::vector<std::vector<int>> res(n, std::vector<int>(n, 0));
	for (int i = 0; i < number.size(); i++) {
		res[number[i][1]][number[i][2]] = res[number[i][2]][number[i][1]] = 1;
	}
	return res;
}

std::vector<int> dfs4(std::vector<std::vector<int>>& m, std::vector<std::vector<int>>& numberChord) {
	std::vector<int> res;
	for (int i = 0; i < numberChord.size(); i++) {
		std::vector<std::vector<int>> t = m;
		int l = numberChord[i][1];
		int r = numberChord[i][2];
		t[l][r] = t[r][l] = 1;
		if (isContented(t)) {
			res.push_back(numberChord[i][0]);
		}
	}
	return res;
}

std::vector<std::vector<int>> Matrix::FindFundamentalCutSet() {
	std::vector<std::vector<int>> tree = FindSpanningTree();  //生成树矩阵
	std::vector<std::vector<int>> chord(data.size(), std::vector<int>(data[0].size(), 0));//弦矩阵
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size(); j++) {
			chord[i][j] = data[i][j] - tree[i][j];
		}
	}

	std::vector<std::vector<int>> number = numberEdges();     //图的边集合
	std::vector<std::vector<int>> numberTree;				  //树枝的边集合
	std::vector<std::vector<int>> numberChord;				  //弦的边集合

	std::vector<std::vector<int>> fundamentalCircuit;         //基本回路集合

	for (int i = 0; i < tree.size(); ++i) {
		for (int j = i + 1; j < tree[i].size(); ++j) {
			if (tree[i][j] == 1) {
				int edgeId = 0;
				for (int k = 0; k < number.size(); k++) {
					if (number[k][1] == i && number[k][2] == j) {
						edgeId = number[k][0];
					}
				}
				numberTree.push_back({ edgeId, i, j });
			}
		}
	}

	for (int i = 0; i < chord.size(); ++i) {
		for (int j = i + 1; j < chord[i].size(); ++j) {
			if (chord[i][j] == 1) {
				int edgeId = 0;
				for (int k = 0; k < number.size(); k++) {
					if (number[k][1] == i && number[k][2] == j) {
						edgeId = number[k][0];
					}
				}
				numberChord.push_back({ edgeId, i, j });
			}
		}
	}

	std::vector<std::vector<int>> MatrixBynumer = FindMatrixByNumber(numberTree); //树枝的边集合转化出邻接矩阵
	
	std::vector<std::vector<int>> FundamentalCutSet;          //基本断集集合
	for (int i = 0; i < numberTree.size(); i++) {             //遍历每一个树枝
		std::vector<std::vector<int>> t = MatrixBynumer;
		int l = numberTree[i][1];
		int r = numberTree[i][2]; 
		t[l][r] = t[r][l] = 0;			//删除一个树枝 生成一个不连通的树 t矩阵

		std::vector<int> t2 = dfs4(t, numberChord);  //得到一个断集
		t2.push_back(numberTree[i][0]);
		FundamentalCutSet.push_back(t2);
	}

	return FundamentalCutSet;
}

//求对称差
std::vector<std::vector<int>> SymmetricDifference(std::vector<std::vector<int>> l, std::vector<std::vector<int>> r, int n) {
	std::vector<std::vector<int>> t(n, std::vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			t[i][j] = (l[i][j] ^ r[i][j]);
		}
	}
	return t;
}

//通过集合 获得n阶大矩阵
std::vector<std::vector<int>> FindMatrixByNumberBig(std::vector<int>& numberCir, std::vector<std::vector<int>>& number, int n) {
	std::vector<std::vector<int>> t(n, std::vector<int>(n, 0));  //空大矩阵
	for (int i = 0; i < numberCir.size(); i++) {
		for (int j = 0; j < number.size(); j++) {
			if (numberCir[i] == number[j][0]) {
				int l = number[j][1];
				int r = number[j][2];
				t[l][r] = t[r][l] = 1;
			}
		}
	}
	return t;
}


void dfs5(int u, std::vector<bool>& isVisted, std::vector<std::vector<int>>& v, int n, std::vector<std::vector<int>>& number, std::vector<std::vector<int>>& res) {
	if (u >= v.size()) {
		std::vector<std::vector<int>> t(n, std::vector<int>(n, 0));  //n阶空矩阵
		for (int i = 0; i < v.size(); i++) {
			if (isVisted[i]) {
				std::vector<std::vector<int>> v2 = FindMatrixByNumberBig(v[i], number, n); //获得大矩阵
				t = SymmetricDifference(t, v2, n);   //让t一步一步对称差  积累结果
			}
		}
		
		std::vector<int> tmp;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (t[i][j]) {
					for (int k = 0; k < number.size(); k++) {  //遍历每一个边的编号
						if (number[k][1] == i && number[k][2] == j) {
							tmp.push_back(number[k][0]);       //尾插 边的编号
						}
					}
				}
			}
		}
		res.push_back(tmp);

		return;
	}
	
	isVisted[u] = true;         //选
	dfs5(u + 1, isVisted, v, n, number, res);

	isVisted[u] = false;
	dfs5(u + 1, isVisted, v, n, number, res);   //不选
}

std::vector<std::vector<int>> Matrix::FindCycleSpace() {
	std::vector<std::vector<int>> v = FindFundamentalCircuit(); //基本环路系统
	std::vector<std::vector<int>> number = numberEdges();       //图的边集合

	int n = data.size();   //矩阵的阶
	std::vector<bool> isVisted(v.size(), false);                //查重向量

	std::vector<std::vector<int>> res;
	dfs5(0, isVisted, v, n, number, res);
	
	return res;
}


std::vector<std::vector<int>> Matrix::FindCutSetSpace() {
	std::vector<std::vector<int>> v = FindFundamentalCutSet();  //基本割集系统
	std::vector<std::vector<int>> number = numberEdges();       //图的边集合

	int n = data.size();   //矩阵的阶
	std::vector<bool> isVisted(v.size(), false);                //查重向量
	std::vector<std::vector<int>> res;
	dfs5(0, isVisted, v, n, number, res);

	return res;
}


