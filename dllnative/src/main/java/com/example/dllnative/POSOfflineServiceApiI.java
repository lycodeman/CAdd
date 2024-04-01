package com.example.dllnative;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface POSOfflineServiceApiI extends Library {

    POSOfflineServiceApiI INSTANCE = (POSOfflineServiceApiI) Native.loadLibrary("dllnative", POSOfflineServiceApiI.class);

    void run();
    void myFunction();

}
