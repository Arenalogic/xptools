# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Product Identity

This is **ACT WED** — Arenalogic's downstream fork of X-Plane's xptools/WorldEditor, repurposed as a professional editor for ACT simulator airbases and military simulation data. It is part of Arenalogic's F-16 / fast-jet simulator ecosystem.

ACT WED is **not** an X-Plane scenery tool. No effort should be spent maintaining X-Plane compatibility unless it directly reduces future upstream merge friction.

## Repository & Branch Model

| Branch | Purpose |
|--------|---------|
| `master` | Mirrors `upstream/master` (X-Plane/xptools) as cleanly as possible |
| `act_wed` | Long-lived ACT product branch — all Arenalogic development happens here |

- **Upstream remote:** `X-Plane/xptools`
- **Fork:** `Arenalogic/xptools`
- Sync from upstream only when upstream has something we need.
- We do not expect to upstream most changes.

## Upstream Merge Policy

**When conflicts arise, reshape ACT code to accommodate upstream evolution** — not the other way around. This preserves long-term mergeability.

Rules for every change:
1. **Evaluate upstream merge impact** before modifying any file that originated upstream.
2. **Prefer extension over modification.** Add new files/classes rather than rewriting upstream code.
3. **Avoid large refactors** of upstream code — they compound merge complexity.
4. **Keep changes well-scoped and traceable.** Each commit should have a clear, narrow purpose.

## Code Modification Rules

### Touching upstream source files
When ACT functionality must modify an upstream `.h` or `.cpp` file (menus, startup paths, wiring), **use `#if ACT_WED` preprocessor guards**:

```cpp
#if ACT_WED
    // ACT-specific code
#else
    // Original upstream code (preserve for mergeability)
#endif
```

`ACT_WED` is defined in the CMake build system. All upstream source modifications must be guarded this way.

### Build system files (CMakeLists.txt, cmake/*.cmake)
CMake and build files **may diverge freely** from upstream. No guards needed. We accept that our build configuration will become significantly different.

### ACT-specific source code
New ACT features (entity types, export formats, project management, military airbase metadata) live in a **separate source tree: `src/ACT/`** (not mixed into `src/WED*`). This keeps ACT code merge-isolated from upstream.

Use existing upstream naming prefixes (`WED_`, `GUI_`, etc.) — do not introduce an `ACT_` class prefix. The source tree location (`src/ACT/`) provides sufficient separation.

## ACT Startup Mode (Future)

ACT WED will operate on **ACT project context files** (XML) that define resource folders, rather than requiring an X-Plane installation. Specifics TBD — design for this to be additive.

## Build System

**Platform:** Windows only. No effort required to maintain macOS or Linux support.

**Current state:** CMake + Conan 2 + Visual Studio, C++20.

**Direction:**
- Migrate from Conan to **vcpkg** (near-term priority, aligns with other Arenalogic projects).
- Modernize CMake to support **CMake 4.x** and **Visual Studio 2022+**. Apply minimal changes to achieve this — if dependency issues arise, the vcpkg migration resolves them.
- Build files can diverge from upstream freely.

### Current Build Commands (Windows)
```powershell
# Generate VS solution in vs_build/
./cmake.ps1                          # Default: Release
./cmake.ps1 -BuildType Debug
./cmake.ps1 -Clean                   # Clean rebuild

# Build from command line
cmake --build vs_build --config Debug
cmake --build vs_build --config Release
```

**Output:** `vs_build/`

**Build targets:** `WED`, `DDSTool`, `DSFTool`, `ObjView`, `XGrinder`, `OneOffs`.

**Build-type defines:** `DEV=1` (Debug, debug features/assertions), `DEV=0` (Release). `IBM=1` (Windows). `BIG=0`, `LIL=1`.

## Upstream Architecture Reference

Understanding the upstream architecture is necessary for knowing where to hook ACT features and where not to touch.

### Platform Conditionals
```cpp
#if IBM    // Windows
#elif APL  // macOS
#elif LIN  // Linux
```

### Layered Architecture
1. **Platform layer** (`src/UI/`) — OS-specific window management (`XWin.win.cpp`, etc.) + `src/Utils/PlatformUtils.*`
2. **GUI framework** (`src/GUI/`) — OpenGL-based widget library (50+ classes)
3. **Application layer** (`src/WED*/`) — WED modules built on the GUI framework

### Core Data Model (`src/WEDCore/`)
- `WED_Application` — Main app class (extends `GUI_Application`)
- `WED_Document` — SQLite3-backed document persistence
- `WED_Entity` — Base entity class for all scenery objects
- `WED_UndoMgr` — Undo/redo system
- `WED_ResourceMgr`, `WED_LibraryMgr`, `WED_TexMgr` — Asset management
- `WED_Validate` — Data validation before export

### Interfaces (`src/Interfaces/`)
`IGIS` (spatial entities), `IPropertyObject` (property system), `ISelection`, `IDirectory` (hierarchy), `IBase`.

### Entity Hierarchy (`src/WEDEntities/`)
67 entity types inheriting from `WED_Entity` with GIS base classes (`WED_GISPoint`, `WED_GISLine`, `WED_GISPolygon`, `WED_GISChain`).

### Map System (`src/WEDMap/`)
- Layers: `WED_StructureLayer`, `WED_ATCLayer`, `WED_TerrainLayer`, etc. (inherit `WED_MapLayer`)
- Tools: `WED_VertexTool`, `WED_CreatePointTool`, `WED_CreateLineTool`, etc. (inherit `WED_CreateToolBase`/`WED_MapToolNew`)

### Other Modules
- `src/DSF/` — Digital Scenery Format file library
- `src/Obj/` — OBJ file format library
- `src/XESCore/` — GIS engine
- `src/Utils/` — Geometry, file I/O, image processing, compression
- `src/WEDImportExport/` — Import/export formats
- `src/lzma19/` — Embedded LZMA compression

### CMake Build Files
Per-tool definitions: `cmake/WED.cmake` (~21KB, largest), `DDSTool.cmake`, `DSFTool.cmake`, `ObjView.cmake`, `XGrinder.cmake`, `OneOffs.cmake`.

## Dependencies

Currently Conan-managed (migrating to vcpkg): GLEW, FreeType, PROJ, libgeotiff, libtiff, libjpeg, libpng, zlib, bzip2, expat, libsquish, shapelib, libcurl, jsoncpp.

Git submodules: `libs/` (xptools_libs), `msvc_libs/` (MSVC prebuilt libraries).

## Task Execution Checklist

Before implementing any change, evaluate:
- [ ] Does this touch upstream files? If yes, use `#if ACT_WED` guards.
- [ ] Could this be placed in `src/ACT/` instead of modifying upstream code?
- [ ] Will this create merge friction with future upstream syncs?
- [ ] Is this the minimum change needed, or am I over-engineering?
- [ ] Are architectural trade-offs explicitly called out?
