// Fill out your copyright notice in the Description page of Project Settings.


#include "BadBoy_XML_SaveGame.h"


UBadBoy_XML_SaveGame::UBadBoy_XML_SaveGame()
{
	SetCash(0);

	SetHealth(100);

	//GameDataXML = TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<SAVE_GAME>\n</SAVE_GAME>") LINE_TERMINATOR;
}

UBadBoy_XML_SaveGame::UBadBoy_XML_SaveGame(float cash, float health)
{
	SetCash(cash);

	SetHealth(health);

	//GameDataXML = TEXT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<SAVE_GAME>\n</SAVE_GAME>") LINE_TERMINATOR;
}

void UBadBoy_XML_SaveGame::SetCash(float cash)
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{
		FXmlNode* cashTag = root->FindChildNode("Cash");

		if (cashTag == nullptr)
		{
			root->AppendChildNode("Cash", FString::SanitizeFloat(cash));
		}
		else
		{
			cashTag->SetContent(FString::SanitizeFloat(cash));
		}

		GameDataXML = XmlHeader;

		XmlToString(*root, FString(), GameDataXML);
	}

}

float UBadBoy_XML_SaveGame::GetCash()
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{

		FXmlNode* cashTag = root->FindChildNode("Cash");

		if (cashTag == nullptr)
		{
			root->AppendChildNode("Cash", FString::SanitizeFloat(0.0));
			cashTag = root->FindChildNode("Cash");
		}

		return FCString::Atof(*cashTag->GetContent());
	}

	return 0.0;
}

void UBadBoy_XML_SaveGame::SetHealth(float health)
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{
		FXmlNode* healthTag = root->FindChildNode("Health");

		if (healthTag == nullptr)
		{
			root->AppendChildNode("Health", FString::SanitizeFloat(health));
		}
		else
		{
			healthTag->SetContent(FString::SanitizeFloat(health));
		}

		GameDataXML = XmlHeader;

		XmlToString(*root, FString(), GameDataXML);
	}
}

float UBadBoy_XML_SaveGame::GetHealth()
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{

		FXmlNode* healthTag = root->FindChildNode("Health");

		if (healthTag == nullptr)
		{
			root->AppendChildNode("Health", FString::SanitizeFloat(100.0));
			healthTag = root->FindChildNode("Health");
		}

		return FCString::Atof(*healthTag->GetContent());
	}

	return 100.0;
}

void UBadBoy_XML_SaveGame::SetMove(FString moveName, FUMoveUnlockStruct moveStruct)
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{
		FXmlNode* movesTag = root->FindChildNode("MoveUnlocks");

		if (movesTag == nullptr)
		{
			root->AppendChildNode("MoveUnlocks");
			movesTag = root->FindChildNode("MoveUnlocks");
		}

		FXmlNode* moveTag = movesTag->FindChildNode(moveName);

		if (moveTag == nullptr)
		{
			movesTag->AppendChildNode(moveName);
			moveTag = movesTag->FindChildNode(moveName);
		}

		FXmlNode* unlockTag = moveTag->FindChildNode("Unlocked");

		if (unlockTag == nullptr)
		{
			moveTag->AppendChildNode("Unlocked");
			unlockTag = moveTag->FindChildNode("Unlocked");
		}

		unlockTag->SetContent(moveStruct.unlocked ? "true" : "false");

		GameDataXML = XmlHeader;

		XmlToString(*root, FString(), GameDataXML);
	}
}

FUMoveUnlockStruct UBadBoy_XML_SaveGame::GetMove(FString moveName)
{
	FUMoveUnlockStruct returnStruct = FUMoveUnlockStruct();

	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{
		FXmlNode* movesTag = root->FindChildNode("MoveUnlocks");

		if (movesTag == nullptr)
		{
			root->AppendChildNode("MoveUnlocks");
			movesTag = root->FindChildNode("MoveUnlocks");
		}

		FXmlNode* moveTag = TryGetChildNode(movesTag, moveName);


		FXmlNode* unlockTag = TryGetChildNode(moveTag, "Unlocked", "false");

		if (unlockTag->GetContent() == "true")
			returnStruct.unlocked = true;
		else
			returnStruct.unlocked = false;

		GameDataXML = XmlHeader;

		XmlToString(*root, FString(), GameDataXML);
	}

	return returnStruct;
}

void UBadBoy_XML_SaveGame::SetMoves(TMap<FString, FUMoveUnlockStruct> moves)
{
	TArray<FString> Keys;
	moves.GetKeys(Keys);

	for (FString key : Keys)
	{
		SetMove(key, *moves.Find(key));
	}
}

