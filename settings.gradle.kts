pluginManagement {
    repositories {
        google()
        mavenCentral()
        gradlePluginPortal()
    }
}
dependencyResolutionManagement {
    repositoriesMode.set(RepositoriesMode.FAIL_ON_PROJECT_REPOS)
    repositories {
        google()
        mavenCentral()
    }
}

rootProject.name = "CAdd"
include(":app")
include(":dynamicnative")
include(":staticnative")
include(":dlopennative")
include(":jnanative")
include(":jnanative1")
include(":defaultnative")
include(":dllnative")
include(":toolchains1")
