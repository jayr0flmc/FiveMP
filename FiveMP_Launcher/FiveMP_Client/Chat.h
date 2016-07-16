#pragma once
class CChat
{
public:
	bool open = false;

	CChat();
	~CChat();

	void Render();
	void Input();
	void AddChatMessage(char string[128]);
	void Clear();
};