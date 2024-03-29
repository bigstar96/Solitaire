#include <string>
#include "Card.h"

namespace solitaire
{
	Card::Card(HWND hwnd, int index, Type type, int x, int y) :
		mHwnd(hwnd),
		mIndex(index),
		mX(x), mY(y),
		mIsFront(false),
		mType(type)
	{
		std::wstring filename(L"Data/card_creature_");

		switch (type)
		{
		case Type::Wolf:
			filename += L"wolf.png";
			break;

		case Type::Dragon:
			filename += L"dragon.png";
			break;

		case Type::Bear:
			filename += L"bear.png";
			break;
		}

		mFront = std::make_unique<Gdiplus::Image>(filename.c_str());
		mBack = std::make_unique<Gdiplus::Image>(L"Data/card_back.png");
	}

	bool Card::CheckClicked(int mouseX, int mouseY)
	{
		if (mouseX >= mX && mouseX <= mX + mBack->GetWidth() &&
			mouseY >= mY && mouseY <= mY + mBack->GetHeight())
		{
			Flip(!mIsFront);
			return true;
		}

		return false;
	}

	void Card::Flip(bool isFront)
	{
		mIsFront = isFront;

		Invalidate();
	}

	void Card::Draw(Gdiplus::Graphics& graphics)
	{
		if (mIsFront)
		{
			graphics.DrawImage(mFront.get(), mX, mY, mFront->GetWidth(), mFront->GetHeight());
		}
		else
		{
			graphics.DrawImage(mBack.get(), mX, mY, mBack->GetWidth(), mBack->GetHeight());
		}
	}
	void Card::Invalidate()
	{
		RECT rct{
			mX, mY,
			static_cast<LONG>(mX + mBack->GetWidth()),
			static_cast<LONG>(mY + mBack->GetHeight())
		};

		InvalidateRect(mHwnd, &rct, false);
	}
}

