// Copyright by MapleNaaa

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IEnemyInterface;
struct FInputActionValue;
class UInputMappingContext; //  这二者作用相同，都是向前声明 #include "InputMappingContext.h"
class UInputAction;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController(); // 在 public 中, 这样能够提供更多的定义方式。
	virtual void PlayerTick(float DeltaTime) override;
	// 处理玩家输入（在 PlayerInput 被更新后立即执行）并调用UpdateRotation()。只有当 PlayerController 拥有一个PlayerInput对象时，才会调用PlayerTick。因此，它只会在本地控制的PlayerController上被调用。

protected:
	virtual void BeginPlay() override; // BeginPlay() 在 protected 范围内部
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	TObjectPtr<IEnemyInterface> LastActor;
	TObjectPtr<IEnemyInterface> ThisActor;
};

