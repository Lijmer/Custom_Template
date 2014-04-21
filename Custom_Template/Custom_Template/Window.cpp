#include "Window.h"
#include "WindowImpl.h"
#include "Bitmap.h"
#include <SDL_syswm.h>
#include <cstdio>

PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLMAPBUFFERPROC glMapBuffer = nullptr;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALFARPROC)(int);
PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = nullptr;

static bool windowInited = false;

using namespace engine;

bool InitBufferFuncs()
{
  glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
  glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
  glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
  glMapBuffer = (PFNGLMAPBUFFERPROC)wglGetProcAddress("glMapBuffer");
  glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBuffer");
  glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
  wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");
  if((!glGenBuffers) || (!glBindBuffer) || (!glBufferData) ||
     (!glMapBuffer) || (!glUnmapBuffer) || (!glDeleteBuffers))
    return false;
  if(!wglSwapIntervalEXT)
    return false;
  if(glGetError()) return false;
  return true;
}

bool CreateFBTexture(WindowImpl* p)
{
  glGenTextures(2, p->m_framebufferTexID);
  if(glGetError()) return false;
  for(int i = 0; i < 2; i++)
  {
    glBindTexture(GL_TEXTURE_2D, p->m_framebufferTexID[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p->m_width, p->m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    if(GLenum error = glGetError())
    {
      printf("%X\n", error);
      return false;
    }
  }
  const int sizeMemory = sizeof(Pixel) * p->m_width * p->m_height;
  glGenBuffers(2, p->m_fbPBO);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, p->m_fbPBO[0]);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeMemory, NULL, GL_STREAM_DRAW);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, p->m_fbPBO[1]);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeMemory, NULL, GL_STREAM_DRAW);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

  glBindTexture(GL_TEXTURE_2D, p->m_framebufferTexID[0]);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, p->m_fbPBO[0]);
  void* frameData = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);

  if(!frameData) return false;

  memset(frameData, 0x0, sizeMemory);
  glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
  return (glGetError() == 0);
}

Window::Window(int width, int height, const char* caption)
:p(new WindowImpl)
{
  if(windowInited)
  {
    printf("WARNING: There already is a window instantiated!\n"
           "This window object will be an empty shell.\n");
    delete p;
    p = nullptr;
    return;
  }
  windowInited = true;
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_EnableKeyRepeat(0, 0);
  p->m_width = width;
  p->m_height = height;
  p->m_SDLWindow = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
  
  if(!InitBufferFuncs())
  {
    printf("Failed to get all buffer function adresses.\n");
    return;
  }

  p->m_fbPBO[0] = p->m_fbPBO[1] = 0xffffffff;
  glEnable(GL_TEXTURE_2D);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glShadeModel(GL_SMOOTH);
  if(!CreateFBTexture(p))
  {
    printf("Failed to create FBTexture\n");
    return;
  }

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  wglSwapIntervalEXT(0);
  glDisable(GL_TEXTURE_2D);
  p->m_frameBuffer = new Bitmap(width, height, width, nullptr);

  SDL_SysWMinfo vmi;
  SDL_VERSION(&vmi.version);
  SDL_GetWMInfo(&vmi);
  p->m_windowHandle = vmi.window;
  SetCaption(caption);
}

Window::~Window()
{
  if(p != nullptr)
  {
    delete p->m_frameBuffer;
    glDeleteTextures(2, p->m_framebufferTexID);
    glDeleteBuffers(2, p->m_fbPBO);
    SDL_FreeSurface(p->m_SDLWindow);
    delete p;
  }
  SDL_Quit();
  windowInited = false;
}

void Window::Draw(void(*RenderFunc)(Bitmap*))
{
  static int index = 0;
  glEnable(GL_TEXTURE_2D);

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(1.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(0.0f, 0.0f);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_GL_SwapBuffers();
  ++index;
  index &= 1; //if 2, make it 0

  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, p->m_fbPBO[index]);
  p->m_frameBuffer->SetBuffer((Pixel*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY));
  RenderFunc(p->m_frameBuffer);
  glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
  
  glBindTexture(GL_TEXTURE_2D, p->m_framebufferTexID[index]);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, p->m_fbPBO[index]);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, p->m_width, p->m_height, GL_BGRA, GL_UNSIGNED_BYTE, 0);
}

void Window::SetCaption(const char* caption)
{
  SDL_WM_SetCaption(caption, nullptr);
}

void Window::ShowMessageBox(const char* message, const char* title)
{
  MessageBox(p->m_windowHandle, message, title, MB_OK);
}
