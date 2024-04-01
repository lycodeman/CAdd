package com.example.dllnative

class DllNativeLib {

    /**
     * A native method that is implemented by the 'dllnative' native library,
     * which is packaged with this application.
     */
    external fun add(a: Int , b: Int): Int

    companion object {
        // Used to load the 'dllnative' library on application startup.
        init {
            System.loadLibrary("dllnative")
        }
    }

    external fun printHelloWorld()
}