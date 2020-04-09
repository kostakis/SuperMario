#pragma once

#ifndef  ANIMATOR_H
#define ANIMATOR_H

#include "basic_includes.h"
#include "Animation.h"

typedef uint64_t timestamp_t;

enum animatorstate_t {
	ANIMATOR_FINISHED = 0, 
	ANIMATOR_RUNNING = 1,
	ANIMATOR_STOPPED = 2
};

class Animator {
	public:
		using OnFinish = function<void(Animator *)>;
		using OnStart = function<void(Animator *)>;
		using OnAction = function<void(Animator*,const Animation&)>;
	protected:
		timestamp_t lastTime = 0;
		animatorstate_t state = ANIMATOR_FINISHED;
		OnFinish onFinish;
		OnStart onStart;
		OnAction onAction;
		void NotifyStopped(void);
		void NotifyStarted(void);
		void NotifyAction(const Animation&);
		void Finish(bool isForced = false);
	public:
		void Stop(void);
		bool HasFinished(void) const;
		virtual void TimeShift(timestamp_t offset);
		virtual void Progress(timestamp_t currTime) = 0;
		template <typename Tfunc> void SetOnFinish(const Tfunc& f) {
			onFinish = f;
		}

		template <typename Tfunc> void SetOnStart(const Tfunc& f) {
			onStart = f;
		}
		template <typename Tfunc> void SetOnAction(const Tfunc& f) {
			onAction = f;
		}
		Animator(void);
		Animator(const Animator&) = delete;
		Animator(Animator&&) = delete;
		virtual ~Animator();
};
#endif // ! ANIMATOR_H