#include "CollisionChecker.h"

void CollisionChecker::Cancel(Sprite* s1, Sprite* s2)
{
	auto i = std::find_if(
		entries.begin(),
		entries.end(),
		[s1, s2](const Entry& e) {
			return std::get<0>(e) == s1 && std::get<1>(e) == s2;
		}
	);
	entries.erase(i);
}

void CollisionChecker::Cancel(Sprite* s2)
{
	auto i = entries.begin();
	while ((i = std::find_if(
		entries.begin(),
		entries.end(),
		[s2](const Entry& e) -> bool {
			return std::get<0>(e) == s2 || std::get<1>(e) == s2;
		})) != entries.end()
			)
		entries.erase(i);
}

void CollisionChecker::Check(void) const
{
	for (auto& e : entries)
		if (std::get<0>(e)->CollisionCheck(std::get<1>(e))) {
			std::get<2>(e)(std::get<0>(e), std::get<1>(e));
		}
}

CollisionChecker& CollisionChecker::GetInstance()
{
	static CollisionChecker singleton;
	return singleton;
}