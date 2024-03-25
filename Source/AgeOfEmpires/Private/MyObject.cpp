#include "MyObject.h"

UMyObject* UMyObject::Instance = nullptr;

UMyObject* UMyObject::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UMyObject>();
        Instance->AddToRoot(); // 防止垃圾回收
    }
    return Instance;
}

UMyObject::UMyObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // 初始化全局变量
    GlobalValue = 0;
}
