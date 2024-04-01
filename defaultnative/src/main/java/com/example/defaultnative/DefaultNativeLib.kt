package com.example.defaultnative

import android.annotation.SuppressLint
import android.util.Log
import androidx.arch.core.util.Function

class DefaultNativeLib {
    var imageList: MutableList<Int> = mutableListOf(
        R.drawable.ic_tx1,
        R.drawable.ic_tx2,
        R.drawable.ic_tx3,
        R.drawable.ic_tx4,
        R.drawable.ic_tx5
    )
    var dataList = mutableListOf<Person>()
    private var addFun: Function1<Person, Any>? = null
    private var addFun2: Function1<Person, Any>? = null
    private var addFun3: Function1<Person, Any>? = null
    private var removeFun: Function1<String, Any>? = null
    private var notifyCall: Function0<Any>? = null
    private var nameCall: Function0<String>? = null
    private var emailCall: Function0<String>? = null

    fun addPerCall(function: Function1<Person, Any>): DefaultNativeLib {
        this.addFun = function
        return this
    }

    fun addPer2Call(function: Function1<Person, Any>): DefaultNativeLib {
        this.addFun2 = function
        return this
    }

    fun addPer3Call(function: Function1<Person, Any>): DefaultNativeLib {
        this.addFun3 = function
        return this
    }

    fun removeCall(function: Function1<String,Any>): DefaultNativeLib {
        this.removeFun = function
        return this
    }

    fun notifyCall(function: Function0<Any>): DefaultNativeLib {
        this.notifyCall = function
        return this
    }

    fun addNameCall(function: Function0<String>): DefaultNativeLib {
        this.nameCall = function
        return this
    }

    fun addEmailCall(function: Function0<String>): DefaultNativeLib {
        this.emailCall = function
        return this
    }

    fun getName(): String {
        return nameCall?.invoke()?: ""
    }

    fun getEmail(): String {
        return emailCall?.invoke()?: ""
    }

    /**
     * A native method that is implemented by the 'defaultnative' native library,
     * which is packaged with this application.
     */
    /**
     * A native method that is implemented by the 'cadd' native library,
     * which is packaged with this application.
     */
    //添加人员
    external fun addPerson(id: String, name: String, text: String, imageId: Int)
    //添加人员
    external fun createPerson(): Person
    //删除成员
    external fun removePerson(id: String)
    //删除成员
    external fun removePerson2(person: Person)

    companion object {
        // Used to load the 'defaultnative' library on application startup.
        init {
            System.loadLibrary("defaultnative")
        }
    }

    fun addPer(person: Person){
        addFun?.invoke(person)
    }

    fun addPer2(id: String, name: String, text: String, imageId: Int){
        this.addFun2?.invoke(Person(id, name, text, imageList[imageId]))
        Log.d("TAG", "addPer3: $id  $name  $text  $imageId")
    }

    fun addPer3(id: String){
            Log.d("TAG", "addPer3: $id")
//            dataList.add(Person("1111", binding.etName.text.toString(), binding.etEmail.text.toString(), imageList[Random.nextInt(5)]))
//            binding.rv.adapter?.notifyDataSetChanged()
    }

    fun removePer(removeId: String){
        removeFun?.invoke(removeId)
    }

    fun notifyDataChange(){
        this.notifyCall?.invoke()
    }
}