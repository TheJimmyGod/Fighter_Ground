#include <XEngine.h>
#include "Leaderboard.h"
void Leaderboard::InitializeData(map<string, int> data)
{
	leaders.clear();

	std::map<string, int>::iterator it = data.begin();
	for (; it != data.end(); ++it)
	{
		LeaderboardItem item = { it->first, it->second };
		leaders.push_back(item);
	}
}

void Leaderboard::PrintLeaderboard()
{
	if (std::size(leaders) <= 0)
	{
		return;
	}

	X::GetScreenHeight();


	float xPos = 350.0f;
	float yPos = 0.0f;
	float textSize = 13.0f;
	// print the header
	X::DrawScreenText("ScoreBoard", xPos, yPos, textSize, X::Math::Vector4(0.0f, 0.0f, 0.0f, 0.0f)); // Vector4(R,G,B,A)

	yPos += 10.0f;
	const char* name = leaders[0].playerName.c_str();
	X::DrawScreenText(name, xPos, yPos, textSize, X::Math::Vector4::Blue());
}