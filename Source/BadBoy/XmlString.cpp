#include "XmlString.h"

FString XmlString::ToString()
{
	FString Xml = TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>") LINE_TERMINATOR;

	const FXmlNode* CurrentNode = GetRootNode();

	//WriteNodeHierarchy(*CurrentNode, FString(), Xml);

	return Xml;
}

