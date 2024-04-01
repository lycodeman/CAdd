package com.example.cadd

import android.annotation.SuppressLint
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.cadd.databinding.ActivityMainBinding
import com.example.cadd.jni.TestI
import com.example.defaultnative.DefaultNativeLib
import com.example.dllnative.DllInterface
import com.example.dllnative.DllNativeLib
import com.example.dllnative.POSOfflineServiceApiI
import com.example.dlopennative.DLOpenNativeLib
import java.io.File
import kotlin.random.Random


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private var dataList = mutableListOf<com.example.defaultnative.Person>()
    var imageList: MutableList<Int> = mutableListOf(
        com.example.defaultnative.R.drawable.ic_tx1,
        com.example.defaultnative.R.drawable.ic_tx2,
        com.example.defaultnative.R.drawable.ic_tx3,
        com.example.defaultnative.R.drawable.ic_tx4,
        com.example.defaultnative.R.drawable.ic_tx5
    )

    @SuppressLint("NotifyDataSetChanged")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val defaultNativeLib = DefaultNativeLib()
        defaultNativeLib
            .addPer2Call {
                this.dataList.add(it)
            }
            .addPerCall {
                this.dataList.add(it)
            }
            .addPer3Call {
                this.dataList.add(it)
            }
            .removeCall { id ->
                this.dataList.removeIf { it.id == id }
            }
            .addEmailCall {
                binding.etEmail.text?.toString()?:""
            }
            .addNameCall {
                binding.etName.text?.toString()?:""
            }
            .notifyCall {
                runOnUiThread {
                    binding.rv.adapter?.notifyDataSetChanged()
                }
                ""
            }.dataList = dataList

        binding.rv.apply {
            layoutManager = LinearLayoutManager(this@MainActivity)
            adapter = object : RecyclerView.Adapter<RecyclerView.ViewHolder>() {
                override fun onCreateViewHolder(
                    parent: ViewGroup,
                    viewType: Int
                ): RecyclerView.ViewHolder {
                    return object : RecyclerView.ViewHolder(
                        LayoutInflater.from(this@MainActivity)
                            .inflate(R.layout.item, binding.rv, false)
                    ) {}
                }

                override fun getItemCount(): Int {
                    return dataList.size
                }

                override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
                    holder.itemView.findViewById<TextView>(R.id.tv_name).text =
                        dataList[position].name
                    holder.itemView.findViewById<TextView>(R.id.tv_email).text =
                        dataList[position].email
                    holder.itemView.findViewById<ImageView>(R.id.img).setImageResource(imageList[dataList[position].image])
                    holder.itemView.findViewById<ImageView>(R.id.img_remove).setOnClickListener {
                        //第一种方式
                        defaultNativeLib.removePerson(dataList[position].id)
                        defaultNativeLib.notifyDataChange()
                        //第二种方式
//                        defaultNativeLib.removePerson2(dataList[position])
                    }
                }
            }
        }
        binding.btAdd.setOnClickListener {
            val file = File(externalCacheDir?.absolutePath + "/jni")
            if (file.exists()) {
                file.delete()
            }
            file.mkdirs()
            File(externalCacheDir?.path + "/jni/test.txt").writeText("hello world")
            /************以上测试ok***********/
            //defaultnative库 初步尝试JNI，调用本地方法
            if (binding.etEmail.text.isNotBlank() && binding.etName.text.isNotBlank()) {
                //第一种方式
//                defaultNativeLib.addPerson(
//                    dataList.size.toString(),
//                    binding.etName.text.toString(),
//                    binding.etEmail.text.toString(),
//                    Random.nextInt(5)
//                )
                //第二种方式 目前连续添加有点问题
//                dataList.add(defaultNativeLib.createPerson())
//                defaultNativeLib.notifyDataChange()
            }
            //staticnative库 静态注入方法
//            Log.e("TAG", "onCreate: " + StaticNative().stringFromJNI())
            //dynamicnative库 动态注入方法
//            Log.e("TAG", "onCreate: " + JniOnloadTest().javaAdd(Random .nextInt(5),Random .nextInt(6)) )
            //jnanative1库 jna方式访问so
//            Log.e("TAG", "jna add: " + WerI.INSTANCE.add(Random.nextInt(5), Random.nextInt(6)))
//            val _Person = WerI._Person(
//                1,
//                "LYHJJKK".toByteArray(),
//                "XXX".toByteArray()
//            )
//            val structInfo = WerI.INSTANCE.getStructInfo(
//                _Person
//            )
//            Log.e("TAG", "jna add: " + structInfo)
//            Log.e("TAG", "jna add: " + _Person.name)
//            Log.e("TAG", "jna add: " + _Person.age)
//            Log.e("TAG", "jna add: " + _Person.type)
//            val retry = IntBuffer.allocate(1)
//            WerI.INSTANCE.getAge(retry)
//            Log.e("TAG", "jna getAge: " + retry[0])
//            val bytename = ByteArray(50)
//            val call = ByteBuffer.wrap(bytename)
//            val name = ByteBuffer.wrap("asdkj".toByteArray())
//            WerI.INSTANCE.getName( name, call)
//            Log.e("TAG", "jna getNamez: " + call.array().toString(Charsets.UTF_8))

            /************以上测试ok***********/
            //dlopen打开so，这个文件必须是elf的文件
            Log.e("TAG", "onCreate: " + DLOpenNativeLib().add(Random.nextInt(5), Random.nextInt(6)))
            //jna方式访问so(so是通过ndk编译的)
            //编译命令： $NDK/toolchains/llvm/prebuilt/darwin-x86_64/bin/aarch64-linux-android33-clang++ -fPIC -shared hello.cpp -o libhello.so
//            Log.e("TAG", "JNANativeLib add: " + JNANativeLib().add(Random.nextInt(5), Random.nextInt(6)))

            //dllnative库 访问dll文件底层调用的是dlopen，这个文件必须是elf的文件
//            DllInterface.INSTANCE2.myFunction()
//            DllNativeLib().printHelloWorld()
//            POSOfflineServiceApiI.INSTANCE.myFunction()
            //本地加载so文件
            Log.e("TAG", "JNANativeLib add: " + stringFromJNI())
//            Log.e("TAG", "JNANativeLib add: " + TestI.INSTANCE.chains1)
//            Log.e("TAG", "JNANativeLib add: " + TestI.INSTANCE.run())
//            Log.e("TAG", "JNANativeLib add: " + com.example.android.`1test`.MainActivity().stringFromJNI())


        }
    }

    external fun stringFromJNI(): String


    companion object {
        init {
            //需要提前加载
//            System.loadLibrary("toolchains1")
            System.loadLibrary("cadd")

//            System.loadLibrary("toolchains2")

//            System.loadLibrary("android_test1")
//            System.loadLibrary("Qt5Core")
//            System.loadLibrary("c++_shared")

        }
    }
}