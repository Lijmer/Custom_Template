// Template by Max Oomen - 2014
// Based on the template by Jacco Bikker - 2006-2014
#include "Bitmap.h"
#include "Game.h"
#include "Constants.h"
#include "Window.h"
#include "EventHandler.h"
#include "TimeImpl.h"
#include "InputImpl.h"
#include "Renderer.h"
#include "CollisionHandler.h"

using namespace engine;

static game::Game* g_game = nullptr;
static bool g_running = true;

int main(int, char**)
{
  Window window(SCRWIDTH, SCRHEIGHT, "Custom_Template");
  Bitmap::InitCharset();
  time::impl::Init();

  event_handler::SetWindowCloseCallback([](){ g_running = false; });
  event_handler::SetKeyDownCallback(&input::impl::OnKeyDown);
  event_handler::SetKeyUpCallback(&input::impl::OnKeyUp);
  event_handler::SetMouseMotionCallback(&input::impl::OnMouseMotion);
  event_handler::SetMouseButtonDownCallback(&input::impl::OnMouseButtonDown);
  event_handler::SetMouseButtonUpCallback(&input::impl::OnMouseButtonUp);

  game::Game game([]{g_running = false; });
  g_game = &game;

  while(g_running)
  {
    window.Draw(&renderer::Render);
    input::impl::OnUpdate();
    event_handler::Update();
    time::impl::Update();
    game.Update();
    collision_handler::Update();
    
  }

  g_game = nullptr;
  return 0;
}
