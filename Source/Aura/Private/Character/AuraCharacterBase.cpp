// Copyright by MapleNaaa


#include "Character/AuraCharacterBase.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // 没有必要每一帧都被调用
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon"); 	// 使用 CreateDefaultSubobject 为 Weapon 指针赋值，创造实例。 可以创建 subobject / component
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket")); // 通常在constructor中被使用，如果没有被注册时，相较于AttachToComponent,应该优先使用该方法。
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision); // PrimitiveComponent 设置碰撞。 ECollisionEnabled 枚举 enum

}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

