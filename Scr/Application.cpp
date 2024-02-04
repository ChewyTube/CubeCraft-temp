#include "Application.h"

void Application::run() {
	m_CubeCraft.Init();
	m_CubeCraft.Loop();
	m_CubeCraft.Quit();
}