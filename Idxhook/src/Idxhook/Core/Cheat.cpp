#include "ihpch.h"

#include "Cheat.h"

namespace Idxhook {

	Cheat* Cheat::s_Instance = nullptr;

	Cheat::Cheat()
	{
		s_Instance = this;
	}

	Cheat::~Cheat()
	{
	}

	void Cheat::Run()
	{

	}

	void Cheat::Close()
	{

	}

}
