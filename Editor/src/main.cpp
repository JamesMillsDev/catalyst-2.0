/*****************************************************************************
 * main
 * Created by James Mills on 28/03/2026.
 *****************************************************************************/

#include "Application.h"
#include "EditorGameInstance.h"
#include "Implementations.h"

using Catalyst::Editor::EditorGameInstance;

int main()
{
	return Catalyst::Application::Run<EditorGameInstance, WindowImpl, RendererImpl>("Catalyst", 1920.f, 1080.f);
}
