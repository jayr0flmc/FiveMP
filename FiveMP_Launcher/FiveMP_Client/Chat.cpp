#include "stdafx.h"

CChat::CChat()
{

}


CChat::~CChat()
{

}

void CChat::Render()
{
	char chatlength[256];
	float heightupdate = 0.002f;

	for (int i = 0; i < 10; i++) {
		sprintf(chatlength, "%s", chatData[i].message);
		draw_text(0.002f, heightupdate, chatlength, { 255, 255, 255, 255 });

		heightupdate += 0.025f;
	}
}

void CChat::Input()
{
	if (open == true) {
		if (IsKeyJustUp(VK_ESCAPE)) {
			open = false;
		}
		else {
			char test[128];
			sprintf(test, "%s - %d", getchar(), getchar());
			Chat->AddChatMessage(test);
		}
	}
	return;
}

void CChat::AddChatMessage(char string[128])
{
	for (int i = 0; i < 9; i++) {
		strcpy(chatData[i].message, chatData[i+1].message);
	}
	strcpy(chatData[9].message, string);
}

void CChat::Clear()
{
	for (int i = 0; i < 10; i++) {
		strcpy(chatData[i].message, "");
	}
}
