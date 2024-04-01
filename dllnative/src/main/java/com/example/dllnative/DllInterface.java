package com.example.dllnative;


import com.sun.jna.Library;
import com.sun.jna.Native;

public interface DllInterface extends Library {
//    String filePath = DllInterface.class.getResource("").getPath().replaceFirst("/","").replaceAll("%20"," ")+"mylibrary.dll";
    DllInterface INSTANCE = (DllInterface) Native.loadLibrary("/Users/ly/AndroidStudioProjects/CAdd/dllnative/src/main/assets/mylibrary.dll",
        DllInterface.class);
    DllInterface INSTANCE2 = (DllInterface) Native.load("/data/data/com.example.cadd/files/jni/mylibrary.dll", DllInterface.class);
//    Native.loa("mylibrary.dll", DllInterface.class);


    void myFunction();
}
