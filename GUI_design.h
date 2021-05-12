int DataXYZ[10][200][30];
int data_num = 0;
int index_num = 0;
int der[200];

void GUI_design (void) {
    int aX, aY;

    for (int i = 0; i < index_num; i++) {
        aX = DataXYZ[data_num][i][0] > 500 || DataXYZ[data_num][i][0] < 500;
        aY = DataXYZ[data_num][i][1] > 500 || DataXYZ[data_num][i][1] < 500;

        if (aX == 1) {
            if (aY == 0) {
                der[i] = 1;
            } else {
                der[i] = 2;
            }
        } else {
            if (aY == 0) {
                der[i] = 3;
            } else {
                der[i] = 4;
            }
        }
    }

}