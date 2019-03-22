#ifndef LEADERBOARD_HEADER_H
#define LEADERBOARD_HEADER_H
#include <vector>
#include <map>
#include <string>
using std::vector;
using std::map;
using std::string;

class Leaderboard
{
public:
	Leaderboard() {}
	~Leaderboard() {}

	struct LeaderboardItem
	{
		string playerName;
		int score;
	};

	void InitializeData(map<string, int> data);
	void PrintLeaderboard();

private:
	vector<LeaderboardItem> leaders;
};
#endif // !LEADERBOARD_HEADER_H