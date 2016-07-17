#include "stdafx.h"

CChat *CChat::singleInstance = nullptr;

void CChat::AddLine(ChatLine line)
{
	if (vChatLines.size() >= cuChatHistorySize)
		vChatLines.erase(vChatLines.begin());
	vChatLines.push_back(line);
}

CChat::CChat() :uiCarretPos(0)
{

}

CChat* CChat::Get()
{
	if (!singleInstance)
		singleInstance = new CChat();
	return singleInstance;
}


void CChat::RegisterCommandProcessor(int(*callback)(std::string))
{
	_commandProcess = callback;
}

void CChat::Scroll(ScrollRoute route)
{
	if (route == SCROLL_UP)
	{
		iOffset += cuLinesOnScreen;
		if (iOffset > vChatLines.size())
			iOffset = vChatLines.size();
	}
	else if (route == SCROLL_DOWN)
	{
		iOffset -= cuLinesOnScreen;
		if (iOffset < 0)
			iOffset = 0;
	}
}

CChat::~CChat()
{

}

void CChat::Render()
{
	if (!bEnabled)
		return;
	int uiFirstLine = vChatLines.size() - cuLinesOnScreen - iOffset;
	if (uiFirstLine < 0)
		uiFirstLine = 0;
	unsigned int uiLastLine = min(uiFirstLine + cuLinesOnScreen, vChatLines.size());

	float heightupdate = 0.002f;
	for (unsigned int i = uiFirstLine; i < uiLastLine; i++) {
		draw_text(0.002f, heightupdate, vChatLines[i].sLineText.c_str(), vChatLines[i].structColor);
		heightupdate += 0.025f;
	}
	if (bOpened)
	{
		GRAPHICS::DRAW_RECT(0.002f, 0.023f + (0.025f * cuLinesOnScreen), 0.9f, 0.03f, 0, 0, 0, 150);
		float chatInputHeight = 0.002f + (0.025f * cuLinesOnScreen) + 0.005f;
		// Temporary here
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::wstring msgCopy(wsCurrentMessage);
		msgCopy.insert(msgCopy.begin() + uiCarretPos, L'_');
		std::string converted_str = std::string("> ") + converter.to_bytes(msgCopy);

		draw_text(0.002f, chatInputHeight, converted_str.c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });
	}
}

void CChat::Input()
{
	if (bOpened)
		UI::SET_PAUSE_MENU_ACTIVE(false);
}

void CChat::AddChatMessage(std::string text, UINT64 rgba /*= 0xFFFFFFFF*/)
{
	ChatLine tempLine;
	tempLine.structColor = {
		((rgba >> 24) & 0xFF) / 255,
		((rgba >> 16) & 0xFF) / 255,
		((rgba >> 8) & 0xFF) / 255,
		((rgba) & 0xFF) / 255
	};
	tempLine.sLineText = text;
	AddLine(tempLine);
}


void CChat::AddChatMessage(std::string text, unsigned char red /*= 255*/, unsigned char green /*= 255*/, unsigned char blue /*= 255*/, unsigned char alpha /*= 255*/)
{
	ChatLine tempLine;
	tempLine.structColor = {
		red, green, blue, alpha
	};
	tempLine.sLineText = text;
	AddLine(tempLine);
}


void CChat::AddChatMessage(std::string text, color_t color)
{
	ChatLine tempLine;
	tempLine.structColor = color;
	tempLine.sLineText = text;
	AddLine(tempLine);
}

void CChat::Clear()
{
	vChatLines.clear();
	iOffset = 0;
}


void CChat::Toggle()
{
	if (bOpened)
		Close();
	else
		Open();
}


void CChat::Open()
{
	PLAYER::SET_PLAYER_CONTROL(PLAYER::PLAYER_ID(), false, 0);
	bOpened = true;
}


void CChat::Close()
{
	PLAYER::SET_PLAYER_CONTROL(PLAYER::PLAYER_ID(), true, 0);
	bOpened = false;
}

