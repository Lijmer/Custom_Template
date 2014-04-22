#include "Input.h"
#include "InputImpl.h"
#include <SDL.h>

#include <bitset>


namespace input
{
  static std::bitset<SDLK_LAST> key, keyDown, keyUp;
  static uint8 mouseButton, mouseButtonDown, mouseButtonUp;
  static int mouseX = 0;
  static int mouseY = 0;

  bool GetKey(SDLKey k) { return key[k]; }
  bool GetKeyDown(SDLKey k) { return keyDown[k]; }
  bool GetKeyUp(SDLKey k) { return keyUp[k]; }

  bool GetMouseButton(int b)
  {
    return (mouseButton & (0x1 << b)) >> b != 0;
  }
  bool GetMouseButtonDown(int b)
  {
    return (mouseButtonDown & (0x1 << b)) >> b != 0;
  }
  bool GetMouseButtonUp(int b)
  {
    return (mouseButtonUp & (0x1 << b)) >> b != 0;
  }
  namespace impl
  {
    void OnKeyDown(SDLKey k)
    {
      key[k] = true;
      keyDown[k] = true;
    }
    void OnKeyUp(SDLKey k)
    {
      key[k] = false;
      keyUp[k] = true;
    }
    void OnMouseMotion(int x, int y)
    {
      mouseX = x;
      mouseY = y;
    }
    void OnMouseButtonDown(uint8 b)
    {
      mouseButton |= b;
      mouseButtonDown |= b;
    }
    void OnMouseButtonUp(uint8 b)
    {
      mouseButton &= ~b;
      mouseButtonUp |= b;
    }

    void OnUpdate()
    {
      keyDown.reset();
      keyUp.reset();
      mouseButtonDown = mouseButtonUp = 0x0000;
    }
  }

}