TMap<FString, FUMoveUnlockStruct> UBadBoy_XML_SaveGame::GetMoves()
{
	TMap<FString, FUMoveUnlockStruct>returnMap = TMap<FString, FUMoveUnlockStruct>();

	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{
		FXmlNode* movesTag = root->FindChildNode("MoveUnlocks");

		if (movesTag == nullptr)
		{
			root->AppendChildNode("MoveUnlocks");
			movesTag = root->FindChildNode("MoveUnlocks");
		}

		TArray<FXmlNode*> moves = movesTag->GetChildrenNodes();

		for (FXmlNode* move : moves)
		{
			FString moveName = move->GetTag();

			FUMoveUnlockStruct moveUnlock = GetMove(moveName);

			returnMap.Add(moveName, moveUnlock);
		}

		GameDataXML = XmlHeader;

		XmlToString(*root, FString(), GameDataXML);
	}

	return returnMap;
}

void UBadBoy_XML_SaveGame::SetLevel(FString levelName, FString episodeName, FULevelCompletionStruct levelStruct)
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{
		FXmlNode* episodesTag = TryGetChildNode(root, "Episodes");

		FXmlNode* episodeTag = TryGetChildNode(episodesTag, episodeName);

		FXmlNode* levelTag = TryGetChildNode(episodeTag, levelName);

		FXmlNode* completeTag = TryGetChildNode(levelTag, "LevelCompleted");
		completeTag->SetContent(levelStruct.levelComplete ? "true" : "false");

		FXmlNode* unlockTag = TryGetChildNode(levelTag, "LevelUnlocked");
		unlockTag->SetContent(levelStruct.levelUnlocked ? "true" : "false");

		FXmlNode* beefyTag = TryGetChildNode(levelTag, "BeefyBarEaten");
		beefyTag->SetContent(levelStruct.beefyBarEaten ? "true" : "false");

		FXmlNode* growthTag = TryGetChildNode(levelTag, "FoodWadGrowth");
		growthTag->SetContent(FString::SanitizeFloat(levelStruct.recordWadGrowth));

		FXmlNode* hangerTag = TryGetChildNode(levelTag, "Hanger");
		hangerTag->SetContent(FString::SanitizeFloat(levelStruct.recordHanger));

		FXmlNode* timeTag = TryGetChildNode(levelTag, "Time");
		timeTag->SetContent(FString::SanitizeFloat(levelStruct.recordTime));

		FXmlNode* wadTag = TryGetChildNode(levelTag, "FoodWad");

		FString foodList = "";
		
		for (int i = 0; i < levelStruct.recordFoodwad.Num(); i++)
		{

			foodList.Append(levelStruct.recordFoodwad[i].ToString());

			if (i < levelStruct.recordFoodwad.Num() - 1)
				foodList.Append(", ");
		}

		wadTag->SetContent(foodList);

		GameDataXML = XmlHeader;

		XmlToString(*root, FString(), GameDataXML);
	}
}

FULevelCompletionStruct UBadBoy_XML_SaveGame::GetLevel(FString levelName, FString episodeName)
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	FULevelCompletionStruct levelStruct = FULevelCompletionStruct();

	if (root != nullptr)
	{
		FXmlNode* episodesTag = TryGetChildNode(root, "Episodes");

		FXmlNode* episodeTag = TryGetChildNode(episodesTag, episodeName);

		FXmlNode* levelTag = TryGetChildNode(episodeTag, levelName);

		FXmlNode* completeTag = TryGetChildNode(levelTag, "LevelCompleted", "false");
		if (completeTag->GetContent() == "true")
			levelStruct.levelComplete = true;
		else
			levelStruct.levelComplete = false;

		FXmlNode* unlockTag = TryGetChildNode(levelTag, "LevelUnlocked", "false");
		if (unlockTag->GetContent() == "true")
			levelStruct.levelUnlocked = true;
		else
			levelStruct.levelUnlocked = false;

		FXmlNode* beefyTag = TryGetChildNode(levelTag, "BeefyBarEaten", "false");
		if (beefyTag->GetContent() == "true")
			levelStruct.beefyBarEaten = true;
		else
			levelStruct.beefyBarEaten = false;

		FXmlNode* growthTag = TryGetChildNode(levelTag, "FoodWadGrowth", "0.0");
		levelStruct.recordWadGrowth = FCString::Atof(*growthTag->GetContent());

		FXmlNode* hangerTag = TryGetChildNode(levelTag, "Hanger", "0.0");
		levelStruct.recordHanger = FCString::Atof(*hangerTag->GetContent());

		FXmlNode* timeTag = TryGetChildNode(levelTag, "Time", "0.0");
		levelStruct.recordTime = FCString::Atof(*timeTag->GetContent());

		FXmlNode* wadTag = TryGetChildNode(levelTag, "FoodWad");

		FString foodList = "";

		for (int i = 0; i < levelStruct.recordFoodwad.Num(); i++)
		{

			foodList.Append(levelStruct.recordFoodwad[i].ToString());

			if (i < levelStruct.recordFoodwad.Num() - 1)
				foodList.Append(", ");
		}

		TArray<FString> recordedWadString;
		wadTag->GetContent().ParseIntoArray(recordedWadString, TEXT(", "));

		TArray<FName> recordedWad;
		for (int i = 0; i < recordedWadString.Num(); i++)
		{
			recordedWad.Add(FName(recordedWadString[i]));
		}

		levelStruct.recordFoodwad = recordedWad;

		GameDataXML = XmlHeader;

		XmlToString(*root, FString(), GameDataXML);
	}

	return levelStruct;
}

