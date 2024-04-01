package com.example.jnanative1

class NativeLib {

    /**
     * A native method that is implemented by the 'jnanative1' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'jnanative1' library on application startup.
        init {
            System.loadLibrary("jnanative1")
        }
    }
}