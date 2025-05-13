// Copyright  by MapleNaaa


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // 将运动方向作为角色朝向方向
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	GetCharacterMovement()->bConstrainToPlane = true; // 如果为真，移动将被限制在一个平面上。
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 开始时，人物应该贴在地面上

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
