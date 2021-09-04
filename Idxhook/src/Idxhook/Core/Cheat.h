#pragma once

#include "Idxhook/Core/Base.h"

namespace Idxhook {

	class Cheat
	{
	public:
		Cheat();
		virtual ~Cheat();

		void Run();
		void Close();

		static inline Cheat& Get() { return *s_Instance; }
	private:
		static Cheat* s_Instance;
	};


}
