/*****************************************************************************
 * main
 * Created by James Mills on 28/03/2026.
 *****************************************************************************/

#include "Application.h"
#include "EditorGameInstance.h"
#include "Implementations.h"

using Catalyst::Application;
using Catalyst::Editor::EditorGameInstance;

int main()
{
	return Application::Run<EditorGameInstance, WindowImpl, RendererImpl, InputManagerImpl>(
		 "Catalyst", 1920.f, 1080.f
		);
}
