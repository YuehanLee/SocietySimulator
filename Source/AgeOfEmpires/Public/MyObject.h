#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

UCLASS()
class YOURPROJECT_API UMyObject : public UObject
{
    GENERATED_BODY()

public:
    // 获取单例实例的静态方法
    static UMyObject* GetInstance();

    // 确保不会被复制或直接构造
    UMyObject(const FObjectInitializer& ObjectInitializer);

protected:
    // 单例实例
    static UMyObject* Instance;

public:
    // 示例全局变量
    UPROPERTY(BlueprintReadWrite, Category = "Global Variables")
    int32 GlobalValue;
};
