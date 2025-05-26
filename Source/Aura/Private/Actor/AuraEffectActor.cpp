// Copyright by MapleNaaa


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(StaticMesh);
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		// StaticClass 获取类的类型 -> UClass
		// https://blog.csdn.net/j756915370/article/details/117913118?ops_request_misc=%257B%2522request%255Fid%2522%253A%25221850cf0a8c494bb14fe59b93c76b9340%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=1850cf0a8c494bb14fe59b93c76b9340&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-117913118-null-null.142^v102^pc_search_result_base1&utm_term=ue5%20staticclass&spm=1018.2226.3001.4187
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	// bindUobject -> 单播
	// addUobject -> 多播
	// bindDynamic -> 动态单播
	// addDynamic -> 动态多播  -> UFunction()
	// https://blog.csdn.net/Motarookie/article/details/140872887?fromshare=blogdetail&sharetype=blogdetail&sharerId=140872887&sharerefer=PC&sharesource=qq_60536076&sharefrom=from_link
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}

