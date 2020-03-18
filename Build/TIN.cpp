/* 
	���������㷨����TIN����
	����չ�㷨
*/
#include "TIN.h"

/*
	@Function Name: angle
	@Function param: ��line�͵���point�е��±�
	@Function return value: һ������߶����˵Ķ˵��γɵ������ߵļн�
*/
double TIN::angle(Line line, long p) {
	double a, b, c;

	c = distance(line.p0, line.p1);
	a = distance(line.p0, p);
	b = distance(line.p1, p);

	double z = 0;
	z = acos((b * b + a * a - c * c) / (2 * a * b));
	return z;
}

/*
	@Function Name: Max
	@Function param: ��line�Ϳ��õĵ���±���ɵļ���
	@Function return value:����cos���ĽǶ�Ӧ�ĵ�
*/
long TIN::Max(Line line, std::vector<long> usableList) {
	/*
		cosֵ��0����֮��ݼ�������cos���Ϊ����С
	*/
	long index = -1;
	double xitaMax = 0, xita = 0;

	for (long i = 0; i < usableList.size(); ++i) {
		xita = angle(line, usableList[i]);
		if (xita > xitaMax) {
			xitaMax = xita;
			index = usableList[i];
		}
	}

	return index;
}

double TIN::F(Line line, long p3) {
	Point a0 = pointList[line.p0], a1 = pointList[line.p1], a2 = pointList[p3];

	double A = (a1.y - a0.y) / (a1.x - a0.x);
	double B = (a1.x * a0.y - a0.x * a1.y) / (a1.x - a0.x);

	double z = 0;
	z = a2.y - a2.x * A - B;
	return z;
}

/*
	@Function Name: distance
	@Function param: ��������pointList�е��±�
	@Function return value: ����֮��ľ���
*/
double TIN::distance(long p1, long p2) {
	double z = 0;
	if (p1 != p2) {
		Point a1 = pointList[p1], a2 = pointList[p2];

		z = sqrt((a1.x - a2.x) * (a1.x - a2.x) + (a1.y - a2.y) * (a1.y - a2.y));
	}
	return z;
}

/*
	@Function Name: createPoint
	@Function param: Ҫ����������������
	@Function return value: void   =>   ��point�в���n�������
*/
void TIN::createPoint(int n) {
	Point point;
	srand(time(NULL));

	for (long i = 0; i < n; ++i) {
		point.x = rand() % 100 * 0.01 * pow(-1, (rand() % 2));
		point.y = rand() % 100 * 0.01 * pow(-1, (rand() % 2));
		point.z = rand() % 100 * 0.001 * pow(-1, (rand() % 2));
		pointList.push_back(point);
	}
}

