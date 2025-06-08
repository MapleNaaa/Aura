// Copyright by MapleNaaa


#include "AbilitySystem/Data/AuraAttributesDataAsset.h"

FAuraAttributeData UAuraAttributesDataAsset::FindAttributeDataByTag(const FGameplayTag AttributeTag, bool bLogNotFound)
{
	for (FAuraAttributeData AttributeData : AttributesInformation)
	{
		if (AttributeData.AttributeTag == AttributeTag)
		{
			return AttributeData;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Attribute Data not found by tag [%s], please check in AuraAttributesDataAsset.cpp"), *AttributeTag.ToString());
	}
	
	return FAuraAttributeData();
}