void UBadBoy_XML_SaveGame::SetEpisode(FString episodeName, FUEpisode episodeStruct)
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{
		FXmlNode* episodesTag = TryGetChildNode(root, "Episodes");

		FXmlNode* episodeTag = TryGetChildNode(episodesTag, episodeName);

		TArray<FString> Keys;
		episodeStruct.Levels.GetKeys(Keys);

		for (FString levelName : Keys)
		{
			SetLevel(levelName, episodeName, *episodeStruct.Levels.Find(levelName));
		}

	}
}

FUEpisode UBadBoy_XML_SaveGame::GetEpisode(FString episodeName)
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	FUEpisode episodeStruct = FUEpisode();

	if (root != nullptr)
	{
		FXmlNode* episodesTag = TryGetChildNode(root, "Episodes");

		FXmlNode* episodeTag = TryGetChildNode(episodesTag, episodeName);

		TArray< FXmlNode* > levelNodes = episodeTag->GetChildrenNodes();

		for (FXmlNode* levelNode : levelNodes)
		{
			FULevelCompletionStruct levelStruct = GetLevel(levelNode->GetTag(), episodeName);

			episodeStruct.Levels.Add(levelNode->GetTag(), levelStruct);
		}
	}

	return episodeStruct;
}

void UBadBoy_XML_SaveGame::SetEpisodes(TMap<FString, FUEpisode> episodesStruct)
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	if (root != nullptr)
	{
		FXmlNode* episodesTag = TryGetChildNode(root, "Episodes");

		TArray<FString> Keys;
		episodesStruct.GetKeys(Keys);

		for (FString episodeName : Keys)
		{
			SetEpisode(episodeName, *episodesStruct.Find(episodeName));
		}
	}
}

TMap<FString, FUEpisode> UBadBoy_XML_SaveGame::GetEpisodes()
{
	FXmlFile xmlData(GameDataXML, EConstructMethod::ConstructFromBuffer);

	FXmlNode* root = xmlData.GetRootNode();

	TMap<FString, FUEpisode> episodesStruct = TMap<FString, FUEpisode>();

	if (root != nullptr)
	{
		FXmlNode* episodesTag = TryGetChildNode(root, "Episodes");

		TArray<FXmlNode*> episodeNodes = episodesTag->GetChildrenNodes();

		for (FXmlNode* episodeNode : episodeNodes)
		{
			FUEpisode episodeStruct = GetEpisode(episodeNode->GetTag());

			episodesStruct.Add(episodeNode->GetTag(), episodeStruct);
		}
	}

	return episodesStruct;
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

FXmlNode* UBadBoy_XML_SaveGame::TryGetChildNode(FXmlNode* Node, const FString& nodeName)
{
	FXmlNode* returnTag = Node->FindChildNode(nodeName);

	if (returnTag == nullptr)
	{
		Node->AppendChildNode(nodeName);
		returnTag = Node->FindChildNode(nodeName);
	}

	return returnTag;
}

FXmlNode* UBadBoy_XML_SaveGame::TryGetChildNode(FXmlNode* Node, const FString& nodeName, const FString& defaultValue)
{
	FXmlNode* returnTag = Node->FindChildNode(nodeName);

	if (returnTag == nullptr)
	{
		Node->AppendChildNode(nodeName);
		returnTag = Node->FindChildNode(nodeName);

		returnTag->SetContent(defaultValue);
	}

	return returnTag;
}
