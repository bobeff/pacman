#include "pch.h"
#include "game.h"

#if !defined(_DEBUG) && defined(WIN32)
  int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
#else
  int main()
#endif

{
  Game game;
  return game.Run();
}
