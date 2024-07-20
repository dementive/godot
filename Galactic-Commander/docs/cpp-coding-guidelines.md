# C++ Coding Guidelines

The coding guildlines are the exact same as the godot engine guidlines...because the code is the same

https://docs.godotengine.org/en/stable/contributing/development/cpp_usage_guidelines.html

Basically this means no stl, no auto keyword, and no lambdas. Since GDExtension is basically an extension of the game engine it makes sense to follow the same style unless it's absoultely necessary.

Reading through this:

https://docs.godotengine.org/en/stable/contributing/development/

And then this:

https://docs.godotengine.org/en/stable/contributing/development/core_and_modules


Should cover everything you need to know when it comes to actually using GDExtension.

## Coding style

Code style should be the exact same as the godot engine code

https://docs.godotengine.org/en/stable/contributing/development/code_style_guidelines.html

Make sure to run clang-format after writing C++ code and setup the clangd LSP in your editor.