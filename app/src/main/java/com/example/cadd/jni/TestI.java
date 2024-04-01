package com.example.cadd.jni;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface TestI extends Library {

//    TestI INSTANCE = Native.load("toolchains1", TestI.class);

    String run();

    int getChains1();

//    TestI INSTANCE_2 = Native.load("toolchains2", TestI.class);
    TestI INSTANCE_3 = Native.load("toolchains2", TestI.class);


}
