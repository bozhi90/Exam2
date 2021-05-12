#include "mbed.h"
#include "serial_RPC.h"

Thread thread_RPC;

int main() {
    thread_RPC.start(function_RPC);

    return 0;
}