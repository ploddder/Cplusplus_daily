#define _CRT_SECURE_NO_WARNINGS 1
#include "task3.h"

void Matrix::setMatrix() {
	for (int i = 0; i < data.size(); i++) {
		std::cout << "请输入第" << i + 1 << "行的数据: ";
		for (int j = 0; j < data[0].size(); j++) {
			std::cin >> data[i][j];
		}
	}
}


void Matrix::printMatrix() {
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size(); j++) {
			std::cout << data[i][j] << " ";
		}
		puts("");
	}
}

std::vector<std::vector<int>> Matrix::getNumberEdge() {
	std::vector<std::vector<int>> res;
	for (int i = 0; i < data[0].size(); i++) {			//遍历每一列  (每一个边)
		std::vector<int> t;
		t.push_back(i);
		for (int j = 0; j < data.size(); j++) {			//遍历每一行  (每一个点)
			if (data[j][i]) {
				t.push_back(j);
			}
		}
		if (t.size() < 3) {                            //如果有环
			for (int j = 0; j < data.size(); j++) {			//遍历每一行  (每一个点)
				if (data[j][i]) {
					t.push_back(j);
				}
			}
		}
		res.push_back(t);
	}
	return res;
}

void dfs3(std::vector<std::vector<int>>& matrix, int u, std::vector<bool>& isVisted) {
	isVisted[u] = true;                 //判断连通性

	for (int i = 0; i < matrix[u].size(); ++i) {
		if (matrix[u][i] && !isVisted[i]) {
			dfs3(matrix, i, isVisted);
		}
	}
}

bool Matrix::isContented(std::vector<std::vector<int>>& mr) {
	std::vector<bool> isVisted(mr.size(), false);  //记录每个结点的访问情况

	dfs3(mr, 0, isVisted);

	for (auto iv : isVisted) {  //判断结点是否被访问过
		if (!iv) {
			return false;       //若存在没被访问过的，则不连通
		}
	}
	return true;
}


std::vector<std::vector<int>> Matrix::getNumberEdgesByAdjacencyMatrix(std::vector<std::vector<int>> matrix ) {
	std::vector<std::vector<int>> edgeList;
	int edgeId = 0;

	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = i + 1; j < matrix[i].size(); ++j) {
			if (matrix[i][j] > 0) {
				edgeList.push_back({ edgeId++, i, j });
			}
		}
	}

	return edgeList;
}


bool Matrix::isEveryEdgeDisjoint(std::vector<std::vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0; i < n; ++i) {
		int edgeCount = 0;
		for (int j = 0; j < n; ++j) {
			if (adjMatrix[i][j] == 1) {
				++edgeCount;
			}
		}
		if (edgeCount > 1) {
			return false;
		}
	}
	return true;
}

std::vector<std::vector<int>> Matrix::getAdjacencyMatrixByNumber(std::vector<std::vector<int>>& number) {
	std::vector<std::vector<int>> res(data.size(), std::vector<int>(data.size(), 0));	//空矩阵
	for (int i = 0; i < number.size(); i++) {	//遍历每一条边
		int rows = number[i][1];
		int cols = number[i][2];
		res[rows][cols] = res[cols][rows] = 1;
	}
	return res;
}

void Matrix::dfs2(int u, std::vector<int>& isVisted, std::vector<std::vector<int>>& numberEdge, std::vector<std::vector<int>>& allMatching) {
	if (u >= isVisted.size()) {  //如果边全部遍历完
		std::vector<std::vector<int>> t1;  //存有被选上的边的集合
		for (int i = 0; i < isVisted.size(); i++) {
			if (isVisted[i] == 1) {
				t1.push_back(numberEdge[i]); 
			}
		}

		std::vector<std::vector<int>> t2;  //存有未被选上的边的集合
		for (int i = 0; i < isVisted.size(); i++) {
			if (isVisted[i] == 2) {
				t2.push_back(numberEdge[i]);
			}
		}
		std::vector<std::vector<int>> judgeMatrix = getAdjacencyMatrixByNumber(t1); //选中边的相邻矩阵
		bool flag = isEveryEdgeDisjoint(judgeMatrix);
		
		if (!flag) return;
		if (flag) {   //如果选中边的矩阵不连通
			std::vector<int> t3;  //存有一个匹配  即边集合
			for (int i = 0; i < t1.size(); i++) {
				t3.push_back(t1[i][0]);
			}
			allMatching.push_back(t3);
		}
		return;
	}

	isVisted[u] = 1;
	dfs2(u + 1, isVisted, numberEdge, allMatching);	//选

	isVisted[u] = 2;    //不选
	dfs2(u + 1, isVisted, numberEdge, allMatching);	//选
}

