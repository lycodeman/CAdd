//
// Created by cd-yong.li on 2023/11/16.
//

#include "POSOfflineServiceApiI.h"
#include <android/log.h>
void POSOfflineServiceApiI::run() {
    printf("Hello from POSOfflineServiceApiI!\n");
    __android_log_print(ANDROID_LOG_DEBUG, "JNI", "Hello from POSOfflineServiceApiI!");
}