void CChat::ScriptKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	CChat *Chat = CChat::Get();

	if (Chat->bOpened && (isUpNow || wasDownBefore) && (key != VK_RETURN && key != VK_BACK && key != VK_DELETE))
	{
		LPWSTR outChars = new WCHAR[4];
		BYTE keyState[256] = { 0 };
		if (!GetKeyboardState(keyState))
			return;
		int charsTranslated = ToUnicodeEx(key, scanCode, keyState, outChars, 4, 0, GetKeyboardLayout(NULL));
		if (charsTranslated > 0)
		{
			for (int i = 0; i < charsTranslated; ++i)
				Chat->wsCurrentMessage.insert(Chat->wsCurrentMessage.begin() + Chat->uiCarretPos, outChars[i]);
			Chat->uiCarretPos += charsTranslated;
		}
	}

	if (isUpNow || wasDownBefore)
	{
		switch (key)
		{
		case VK_ESCAPE:
			if (Chat->bOpened)
				Chat->Close();
			break;
		case VK_F6:
			Chat->Toggle();
			break;
		case VK_F7:
			Chat->bEnabled = !Chat->bEnabled;
			break;
		case VK_RETURN:
			if (Chat->bOpened)
			{
				if (Chat->wsCurrentMessage.empty())
				{
					Chat->Close();
					break;
				}
				if (Chat->wsCurrentMessage[0] == L'/')
				{
					using convert_type = std::codecvt_utf8<wchar_t>;
					std::wstring_convert<convert_type, wchar_t> converter;
					std::string converted_str = converter.to_bytes(Chat->wsCurrentMessage);
					if (Chat->_commandProcess != nullptr)
						if (Chat->_commandProcess(converted_str) == 1)
						{
							Chat->wsCurrentMessage.clear();
							Chat->Close();
							Chat->uiCarretPos = 0;
							break;
						}
				}
				//SendMessageToServer(wsCurrentMessage);
				using convert_type = std::codecvt_utf8<wchar_t>;
				std::wstring_convert<convert_type, wchar_t> converter;

				std::string converted_str = converter.to_bytes(Chat->wsCurrentMessage);
				Chat->AddChatMessage(converted_str, { 0xFF, 0xFF, 0xFF, 0xFF });
				Chat->wsCurrentMessage.clear();
				Chat->Close();
				Chat->uiCarretPos = 0;
			}
			break;
		case VK_LEFT:
			if (!Chat->bOpened)
				break;
			if (Chat->uiCarretPos > 0)
				Chat->uiCarretPos--;
			break;
		case VK_RIGHT:
			if (!Chat->bOpened)
				break;
			if (Chat->uiCarretPos < Chat->wsCurrentMessage.length())
				Chat->uiCarretPos++;
			break;
		case VK_BACK:
			if (!Chat->bOpened)
				break;
			if (Chat->uiCarretPos > 0)
			{
				Chat->wsCurrentMessage.erase(Chat->wsCurrentMessage.begin() + (Chat->uiCarretPos - 1), Chat->wsCurrentMessage.begin() + Chat->uiCarretPos);
				Chat->uiCarretPos--;
			}
			break;
		case VK_DELETE:
			if (!Chat->bOpened)
				break;
			if (Chat->uiCarretPos < Chat->wsCurrentMessage.length())
			{
				Chat->wsCurrentMessage.erase(Chat->wsCurrentMessage.begin() + Chat->uiCarretPos, Chat->wsCurrentMessage.begin() + Chat->uiCarretPos + 1);
			}
			break;
		case VK_PRIOR:
			if (!Chat->bOpened)
				break;
			Chat->Scroll(SCROLL_UP);
			break;
		case VK_NEXT:
			if (!Chat->bOpened)
				break;
			Chat->Scroll(SCROLL_DOWN);
			break;
		}
	}
}