void TIN::createTin() {
	std::vector<long> usablePointList;

	Tri tri;	//���ɵ�0��������
	long k = 0;

	Line line0;	//��L0��
	line0.p0 = 0;
	line0.p1 = 1;
	line0.useCount = 1;
	lineList.push_back(line0);
	tri.L0 = lineList.size() - 1;

	for (long i = 2; i < pointList.size(); ++i) {
		usablePointList.push_back(i);
	}

	long index = -1;
	index = Max(line0, usablePointList);

	/* ����L1,L2�� */
	Line line1, line2;

	line1.p0 = 0;
	line1.p1 = index;
	line1.useCount = 1;
	lineList.push_back(line1);
	tri.L1 = lineList.size() - 1;

	line2.p0 = 1;
	line2.p1 = index;
	line2.useCount = 1;
	lineList.push_back(line2);
	tri.L2 = lineList.size() - 1;

	triList.push_back(tri);

	/* ���ڵ�K��������Ϊ��չ������ʱ */
	while (1) {
		/* L0 �� */
		if (lineList[triList[k].L0].useCount < 2) {	//�ж��ǲ��ǿ���չ��
			//����չ��
			long tuo = -1;

			if (lineList[triList[k].L0].p0 == lineList[triList[k].L1].p0 
				|| lineList[triList[k].L0].p1 == lineList[triList[k].L1].p0) {
				tuo = lineList[triList[k].L1].p1;
			}
			if (lineList[triList[k].L0].p0 == lineList[triList[k].L1].p1 
				|| lineList[triList[k].L0].p1 == lineList[triList[k].L1].p1) {
				tuo = lineList[triList[k].L1].p0;
			}

			usablePointList.clear();
			double Fuhao = 0, Fu = 0;

			Fuhao = F(lineList[triList[k].L0], tuo);

			for (long i = 0; i < pointList.size(); ++i) {
				if (lineList[triList[k].L0].p0 != i && 
					lineList[triList[k].L0].p1 != i && 
					lineList[triList[k].L1].p0 != i && 
					lineList[triList[k].L1].p1 != i &&
					lineList[triList[k].L2].p0 != i && 
					lineList[triList[k].L2].p1 != i) {
					//���������εĶ���
					Fu = F(lineList[triList[k].L0], i);

					if (Fuhao * Fu < 0) {	//���
						usablePointList.push_back(i);
					}
				}
			}

			if (usablePointList.size() > 0) {
				int idx = -1;
				idx = Max(lineList[triList[k].L0], usablePointList);

				long lineIndex1 = -1, lineIndex2 = -1;
				int cout1 = 0, cout2 = 0;
				Line line1, line2;

				line1.p0 = lineList[triList[k].L0].p0;
				line1.p1 = idx;
				line2.p0 = lineList[triList[k].L0].p1;
				line2.p1 = idx;

				for (long i = 0; i < lineList.size(); ++i) {
					if (line1 == lineList[i]) {
						lineIndex1 = i;
						cout1 = lineList[lineIndex1].useCount;
					}

					if (line2 == lineList[i]) {
						lineIndex2 = i;
						cout2 = lineList[lineIndex2].useCount;
					}
				}

				if (cout1 < 2 && cout2 < 2) {
					Tri tri;
					tri.L0 = triList[k].L0;

					if (cout1 == 0) {
						Line line;
						line.p0 = lineList[triList[k].L0].p0;
						line.p1 = idx;
						line.useCount = 1;
						lineList.push_back(line);
						tri.L1 = lineList.size() - 1;
					}

					if (cout1 == 1) {
						lineList[lineIndex1].useCount = 2;
						tri.L1 = lineIndex1;
					}

					if (cout2 == 0) {
						Line line;
						line.p0 = lineList[triList[k].L0].p1;
						line.p1 = idx;
						line.useCount = 1;
						lineList.push_back(line);
						tri.L2 = lineList.size() - 1;
					}

					if (cout2 == 1) {
						lineList[lineIndex2].useCount = 2;
						tri.L2 = lineIndex2;
					}

					triList.push_back(tri);
				}
			}
			lineList[triList[k].L0].useCount = 2;
		}
		/* L1 �� */
		if (lineList[triList[k].L1].useCount < 2) {
			//����չ��
			long tuo = -1;

			if (lineList[triList[k].L1].p0 == lineList[triList[k].L0].p0 ||
				lineList[triList[k].L1].p1 == lineList[triList[k].L0].p0) {
				tuo = lineList[triList[k].L0].p1;
			}
			if (lineList[triList[k].L1].p0 == lineList[triList[k].L0].p1 || 
				lineList[triList[k].L1].p1 == lineList[triList[k].L0].p1) {
				tuo = lineList[triList[k].L0].p0;
			}

			usablePointList.clear();

			double Fuhao = 0, Fu = 0;
			Fuhao = F(lineList[triList[k].L1], tuo);

			for (long i = 0; i < pointList.size(); ++i) {		//�ҵ����õĶ���
				if (lineList[triList[k].L0].p0 != i && 
					lineList[triList[k].L0].p1 != i && 
					lineList[triList[k].L1].p0 != i && 
					lineList[triList[k].L1].p1 != i && 
					lineList[triList[k].L2].p0 != i && 
					lineList[triList[k].L2].p1 != i) {
					//���������εĶ���
					Fu = F(lineList[triList[k].L1], i);

					if (Fuhao * Fu < 0) {
						//���

						usablePointList.push_back(i);
					}
				}
			}
			if (usablePointList.size() > 0) {
				int idx = -1;
				idx = Max(lineList[triList[k].L1], usablePointList);

				long lineIndex1 = -1, lineIndex2 = -1;
				int cout1 = 0, cout2 = 0;
				Line line1, line2;

				line1.p0 = lineList[triList[k].L1].p0;
				line1.p1 = idx;
				line2.p0 = lineList[triList[k].L1].p1;
				line2.p1 = idx;

				for (long i = 0; i < lineList.size(); ++i) {
					if (line1 == lineList[i]) {
						lineIndex1 = i;
						cout1 = lineList[lineIndex1].useCount;
					}

					if (line2 == lineList[i]) {
						lineIndex2 = i;
						cout2 = lineList[lineIndex2].useCount;
					}
				}

				if (cout1 < 2 && cout2 < 2) {
					Tri tri;
					tri.L0 = triList[k].L1;

					if (cout1 == 0) {
						Line line;
						line.p0 = lineList[triList[k].L1].p0;
						line.p1 = idx;
						line.useCount = 1;
						lineList.push_back(line);
						tri.L1 = lineList.size() - 1;
					}
					if (cout1 == 1) {
						lineList[lineIndex1].useCount = 2;
						tri.L1 = lineIndex1;
					}

					if (cout2 == 0) {
						Line line;
						line.p0 = lineList[triList[k].L1].p1;
						line.p1 = idx;
						line.useCount = 1;
						lineList.push_back(line);
						tri.L2 = lineList.size() - 1;
					}
					if (cout2 == 1) {
						lineList[lineIndex2].useCount = 2;
						tri.L2 = lineIndex2;
					}
					triList.push_back(tri);
				}
			}
			lineList[triList[k].L1].useCount = 2;
		}
		/* L2 �� */
		if (lineList[triList[k].L2].useCount < 2) {
			long tuo = -1;
			if (lineList[triList[k].L2].p0 == lineList[triList[k].L0].p0 || 
				lineList[triList[k].L2].p1 == lineList[triList[k].L0].p0) {
				tuo = lineList[triList[k].L0].p1;
			}
			if (lineList[triList[k].L2].p0 == lineList[triList[k].L0].p1 ||
				lineList[triList[k].L2].p1 == lineList[triList[k].L0].p1) {
				tuo = lineList[triList[k].L0].p0;
			}

			usablePointList.clear();
			double Fuhao = 0, Fu = 0;
			Fuhao = F(lineList[triList[k].L2], tuo);

			for (long i = 0; i < pointList.size(); ++i) {
				if (lineList[triList[k].L0].p0 != i && 
					lineList[triList[k].L0].p1 != i && 
					lineList[triList[k].L1].p0 != i && 
					lineList[triList[k].L1].p1 != i && 
					lineList[triList[k].L2].p0 != i && 
					lineList[triList[k].L2].p1 != i) {
					Fu = F(lineList[triList[k].L2], i);

					if (Fuhao * Fu < 0) {
						usablePointList.push_back(i);
					}
				}
			}

			if (usablePointList.size() > 0) {
				int idx = -1;
				idx = Max(lineList[triList[k].L2], usablePointList);

				long lineIndex1 = -1, lineIndex2 = -1;
				int cout1 = 0, cout2 = 0;
				Line line1, line2;

				line1.p0 = lineList[triList[k].L2].p0;
				line1.p1 = idx;
				line2.p0 = lineList[triList[k].L2].p1;
				line2.p1 = idx;

				for (long i = 0; i < lineList.size(); ++i) {
					if (line1 == lineList[i]) {
						lineIndex1 = i;
						cout1 = lineList[lineIndex1].useCount;
					}

					if (line2 == lineList[i]) {
						lineIndex2 = i;
						cout2 = lineList[lineIndex2].useCount;
					}
				}

				if (cout1 < 2 && cout2 < 2) {
					Tri tri;
					tri.L0 = triList[k].L2;

					if (cout1 == 0) {
						Line line;
						line.p0 = lineList[triList[k].L2].p0;
						line.p1 = idx;
						line.useCount = 1;
						lineList.push_back(line);
						tri.L1 = lineList.size() - 1;
					}
					if (cout1 == 1) {
						lineList[lineIndex1].useCount = 2;
						tri.L1 = lineIndex1;
					}

					if (cout2 == 0) {
						Line line;
						line.p0 = lineList[triList[k].L2].p1;
						line.p1 = idx;
						line.useCount = 1;
						lineList.push_back(line);
						tri.L2 = lineList.size() - 1;
					}
					if (cout2 == 1) {
						lineList[lineIndex2].useCount = 2;
						tri.L2 = lineIndex2;
					}
					triList.push_back(tri);
				}

			}
			lineList[triList[k].L2].useCount = 2;

		}

		k++;
		if (k == triList.size()) {
			std::cout << "TIN build over" << std::endl;
			break;
		}
	}
}

/*
	@Function Name: writeFile
	@Function param: void
	@Function return value: void   =>   ��������TINд�뵽�ļ���
*/
void TIN::writeFile() {
	FILE* vertexInput = fopen("input.txt","w");
	FILE* triInput = fopen("Tin.txt", "w");

	if (vertexInput == nullptr || triInput == nullptr) {
		std::cout << "file open error" << std::endl;
		goto EXIT;
	}
	
	for (std::vector<Point>::iterator it = pointList.begin(); it != pointList.end(); ++it) {
		fprintf(vertexInput, "%lf\t%lf\t%lf\n", it->x, it->y, it->z);
	}
	std::cout << "Vertex Info write Over" << std::endl;
        
	for (std::vector<Tri>::iterator it = triList.begin(); it != triList.end(); ++it) {
		fprintf(triInput, "%d\t%d\t%d\n", this->lineList[it->L0].p1, this->lineList[it->L1].p0, this->lineList[it->L2].p1);
	}

	std::cout << "Edge Info write Over" << std::endl;

	EXIT:
	fclose(vertexInput);
	fclose(triInput);
}
