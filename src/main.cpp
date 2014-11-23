#include "pch.h"
#include "application.h"

#if !defined(_DEBUG) && defined(WIN32)
  int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,
    LPSTR lpszArgument, int nCmdShow)
#else
  int main()
#endif

{
  Application app;
  return app.Run();
}