std::vector<std::vector<int>> Matrix::getMaxMatching() {
	std::vector<int> isVisted(data[0].size(), 0);  //查重向量,看边选不选
	std::vector<std::vector<int>> numberEdge = getNumberEdge(); //获得边集合
	std::vector<std::vector<int>> allMatching;				   //存所有匹配
	std::vector<std::vector<int>> maxMatching;                 //存最匹配
	
	dfs2(0, isVisted, numberEdge, allMatching);
	int k = 0;                             //存有最大匹配种 存的边数
	for (int i = 0; i < allMatching.size(); i++) {
		int t = allMatching[i].size();
		k = std::max(k, t);
		//std::cout << k << std::endl;
	}
	for (int i = 0; i < allMatching.size(); i++) {
		if (allMatching[i].size() == k) {
			maxMatching.push_back(allMatching[i]);
		}
	}
	return maxMatching;
}

std::vector<std::vector<int>> Matrix::getMaxMatching(std::vector<std::vector<int>>& numberEdge) {
	std::vector<int> isVisted(numberEdge.size(), 0);  //查重向量,看边选不选
	std::vector<std::vector<int>> allMatching;				   //存所有匹配
	std::vector<std::vector<int>> maxMatching;                 //存最大匹配

	dfs2(0, isVisted, numberEdge, allMatching);
	int k = 0;                             //存有最大匹配种 存的边数
	for (int i = 0; i < allMatching.size(); i++) {
		int t = allMatching[i].size();
		k = std::max(k, t);
		//std::cout << k << std::endl;
	}
	for (int i = 0; i < allMatching.size(); i++) {
		if (allMatching[i].size() == k) {
			maxMatching.push_back(allMatching[i]);
		}
	}
	return maxMatching;
}



bool Matrix::isEulerianGraph() {
	int n = data.size();
	for (int i = 0; i < n; i++) {  //遍历每一行
		int deg = 0;
		for (int j = 0; j < data[0].size(); j++) {
			if (data[i][j]) {   //如果为1  则度数++
				deg++;
			}
		}
		if (deg % 2 != 0) return false;  //如果有一个结点度数不是偶数 则不是欧拉图
	}
	return true;
}

int Matrix::shortestPath(const std::vector<std::vector<int>>& adjMatrix, int start, int end) {
	int n = adjMatrix.size(); // 获取邻接矩阵的大小
	std::vector<int> dist(n, -1); // 初始化距离数组，全部赋值为-1
	std::queue<int> q; // 定义队列，用于广度优先搜索

	dist[start] = 0; // 起点到起点的距离为0
	q.push(start); // 将起点加入队列

	while (!q.empty()) { // 当队列不为空时
		int v = q.front(); // 取出队头元素
		q.pop(); // 弹出队头元素

		for (int u = 0; u < n; ++u) { // 遍历所有与当前节点相连的节点
			if (adjMatrix[v][u] && dist[u] == -1) { // 如果存在一条从v到u的边，并且u还未被访问过
				q.push(u); // 将u加入队列
				dist[u] = dist[v] + 1; // 更新u到start的距离

				if (u == end) return dist[u]; // 如果u为终点，返回距离
			}
		}
	}

	return 0; // 如果图不连通，返回0
}



std::vector<int> findPathByPoint(std::vector<int>& pathPoint, std::vector<std::vector<int>>& numberEdge) {
	std::vector<int> path;
	for (int i = 0, j = 1; j < pathPoint.size(); i++, j ++) {  //遍历每一个点
		for (int k = 0; k < numberEdge.size(); k++) {          //遍历每一个边
			if ((numberEdge[k][1] == pathPoint[i] && numberEdge[k][2] == pathPoint[j])
				|| (numberEdge[k][2] == pathPoint[i] && numberEdge[k][1] == pathPoint[j])) {
				path.push_back(k);
			}
		}
	}
	return path;
}

