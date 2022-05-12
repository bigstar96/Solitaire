#include <string>
#include "Game.h"

namespace solitaire
{
	void Game::Init(HWND hwnd)
	{
		mHwnd = hwnd;
		mBackground = std::make_unique<Gdiplus::Image>(L"Data/bg_blank.png");

		CreateCards();
	}

	void Game::Release()
	{
		mDeck.clear();
		mBackground.reset();
	}

	void Game::Draw(Gdiplus::Graphics& graphics)
	{
		graphics.DrawImage(mBackground.get(), 0, 0,
			mBackground->GetWidth(), mBackground->GetHeight());

		for (auto& card : mDeck)
		{
			card.Draw(graphics);
		}

		Gdiplus::PointF pos(895.0f, 20.0f);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 79, 64));
		Gdiplus::Font font(L"¸¼Àº °íµñ", 20);

		graphics.DrawString(L"Å¬¸¯¼ö", -1, &font, pos, &brush);
		
		Gdiplus::StringFormat format;
		format.SetAlignment(Gdiplus::StringAlignmentCenter);
		format.SetLineAlignment(Gdiplus::StringAlignmentCenter);

		graphics.DrawString(
			std::to_wstring(mFlipCount).c_str(),
			-1, &font, mCountRect, &format, &brush
		);
	}

	void Game::OnClick(int mouseX, int mouseY)
	{
		for (auto& card : mDeck)
		{
			if (card.CheckClicked(mouseX, mouseY))
			{
				// TODO : Å¬¸¯ Ã³¸®

			}
		}
	}

	void Game::CreateCards()
	{
		// TODO : Ä«µå ¼¯±â

		mDeck.push_back(Card(mHwnd, Type::Bear, 0,0));
		mDeck.push_back(Card(mHwnd, Type::Wolf, 120,0));
		mDeck.push_back(Card(mHwnd, Type::Dragon, 240,0));
	}

}