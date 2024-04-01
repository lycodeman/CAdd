package com.example.jnanative

class JNANativeLib {

    /**
     * A native method that is implemented by the 'jnanative' native library,
     * which is packaged with this application.
     */
    external fun add(a: Int, b: Int): Int

    companion object {
        // Used to load the 'jnanative' library on application startup.
        init {
//            System.loadLibrary("jnanative")
        }
    }
}