void dfs1(int u, std::vector<std::vector<int>>& matrix, std::vector<int>& pathPoint) {
	for (int i = 0; i < matrix.size(); i++) {  //遍历当前结点为所有点
		if (matrix[u][i]) {                    //如果i点和当前点相邻
			matrix[u][i]--;
			matrix[i][u]--;
			dfs1(i, matrix, pathPoint);
		}
	}
	pathPoint.push_back(u);
}

std::vector<int> Matrix::findEulerianCircuit(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& numberEdge) {
	
	std::vector<int> pathPoint;  //回路路径经过的点
	dfs1(0, matrix, pathPoint);

	std::vector<int> path;
	path = findPathByPoint(pathPoint, numberEdge);
	return path;
}

std::vector<int> Matrix::ansPostman() {
	std::vector<std::vector<int>> numberEdge = getNumberEdge(); //获得边集合
	std::vector<std::vector<int>> matrix = getAdjacencyMatrixByNumber(numberEdge);  //图的相邻矩阵

	std::vector<int> path;                //最终边路径
	
	if (isEulerianGraph()) {
		path = findEulerianCircuit(matrix, numberEdge);
	}
	else {
		std::vector<int> oddDegreeVertex;  //奇度顶点
		for (int i = 0; i < data.size(); i++) {  //遍历每一个点
			int sum = 0;
			for (int j = 0; j < data[0].size(); j++) {
				if (data[i][j]) {
					sum++;
				}
			}
			if (sum % 2 != 0) {  //度数为奇数
				oddDegreeVertex.push_back(i);
			}
		}

		int n = oddDegreeVertex.size();    //奇度顶点的数量
		std::vector<std::vector<int>> matrixCompleteGraph(n, std::vector<int>(n, 0));//完全图带权矩阵


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int l_point = oddDegreeVertex[i];  //节点1
				int r_point = oddDegreeVertex[j];  //节点2
				int t = shortestPath(matrix, l_point, r_point);
				matrixCompleteGraph[i][j] = t;
			}
		}
		
		//这个完全图的边集合
		std::vector<std::vector<int>> numberEdge2 = getNumberEdgesByAdjacencyMatrix(matrixCompleteGraph);
		std::vector<std::vector<int>> maxMatching = getMaxMatching(numberEdge2);

		/*for (int i = 0; i < maxMatching.size(); i++) {
			for (int j = 0; j < maxMatching[0].size(); j++) {
				std::cout << maxMatching[i][j] << " ";
			}
			puts("");
		}
		puts("");
		puts("");*/

		int needMatching = 0;   //需要的最小权重和的 完美匹配的序号
		int maxNum = 10000000000000;
		for (int i = 0; i < maxMatching.size(); i++) {  //遍历每一组最大匹配
			int sum = 0;   //存有某组匹配的权和
			for (int j = 0; j < maxMatching[0].size(); j++) {  //对与某一组最大匹配 遍历每一条边
				int t = maxMatching[i][j];  //这个边的序号
				int l = numberEdge2[t][1];  //这个边左边的点
				int r = numberEdge2[t][2];  //这个边右边的点
				sum += matrixCompleteGraph[l][r];
			}
			if (sum < maxNum) {
				maxNum = sum;
				needMatching = i;
			}
		}
		

		for (int i = 0; i < maxMatching[needMatching].size(); i++) { //遍历最优完美匹配的每一条边
			int l = numberEdge2[maxMatching[needMatching][i]][1];  //这个边的左顶点
			int r = numberEdge2[maxMatching[needMatching][i]][2];  //这个边的右顶点
			int l2 = oddDegreeVertex[l];         //转换成真实的顶点序号
			int r2 = oddDegreeVertex[r];         //转换成真实的顶点序号
			
			matrix[l2][r2]++;             //给相邻矩阵添加边
			matrix[r2][l2]++;             //给相邻矩阵添加边变成欧拉图

			std::vector<int> t(3);

			for (int j = 0; j < numberEdge.size(); j++) {
				if ((numberEdge[j][1] == l2 && numberEdge[j][2] == r2) ||
					(numberEdge[j][2] == l2 && numberEdge[j][1] == r2)) {
					t.push_back(numberEdge[j][0]);
					t.push_back(numberEdge[j][1]);
					t.push_back(numberEdge[j][2]);
				}
			}
			numberEdge.push_back(t);    //给边集合添加边
		}
		path = findEulerianCircuit(matrix, numberEdge);
		
	}
	return path;
}

