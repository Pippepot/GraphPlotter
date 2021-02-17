#pragma once
#include "olcPixelGameEngine.h"

std::string inputString;
int cursor;
float cursorBlinkTime = 0.5;
bool shiftFlag;
bool ctrlFlag;

void UpdateKeyState(int32_t input, bool state)
{
	olc::Key key = olc::Key(input);


	if (state)
		inputString = std::to_string(input);

	return;

	if (!state)
	{
		switch (key)
		{
		case olc::SHIFT:
			shiftFlag = false;
			break;
		case olc::CTRL:
			ctrlFlag = false;
			break;
		default:
			break;
		}
		return;
	}

	switch (key)
	{
	case olc::NONE:
		break;
	case olc::A:
		inputString.insert(cursor, "A");
		cursor++;
		break;
	case olc::B:
		inputString.insert(cursor, "B");
		cursor++;
		break;
	case olc::C:
		inputString.insert(cursor, "C");
		cursor++;
		break;
	case olc::D:
		inputString.insert(cursor, "D");
		cursor++;
		break;
	case olc::E:
		inputString.insert(cursor, "E");
		cursor++;
		break;
	case olc::F:
		inputString.insert(cursor, "F");
		cursor++;
		break;
	case olc::G:
		inputString.insert(cursor, "G");
		cursor++;
		break;
	case olc::H:
		inputString.insert(cursor, "H");
		cursor++;
		break;
	case olc::I:
		inputString.insert(cursor, "I");
		cursor++;
		break;
	case olc::J:
		inputString.insert(cursor, "J");
		cursor++;
		break;
	case olc::K:
		inputString.insert(cursor, "K");
		cursor++;
		break;
	case olc::L:
		inputString.insert(cursor, "L");
		cursor++;
		break;
	case olc::M:
		inputString.insert(cursor, "M");
		cursor++;
		break;
	case olc::N:
		inputString.insert(cursor, "N");
		cursor++;
		break;
	case olc::O:
		inputString.insert(cursor, "O");
		cursor++;
		break;
	case olc::P:
		inputString.insert(cursor, "P");
		cursor++;
		break;
	case olc::Q:
		inputString.insert(cursor, "Q");
		cursor++;
		break;
	case olc::R:
		inputString.insert(cursor, "R");
		cursor++;
		break;
	case olc::S:
		inputString.insert(cursor, "S");
		cursor++;
		break;
	case olc::T:
		inputString.insert(cursor, "T");
		cursor++;
		break;
	case olc::U:
		inputString.insert(cursor, "U");
		cursor++;
		break;
	case olc::V:
		inputString.insert(cursor, "V");
		cursor++;
		break;
	case olc::W:
		inputString.insert(cursor, "W");
		cursor++;
		break;
	case olc::X:
		inputString.insert(cursor, "X");
		cursor++;
		break;
	case olc::Y:
		inputString.insert(cursor, "Y");
		cursor++;
		break;
	case olc::Z:
		inputString.insert(cursor, "Z");
		cursor++;
		break;
	case olc::K0:
		inputString.insert(cursor, "0");
		cursor++;
		break;
	case olc::K1:
		inputString.insert(cursor, "1");
		cursor++;
		break;
	case olc::K2:
		inputString.insert(cursor, "2");
		cursor++;
		break;
	case olc::K3:
		inputString.insert(cursor, "3");
		cursor++;
		break;
	case olc::K4:
		inputString.insert(cursor, "4");
		cursor++;
		break;
	case olc::K5:
		inputString.insert(cursor, "5");
		cursor++;
		break;
	case olc::K6:
		inputString.insert(cursor, "6");
		cursor++;
		break;
	case olc::K7:
		inputString.insert(cursor, "7");
		cursor++;
		break;
	case olc::K8:
		inputString.insert(cursor, "8");
		cursor++;
		break;
	case olc::K9:
		inputString.insert(cursor, "9");
		cursor++;
		break;
	case olc::F1:
		break;
	case olc::F2:
		break;
	case olc::F3:
		break;
	case olc::F4:
		break;
	case olc::F5:
		break;
	case olc::F6:
		break;
	case olc::F7:
		break;
	case olc::F8:
		break;
	case olc::F9:
		break;
	case olc::F10:
		break;
	case olc::F11:
		break;
	case olc::F12:
		break;
	case olc::UP:
		break;
	case olc::DOWN:
		break;
	case olc::LEFT:
		cursor = max(0, cursor-1);
		break;
	case olc::RIGHT:
		cursor = min(inputString.length(), cursor+1);
		break;
	case olc::SPACE:
		inputString += ' ';
		break;
	case olc::TAB:
		break;
	case olc::SHIFT:
		shiftFlag = true;
		break;
	case olc::CTRL:
		ctrlFlag = true;
		break;
	case olc::INS:
		break;
	case olc::DEL:
		inputString.erase(cursor, 1);
		break;
	case olc::HOME:
		break;
	case olc::END:
		break;
	case olc::PGUP:
		break;
	case olc::PGDN:
		break;
	case olc::BACK:
		if (cursor == 0)
			break;

		inputString.erase(cursor - 1, 1);
		cursor--;
		break;
	case olc::ESCAPE:
		break;
	case olc::RETURN:
		break;
	case olc::ENTER:
		break;
	case olc::PAUSE:
		break;
	case olc::SCROLL:
		break;
	case olc::NP0:
		inputString.insert(cursor, "0");
		cursor++;
		break;
	case olc::NP1:
		inputString.insert(cursor, "1");
		cursor++;
		break;
	case olc::NP2:
		inputString.insert(cursor, "2");
		cursor++;
		break;
	case olc::NP3:
		inputString.insert(cursor, "3");
		cursor++;
		break;
	case olc::NP4:
		inputString.insert(cursor, "4");
		cursor++;
		break;
	case olc::NP5:
		inputString.insert(cursor, "5");
		cursor++;
		break;
	case olc::NP6:
		inputString.insert(cursor, "6");
		cursor++;
		break;
	case olc::NP7:
		inputString.insert(cursor, "7");
		cursor++;
		break;
	case olc::NP8:
		inputString.insert(cursor, "8");
		cursor++;
		break;
	case olc::NP9:
		inputString.insert(cursor, "9");
		cursor++;
		break;
	case olc::NP_MUL:
		inputString.insert(cursor, "*");
		cursor++;
		break;
	case olc::NP_DIV:
		inputString.insert(cursor, "/");
		cursor++;
		break;
	case olc::NP_ADD:
		inputString.insert(cursor, "+");
		cursor++;
		break;
	case olc::NP_SUB:
		inputString.insert(cursor, "-");
		cursor++;
		break;
	case olc::NP_DECIMAL:
		inputString.insert(cursor, ",");
		cursor++;
		break;
	case olc::PERIOD:
		inputString.insert(cursor, ".");
		cursor++;
		break;
	default:
		break;
	}

}