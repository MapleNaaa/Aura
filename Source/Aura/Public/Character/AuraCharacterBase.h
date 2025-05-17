// Copyright  by MapleNaaa

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

// 如果要重构文件结构，可以直接在文件夹中修改，然后删除InterMediate和Binaries，点击uproject用rider打开

class UAttributeSet;

UCLASS(Abstract) // 防止该基类被实例化
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet(){ return AttributeSet; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// TObjectPtr 在打包时，和raw相同，但是在编辑器版本中，有 access tracking 和 lazy loading

	// 骨骼网格组件 / 用于手持武器 / AuraCharacterBase
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
