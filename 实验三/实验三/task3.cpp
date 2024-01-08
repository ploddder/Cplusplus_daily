#define _CRT_SECURE_NO_WARNINGS 1
#include "task3.h"

void Matrix::setMatrix() {
	for (int i = 0; i < data.size(); i++) {
		std::cout << "�������" << i + 1 << "�е�����: ";
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
	for (int i = 0; i < data[0].size(); i++) {			//����ÿһ��  (ÿһ����)
		std::vector<int> t;
		t.push_back(i);
		for (int j = 0; j < data.size(); j++) {			//����ÿһ��  (ÿһ����)
			if (data[j][i]) {
				t.push_back(j);
			}
		}
		if (t.size() < 3) {                            //����л�
			for (int j = 0; j < data.size(); j++) {			//����ÿһ��  (ÿһ����)
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
	isVisted[u] = true;                 //�ж���ͨ��

	for (int i = 0; i < matrix[u].size(); ++i) {
		if (matrix[u][i] && !isVisted[i]) {
			dfs3(matrix, i, isVisted);
		}
	}
}

bool Matrix::isContented(std::vector<std::vector<int>>& mr) {
	std::vector<bool> isVisted(mr.size(), false);  //��¼ÿ�����ķ������

	dfs3(mr, 0, isVisted);

	for (auto iv : isVisted) {  //�жϽ���Ƿ񱻷��ʹ�
		if (!iv) {
			return false;       //������û�����ʹ��ģ�����ͨ
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
	std::vector<std::vector<int>> res(data.size(), std::vector<int>(data.size(), 0));	//�վ���
	for (int i = 0; i < number.size(); i++) {	//����ÿһ����
		int rows = number[i][1];
		int cols = number[i][2];
		res[rows][cols] = res[cols][rows] = 1;
	}
	return res;
}

void Matrix::dfs2(int u, std::vector<int>& isVisted, std::vector<std::vector<int>>& numberEdge, std::vector<std::vector<int>>& allMatching) {
	if (u >= isVisted.size()) {  //�����ȫ��������
		std::vector<std::vector<int>> t1;  //���б�ѡ�ϵıߵļ���
		for (int i = 0; i < isVisted.size(); i++) {
			if (isVisted[i] == 1) {
				t1.push_back(numberEdge[i]); 
			}
		}

		std::vector<std::vector<int>> t2;  //����δ��ѡ�ϵıߵļ���
		for (int i = 0; i < isVisted.size(); i++) {
			if (isVisted[i] == 2) {
				t2.push_back(numberEdge[i]);
			}
		}
		std::vector<std::vector<int>> judgeMatrix = getAdjacencyMatrixByNumber(t1); //ѡ�бߵ����ھ���
		bool flag = isEveryEdgeDisjoint(judgeMatrix);
		
		if (!flag) return;
		if (flag) {   //���ѡ�бߵľ�����ͨ
			std::vector<int> t3;  //����һ��ƥ��  ���߼���
			for (int i = 0; i < t1.size(); i++) {
				t3.push_back(t1[i][0]);
			}
			allMatching.push_back(t3);
		}
		return;
	}

	isVisted[u] = 1;
	dfs2(u + 1, isVisted, numberEdge, allMatching);	//ѡ

	isVisted[u] = 2;    //��ѡ
	dfs2(u + 1, isVisted, numberEdge, allMatching);	//ѡ
}

std::vector<std::vector<int>> Matrix::getMaxMatching() {
	std::vector<int> isVisted(data[0].size(), 0);  //��������,����ѡ��ѡ
	std::vector<std::vector<int>> numberEdge = getNumberEdge(); //��ñ߼���
	std::vector<std::vector<int>> allMatching;				   //������ƥ��
	std::vector<std::vector<int>> maxMatching;                 //����ƥ��
	
	dfs2(0, isVisted, numberEdge, allMatching);
	int k = 0;                             //�������ƥ���� ��ı���
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
	std::vector<int> isVisted(numberEdge.size(), 0);  //��������,����ѡ��ѡ
	std::vector<std::vector<int>> allMatching;				   //������ƥ��
	std::vector<std::vector<int>> maxMatching;                 //�����ƥ��

	dfs2(0, isVisted, numberEdge, allMatching);
	int k = 0;                             //�������ƥ���� ��ı���
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
	for (int i = 0; i < n; i++) {  //����ÿһ��
		int deg = 0;
		for (int j = 0; j < data[0].size(); j++) {
			if (data[i][j]) {   //���Ϊ1  �����++
				deg++;
			}
		}
		if (deg % 2 != 0) return false;  //�����һ������������ż�� ����ŷ��ͼ
	}
	return true;
}

int Matrix::shortestPath(const std::vector<std::vector<int>>& adjMatrix, int start, int end) {
	int n = adjMatrix.size(); // ��ȡ�ڽӾ���Ĵ�С
	std::vector<int> dist(n, -1); // ��ʼ���������飬ȫ����ֵΪ-1
	std::queue<int> q; // ������У����ڹ����������

	dist[start] = 0; // ��㵽���ľ���Ϊ0
	q.push(start); // �����������

	while (!q.empty()) { // �����в�Ϊ��ʱ
		int v = q.front(); // ȡ����ͷԪ��
		q.pop(); // ������ͷԪ��

		for (int u = 0; u < n; ++u) { // ���������뵱ǰ�ڵ������Ľڵ�
			if (adjMatrix[v][u] && dist[u] == -1) { // �������һ����v��u�ıߣ�����u��δ�����ʹ�
				q.push(u); // ��u�������
				dist[u] = dist[v] + 1; // ����u��start�ľ���

				if (u == end) return dist[u]; // ���uΪ�յ㣬���ؾ���
			}
		}
	}

	return 0; // ���ͼ����ͨ������0
}



std::vector<int> findPathByPoint(std::vector<int>& pathPoint, std::vector<std::vector<int>>& numberEdge) {
	std::vector<int> path;
	for (int i = 0, j = 1; j < pathPoint.size(); i++, j ++) {  //����ÿһ����
		for (int k = 0; k < numberEdge.size(); k++) {          //����ÿһ����
			if ((numberEdge[k][1] == pathPoint[i] && numberEdge[k][2] == pathPoint[j])
				|| (numberEdge[k][2] == pathPoint[i] && numberEdge[k][1] == pathPoint[j])) {
				path.push_back(k);
			}
		}
	}
	return path;
}

void dfs1(int u, std::vector<std::vector<int>>& matrix, std::vector<int>& pathPoint) {
	for (int i = 0; i < matrix.size(); i++) {  //������ǰ���Ϊ���е�
		if (matrix[u][i]) {                    //���i��͵�ǰ������
			matrix[u][i]--;
			matrix[i][u]--;
			dfs1(i, matrix, pathPoint);
		}
	}
	pathPoint.push_back(u);
}

std::vector<int> Matrix::findEulerianCircuit(std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& numberEdge) {
	
	std::vector<int> pathPoint;  //��··�������ĵ�
	dfs1(0, matrix, pathPoint);

	std::vector<int> path;
	path = findPathByPoint(pathPoint, numberEdge);
	return path;
}

std::vector<int> Matrix::ansPostman() {
	std::vector<std::vector<int>> numberEdge = getNumberEdge(); //��ñ߼���
	std::vector<std::vector<int>> matrix = getAdjacencyMatrixByNumber(numberEdge);  //ͼ�����ھ���

	std::vector<int> path;                //���ձ�·��
	
	if (isEulerianGraph()) {
		path = findEulerianCircuit(matrix, numberEdge);
	}
	else {
		std::vector<int> oddDegreeVertex;  //��ȶ���
		for (int i = 0; i < data.size(); i++) {  //����ÿһ����
			int sum = 0;
			for (int j = 0; j < data[0].size(); j++) {
				if (data[i][j]) {
					sum++;
				}
			}
			if (sum % 2 != 0) {  //����Ϊ����
				oddDegreeVertex.push_back(i);
			}
		}

		int n = oddDegreeVertex.size();    //��ȶ��������
		std::vector<std::vector<int>> matrixCompleteGraph(n, std::vector<int>(n, 0));//��ȫͼ��Ȩ����


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int l_point = oddDegreeVertex[i];  //�ڵ�1
				int r_point = oddDegreeVertex[j];  //�ڵ�2
				int t = shortestPath(matrix, l_point, r_point);
				matrixCompleteGraph[i][j] = t;
			}
		}
		
		//�����ȫͼ�ı߼���
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

		int needMatching = 0;   //��Ҫ����СȨ�غ͵� ����ƥ������
		int maxNum = 10000000000000;
		for (int i = 0; i < maxMatching.size(); i++) {  //����ÿһ�����ƥ��
			int sum = 0;   //����ĳ��ƥ���Ȩ��
			for (int j = 0; j < maxMatching[0].size(); j++) {  //����ĳһ�����ƥ�� ����ÿһ����
				int t = maxMatching[i][j];  //����ߵ����
				int l = numberEdge2[t][1];  //�������ߵĵ�
				int r = numberEdge2[t][2];  //������ұߵĵ�
				sum += matrixCompleteGraph[l][r];
			}
			if (sum < maxNum) {
				maxNum = sum;
				needMatching = i;
			}
		}
		

		for (int i = 0; i < maxMatching[needMatching].size(); i++) { //������������ƥ���ÿһ����
			int l = numberEdge2[maxMatching[needMatching][i]][1];  //����ߵ��󶥵�
			int r = numberEdge2[maxMatching[needMatching][i]][2];  //����ߵ��Ҷ���
			int l2 = oddDegreeVertex[l];         //ת������ʵ�Ķ������
			int r2 = oddDegreeVertex[r];         //ת������ʵ�Ķ������
			
			matrix[l2][r2]++;             //�����ھ�����ӱ�
			matrix[r2][l2]++;             //�����ھ�����ӱ߱��ŷ��ͼ

			std::vector<int> t(3);

			for (int j = 0; j < numberEdge.size(); j++) {
				if ((numberEdge[j][1] == l2 && numberEdge[j][2] == r2) ||
					(numberEdge[j][2] == l2 && numberEdge[j][1] == r2)) {
					t.push_back(numberEdge[j][0]);
					t.push_back(numberEdge[j][1]);
					t.push_back(numberEdge[j][2]);
				}
			}
			numberEdge.push_back(t);    //���߼�����ӱ�
		}
		path = findEulerianCircuit(matrix, numberEdge);
		
	}
	return path;
}

