// Copyright by MapleNaaa


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 100.f;
	// 此角色每秒钟会被考虑进行复制的频率，用于确定网络更新时间

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	/** Minimal : Only replicate minimal gameplay effect info. Note: this does not work for Owned AbilitySystemComponents (Use Mixed instead).
	 *  GE not replicated. Gameplay Cues and Gameplay Tags to all Clients;
	 *  Multiplayer -> Al-Controller
	 */

	/** Mixed : Only replicate minimal gameplay effect info to simulated proxies but full info to owners and autonomous proxies
	 * GE replicated to the owning client only. GCues and GTags all
	 * Multiplayer -> Player-Controller
	 */
	
	/** Full : Replicate full gameplay info to all
	 *  All
	 *  Single Player
	 */


	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
