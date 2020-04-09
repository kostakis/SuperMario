#include "TileActions.h"

void TileActions::SetTag(int col, int row, const string& tag)
{
	tags[tag].insert(enumerator(col, row));
}

void TileActions::Trigger(int col, int row) {
	auto pos = enumerator(col, row);
	for (auto& i : tags)
		if (i.second.find(pos) != i.second.end()) {
			auto j = actions.find(i.first);
			if (j != actions.end())
				j->second(col, row);
			return;
		}
}

TileActions& TileActions::GetSingleton(void)
{
	static TileActions singleton;
	return singleton;
}

