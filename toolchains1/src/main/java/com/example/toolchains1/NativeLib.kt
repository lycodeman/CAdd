package com.example.toolchains1

class NativeLib {

    /**
     * A native method that is implemented by the 'toolchains1' native library,
     * which is packaged with this application.
     */
//    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'toolchains1' library on application startup.
        init {
//            System.loadLibrary("toolchains1")
        }
    }
}