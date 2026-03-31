#include "IGameInstance.h"

namespace Catalyst
{
	IGameInstance::IGameInstance()
		: m_window{ nullptr }, m_renderer{ nullptr } { }

	IGameInstance::~IGameInstance() = default;
}
