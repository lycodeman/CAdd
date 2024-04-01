package com.example.dlopennative

class DLOpenNativeLib {

    /**
     * A native method that is implemented by the 'dlopennative' native library,
     * which is packaged with this application.
     */
    external fun add(a: Int, b: Int): String

    companion object {
        // Used to load the 'dlopennative' library on application startup.
        init {
            System.loadLibrary("dlopennative")
        }
    }
}