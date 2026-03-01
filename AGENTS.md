# Godot Repo Guide for GRE Agents

You are usually here as an agent working on **GRE**, not as a generic Godot contributor.
Treat this repository as the engine/runtime dependency that GRE is built into.

## Scope and intent

- Primary product logic for GRE lives in the sibling repo: `../gre/`.
- This `godot/` repo is where engine behavior, engine APIs, and module integration are defined.
- For most GRE tasks, use this repo to understand engine internals and integration boundaries, then make gameplay/UI changes in `../gre/`.
- Do not make changes to code in this repo. It is read-only.

## How this Godot fork fits GRE

- GRE is integrated as custom modules loaded from `../gre/src` (see current build environment using `custom_modules: ../gre/src`).
- The GRE-relevant custom modules are:
- `../gre/src/flecs` (vendored Flecs ECS module code)
- `../gre/src/gre` (GRE gameplay/runtime module)
- Godot-generated module wiring (`modules/register_module_types.gen.cpp`) calls:
- `initialize_flecs_module(...)`
- `initialize_gre_module(...)`

## GRE integration entry points (most important)

- `../gre/src/gre/register_types.cpp`
- Registers GRE classes with Godot.
- Creates `ScriptAPI` and exposes it as engine singleton `"CG"` via `Engine::add_singleton(...)`.
- Initializes GRE world/module state at `MODULE_INITIALIZATION_LEVEL_SCENE`.
- `../gre/src/gre/script/script.cpp` - The ScriptAPI
- Binds methods and enums with `ClassDB::bind_method(...)` and enum constants.
- `../gre/src/gre/SCsub`

## Godot architecture map (relevant when debugging GRE)

- `core/`
- Foundation layer: `Object`, `Variant`, strings, containers, OS/IO, math.
- If conversion/binding/lifetime issues happen, investigate here.
- `servers/`
- Backend services (rendering, physics, audio, text, navigation).
- If behavior is engine-backend level (not gameplay logic), investigate here.
- `scene/`
- Node/resource layer used by gameplay and UI (`Node`, `Node3D`, `Control`, resources, scene tree behavior).
- Most GRE runtime interactions with Godot are through this layer.
- `main/`
- Engine startup, module init flow, CLI handling.
- Useful when debugging initialization order or module lifecycle problems.
- `editor/`
- Editor-only tooling.
- Relevant for GRE editor plugins/tools (for example, map tooling), not normal gameplay runtime.
- `modules/`
- Built-in and generated module registration plumbing.
- `thirdparty/`
- Vendored external libraries. Avoid edits unless a task explicitly requires it.

## Bottom line

- Think of `godot/` as GRE's host engine internals.
- Think of `../gre/src/gre` as GRE's game/runtime module.
- All feature work belongs in GRE module code; use Godot internals to understand constraints and engine behavior.
