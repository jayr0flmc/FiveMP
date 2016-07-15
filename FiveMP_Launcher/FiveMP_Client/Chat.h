#pragma once
class CChat
{
public:
	bool open = false;

	CChat();
	~CChat();

	void Render();
	void Input(WCHAR key);
	void AddChatMessage(char string[128]);
};