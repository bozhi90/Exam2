#include "stm32l475e_iot01_accelero.h"
#include "gesture_UI.h"
#include "GUI_design.h"

InterruptIn btnRecord(USER_BUTTON);
EventQueue queue;
Thread t;

bool runUI = false;
int sel;
//int DataXYZ[10][200][30];
int Date[10] = {0};
//int data_num = 0;
//int index_num = 0;

int16_t tDataXYZ[3] = {0};
int idR[32] = {0};
int indexR = 0;

Thread thread_GUI(osPriorityNormal);

void record(void) {
   if (index_num == 199) return;
   index_num += 1;
   BSP_ACCELERO_AccGetXYZ(tDataXYZ);
   DataXYZ[data_num][index_num][0] = tDataXYZ[0];
   DataXYZ[data_num][index_num][1] = tDataXYZ[1];
   DataXYZ[data_num][index_num][2] = tDataXYZ[2];
   printf("%d, %d, %d\n", tDataXYZ[0], tDataXYZ[1], tDataXYZ[2]);
}

void startRecord(void) {
   if (data_num == 9) return;;
   sel = 0;
   runUI = true;
   data_num += 1;
   index_num = 0;
   printf("---start---\n");
   idR[indexR++] = queue.call_every(2ms, record);
   indexR = indexR % 32;
}

void stopRecord(void) {
   runUI = false;
   printf("---stop---\n");
   for (auto &i : idR)
      queue.cancel(i);
   printf("data_num = %d, index_num = %d, sel = %d\n", data_num, index_num, sel);
}

void function_AC () {
   thread_GUI.start(function_GUI);
   printf("Start accelerometer init\n");
   BSP_ACCELERO_Init();
   t.start(callback(&queue, &EventQueue::dispatch_forever));
   btnRecord.fall(queue.event(startRecord));
   btnRecord.rise(queue.event(stopRecord));
}