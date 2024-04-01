package com.example.jni.dynamic;

public class JniOnloadTest {
    public native int  javaAdd(int x, int y);
    public native String javaSayHi();

    static {
        System.loadLibrary("dynamicnative");
    }
}
