plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")
}

android {
    namespace = "com.example.cadd"
    compileSdk = 33

    defaultConfig {
        applicationId = "com.example.cadd"
        minSdk = 24
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                //c、c++文件编译的时候用那些指令集
//                abiFilters "arm64-v8a";
//            abiFilters.addAll(mutableSetOf("armeabi-v7a", "arm64-v8a"))
                abiFilters.addAll(mutableSetOf("arm64-v8a"))
            }

        }
        //打包脚本，只输出arm64-v8a指令集
        ndk {
//            abiFilters.addAll(mutableSetOf("armeabi-v7a", "arm64-v8a"))
            abiFilters.addAll(mutableSetOf("arm64-v8a"))
        }

//        ndk{
//            moduleName = "jnidemo3"
//            abiFilters.addAll(mutableSetOf("x86","armeabi-v7a","arm64-v8a"))
//            ldLibs?.add("log")
//        }
    }
    sourceSets.getByName("main") {
        // Changes the directory for Java sources. The default directory is
        // 'src/main/java'.
        jniLibs.srcDirs("src/main/jniLibs")
    }


    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
        getByName("debug") {
            isJniDebuggable = true
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }
    externalNativeBuild {
        cmake {
            path = file("src/main/CMakeLists.txt")
            version = "3.22.1"
        }
//        ndkBuild {
//            path = file("src/main/jni/Android.mk")
//        }
    }
    buildFeatures {
        viewBinding = true
    }



}

dependencies {

    implementation("androidx.core:core-ktx:1.9.0")
    implementation("androidx.appcompat:appcompat:1.6.1")
    implementation("com.google.android.material:material:1.8.0")
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")
//    implementation(project(mapOf("path" to ":staticnative")))
//    implementation(project(mapOf("path" to ":dynamicnative")))
    implementation(project(mapOf("path" to ":dlopennative")))
//    api(project(mapOf("path" to ":jnanative")))
//    api(project(mapOf("path" to ":jnanative1")))
    implementation(project(mapOf("path" to ":defaultnative")))
    implementation(project(mapOf("path" to ":dllnative")))
    implementation(project(mapOf("path" to ":toolchains1")))
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.1.5")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.5.1")

}