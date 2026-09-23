# PixEngine

A simple game engine, intended as an introduction to simple 2D games.

## Overview

This repository contains the source code and assets for [PixEngine].  
All work is created by the authors listed below and may not be used commercially by third parties without explicit permission.

## Repository layout

- `source/`, `include/` - the reusable engine core (built as the `PixEngineLib` CMake target).
- `assets/`, `config/` - resources owned by the engine itself (fonts, engine intro logo/sfx, default key bindings, etc.).
- `example/` - a sample game built on top of PixEngine, with the same `source/include/config/assets` layout. Only built when PixEngine is opened/built on its own.

## Using PixEngine in another project

PixEngine is designed to be dropped straight into another project as a subfolder and consumed via CMake, without needing any of its own example content.

1. Copy (or add as a git submodule) the whole `PixEngine` folder into your project, e.g. `MyGame/PixEngine/`.
2. Give your own project the normal `source/`, `include/`, `config/`, `assets/` folders at its root - this is where your game code and resources live.
3. In your project's root `CMakeLists.txt`:

   ```cmake
   add_subdirectory(PixEngine)

   add_executable(MyGame ${MY_SOURCES} ${MY_HEADERS})
   target_include_directories(MyGame PRIVATE include)
   target_link_libraries(MyGame PRIVATE PixEngineLib)

   # Tell the engine where *your* project's own assets/config live.
   target_compile_definitions(MyGame PRIVATE
       PIXENGINE_GAME_ASSETS_DIR="assets/"
       PIXENGINE_GAME_CONFIG_DIR="config/"
   )

   # Copies SFML/OpenAL DLLs and PixEngine's own assets/config (under
   # PixEngine/assets, PixEngine/config next to your binary) and sets the
   # debugger working directory.
   pixengine_setup_app(MyGame)
   ```

4. Add your own custom command(s) to copy `assets/` and `config/` next to your executable, the same way `pixengine_setup_app` does for the engine's own resources.
5. In your `main()`, create an `Engine`, register your own game states, and set the state to run after the built-in PixEngine intro:

   ```cpp
   #include "Engine.h"
   #include "MyGameState.h"

   int main()
   {
       Engine engine;
       engine.GetStateManager()->RegisterState<MyGameState>(MyStateType::MyGameState);
       engine.GetStateManager()->SetInitialState(MyStateType::MyGameState);

       while (!engine.GetWindow()->IsDone())
       {
           engine.Update();
           engine.Render();
           engine.LateUpdate();
       }
       return 0;
   }
   ```

   Define your own `StateType` ids starting at `EngineStateType::UserStateStart` (see `include/StateType.h`) so they never collide with engine-reserved ids - `example/include/GameStateType.h` shows this pattern.

See `example/` for a complete, working reference implementation of all of the above.

## Authors & Attribution

- Daniel Palacio

When sharing or adapting this project, the `NOTICE.txt` and `LICENSE` files **must be included** to ensure proper attribution and compliance with the license.

## License

This project is licensed under the **Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)** license.  
Full license text can be found in the [LICENSE](LICENSE) file.  

## Copyright & Disclaimer

© 2025 Daniel Palacio

All rights reserved. This project and its assets are for personal and educational use only. 
Commercial use is prohibited unless explicitly agreed in writing.

This project is provided "as-is." The authors are not responsible for any damage or misuse resulting from the use of this software or assets.
