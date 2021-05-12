int DataXYZ[10][200][30];
int data_num = 0;
int index_num = 0;
int der[200];

void GUI_design (void) {
    int aX, aY;

    for (int i = 0; i < index_num; i++) {
        aX = DataXYZ[data_num][i + 1][0] - DataXYZ[data_num][i][0];
        aY = DataXYZ[data_num][i + 1][1] - DataXYZ[data_num][i][1];


    }
}