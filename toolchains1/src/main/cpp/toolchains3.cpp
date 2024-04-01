//
// Created by cd-yong.li on 2023/11/20.
//

#include "toolchains3.h"
#include "toolchains2.h"

int TestToolChains3::getChains3(){
    TestToolChains2 testToolChains2;
    return testToolChains2.getChains2() + 5;
};
