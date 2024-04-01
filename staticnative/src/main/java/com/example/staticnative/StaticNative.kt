package com.example.staticnative

class StaticNative {

    /**
     * A native method that is implemented by the 'staticnative' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'staticnative' library on application startup.
        init {
            System.loadLibrary("staticnative")
        }
    }
}