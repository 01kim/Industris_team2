#include "Input.h"


void Input::Update()
{
	//入力が更新される変数
	GamePadButton newButtonState = 0;
	//入力で変更
	//XBOXコントローラー
	{
		if (xInput[0].bUPt) newButtonState |= button.BTN_UP;//上
		if (xInput[0].bLEFTt) newButtonState |= button.BTN_LEFT;//左
		if (xInput[0].bDOWNt) newButtonState |= button.BTN_DOWN;//下
		if (xInput[0].bRIGHTt) newButtonState |= button.BTN_RIGHT;//右
		if (xInput[0].bAt) newButtonState |= button.BTN_A; //Aボタン
		if (xInput[0].bBt) newButtonState |= button.BTN_B; //Bボタン
		if (xInput[0].bXt) newButtonState |= button.BTN_X; //Xボタン
		if (xInput[0].bYt) newButtonState |= button.BTN_Y; //Yボタン
		if (xInput[0].bSTARTt) newButtonState |= button.BTN_START;//STARTボタン
		if (xInput[0].bBACKt) newButtonState |= button.BTN_BACK;//BACKボタン
		if (xInput[0].bLBt) newButtonState |= button.BTN_LEFT_THUMB;//L1ボタン
		if (xInput[0].bRBt) newButtonState |= button.BTN_RIGHT_THUMB;//R1ボタン
		if (xInput[0].bLTt) newButtonState |= button.BTN_LEFT_SHOULDER;//L2ボタン
		if (xInput[0].bRTt) newButtonState |= button.BTN_RIGHT_SHOULDER;//R2ボタン
		if (xInput[0].bL3t) newButtonState |= button.BTN_LEFT_TRIGGER;//L3ボタン
		if (xInput[0].bR3t) newButtonState |= button.BTN_RIGHT_TRIGGER;//R3ボタン

		axisLx = static_cast<float>(xInput[0].sLX) / static_cast<float>(0x8000);
		axisLy = static_cast<float>(xInput[0].sLY) / static_cast<float>(0x8000);
		axisRx = static_cast<float>(xInput[0].sRX) / static_cast<float>(0x8000);
		axisRy = static_cast<float>(xInput[0].sRY) / static_cast<float>(0x8000);
	}
	//キーボード
	{
		float lx = 0.0f;
		float ly = 0.0f;
		float rx = 0.0f;
		float ry = 0.0f;
		//キーを追加してもOK
		if (GetAsyncKeyState('W') & 0x8000) newButtonState |= button.BTN_UP;
		if (GetAsyncKeyState('A') & 0x8000) newButtonState |= button.BTN_LEFT;
		if (GetAsyncKeyState('S') & 0x8000) newButtonState |= button.BTN_DOWN;
		if (GetAsyncKeyState('D') & 0x8000) newButtonState |= button.BTN_RIGHT;
		if (GetAsyncKeyState('Z') & 0x8000) newButtonState |= button.BTN_A;
		if (GetAsyncKeyState('X') & 0x8000) newButtonState |= button.BTN_B;
		if (GetAsyncKeyState('C') & 0x8000) newButtonState |= button.BTN_X;
		if (GetAsyncKeyState('V') & 0x8000) newButtonState |= button.BTN_Y;
		//https://docs.microsoft.com/ja-jp/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN&f1url=%3FappId%3DDev16IDEF1%26l%3DJA-JP%26k%3Dk(WINUSER%252FVK_ESCAPE);k(VK_ESCAPE);k(DevLang-C%252B%252B);k(TargetOS-Windows)%26rd%3Dtrue
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) newButtonState |= button.BTN_START;
		if (GetAsyncKeyState(VK_BACK) & 0x8000) newButtonState |= button.BTN_BACK;
		
		
		if (newButtonState & button.BTN_UP)    ly = -1.0f;
		if (newButtonState & button.BTN_LEFT) lx = -1.0f;
		if (newButtonState & button.BTN_DOWN)  ly = 1.0f;
		if (newButtonState & button.BTN_RIGHT)  lx = 1.0f;

		//Lスティック
		if (lx >= 1.0f || lx <= -1.0f || ly >= 1.0f || ly <= -1.0)
		{
			float power = ::sqrtf(lx * lx + ly * ly);
			axisLx = lx / power;
			axisLy = ly / power;
		}
		//Rスティック
		if (rx >= 1.0f || rx <= -1.0f || ry >= 1.0f || ry <= -1.0)
		{
			float power = ::sqrtf(rx * rx + ry * ry);
			axisRx = rx / power;
			axisRy = ry / power;
		}

	}
	//ボタンの状態
	{
		buttonState[1] = buttonState[0];	// スイッチ履歴
		buttonState[0] = newButtonState;

		buttonDown = ~buttonState[1] & newButtonState;	// 押した瞬間
		buttonUp = ~newButtonState & buttonState[1];	// 離した瞬間
	}
}