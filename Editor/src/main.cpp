/*****************************************************************************
 * main
 * Created by James Mills on 28/03/2026.
 *****************************************************************************/

#include "Application.h"
#include "Implementations.h"

int main()
{
	return Catalyst::Application::Run<WindowImpl, RendererImpl>("Catalyst", 1920.f, 1080.f);
}
