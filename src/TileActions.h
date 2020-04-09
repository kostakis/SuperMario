#pragma once
#ifndef TILEACTIONS_H
#define TILEACTIONS_H

#include "basic_includes.h"
#include "TileLayer.h"

class TileActions {
public:
	using Action = function<void(int col, int row)>;
	using Enumerator = function<unsigned(int col, int row)>;
private:
	TileActions() {}
	~TileActions() {}

	using Actions = map<string, Action>;
	Actions actions;
							
	using Tags = map<string, set<unsigned>>;
	Tags tags;
	Enumerator enumerator;
public:
	template <typename Tfunc>
	void SetEnumerator(const Tfunc& f) {
		enumerator = f;
	}

	template <typename Tfunc>
	void Install(const string& tag, const Tfunc& f) {
		actions[tag] = f;
	}

	void SetTag(int col, int row, const string& tag);
	void Trigger(int col, int row);

	static TileActions& GetSingleton(void);
};
#endif // ! TILEACTIONS