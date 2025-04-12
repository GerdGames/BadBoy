// Fill out your copyright notice in the Description page of Project Settings.


#include "BadBoy_XML_SaveGame.h"


void UBadBoy_XML_SaveGame::SetCash(float cash)
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	FXmlNode* cashTag = root->FindChildNode("Cash");

	if (cashTag == nullptr)
	{
		root->AppendChildNode("Cash", FString::SanitizeFloat(cash));
	}
	else
	{
		cashTag->SetContent(FString::SanitizeFloat(cash));
	}

	XmlToString(*root, FString(), GameDataXML);
}

float UBadBoy_XML_SaveGame::GetCash()
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	FXmlNode* cashTag = root->FindChildNode("Cash");

	if (cashTag == nullptr)
	{
		root->AppendChildNode("Cash", FString::SanitizeFloat(0.0));
		cashTag = root->FindChildNode("Cash");
	}

	return FCString::Atof(*cashTag->GetContent());
}

void UBadBoy_XML_SaveGame::SetHealth(float health)
{
}

float UBadBoy_XML_SaveGame::GetHealth()
{
	return 0.0f;
}

void UBadBoy_XML_SaveGame::XmlToString(const FXmlNode& Node, const FString& Indent, FString& Output)
{
	// Write the tag
	Output += Indent + FString::Printf(TEXT("<%s"), *Node.GetTag());
	for (const FXmlAttribute& Attribute : Node.GetAttributes())
	{
		FString EscapedValue = Attribute.GetValue();
		EscapedValue.ReplaceInline(TEXT("&"), TEXT("&amp;"), ESearchCase::CaseSensitive);
		EscapedValue.ReplaceInline(TEXT("\""), TEXT("&quot;"), ESearchCase::CaseSensitive);
		EscapedValue.ReplaceInline(TEXT("'"), TEXT("&apos;"), ESearchCase::CaseSensitive);
		EscapedValue.ReplaceInline(TEXT("<"), TEXT("&lt;"), ESearchCase::CaseSensitive);
		EscapedValue.ReplaceInline(TEXT(">"), TEXT("&gt;"), ESearchCase::CaseSensitive);
		Output += FString::Printf(TEXT(" %s=\"%s\""), *Attribute.GetTag(), *EscapedValue);
	}

	// Write the node contents
	const FXmlNode* FirstChildNode = Node.GetFirstChildNode();
	if (FirstChildNode == nullptr)
	{
		const FString& Content = Node.GetContent();
		if (Content.Len() == 0)
		{
			Output += TEXT(" />") LINE_TERMINATOR;
		}
		else
		{
			Output += TEXT(">") + Content + FString::Printf(TEXT("</%s>"), *Node.GetTag()) + LINE_TERMINATOR;
		}
	}
	else
	{
		Output += TEXT(">") LINE_TERMINATOR;
		for (const FXmlNode* ChildNode = FirstChildNode; ChildNode != nullptr; ChildNode = ChildNode->GetNextNode())
		{
			XmlToString(*ChildNode, Indent + TEXT("\t"), Output);
		}
		Output += Indent + FString::Printf(TEXT("</%s>"), *Node.GetTag()) + LINE_TERMINATOR;
	}
}
