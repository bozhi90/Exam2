#include "mbed_rpc.h"
#include "accelerator_capture.h"

BufferedSerial pc(USBTX, USBRX);
bool runAC = false;

Thread thread_AC;

/******************************************************************************/
void function_RPC () {                                          // RPC接收
    char buf[256], outbuf[256];

    FILE *devin = fdopen(&pc, "r");
    FILE *devout = fdopen(&pc, "w");
    while(1) {
        memset(buf, 0, 256);
        for (int i = 0; ; i++) {
            char recv = fgetc(devin);
            if (recv == '\n') {
                printf("\r\n");
                break;
            }
            buf[i] = fputc(recv, devout);
        }
        RPC::call(buf, outbuf);
        printf("%s\r\n", outbuf);
    }
}
/******************************************************************************/
void Accelerator_capture (Arguments *in, Reply *out) {
    runAC = true;
    thread_AC.start(function_AC);
}
RPCFunction AC(&Accelerator_capture, "Accelerator_capture");
/******************************************************************************/
void Accelerator_capture_stop (Arguments *in, Reply *out) {
    runAC = false;
}
RPCFunction AC_stop(&Accelerator_capture_stop, "Accelerator_capture_stop");
/******************************************************************************/