# Waffle
- Static library for easier use of DirectX11 and ImGui
- Created with Visual Studio 2019 version 16.4.6, Boost library version 1.72.0, and ImGui

## Required project settings:
 - C++ 17 as language standard
 - Waffle as project reference (for correct build order)
 - Additional include directories
   1) ../libraries/boost_1_72_0
   2) ../libraries/imgui
   3) ../Waffle

   * The external libraries I used is not modified at all.\
     Just download, unzip if neccessary, and everything's good to go.\
     If you have those libraries in different folder, then change\
     additional include directories to fit yours.

   * I assume that you are creating a project in this solution (the same one where Waffle is in),\
     so there will be no problem in locating required lib file

## Example1
 - This example project shows how to use ImGui with this library
 - There are some steps you need to follow in order to use ImGui:
   1) Create waffle::ImGuiHelper instance (requires waffle::Context and waffle::RenderWindow)
   2) Call RenderWindow::Clear() and RenderWindow::Set() at the beginning of each frame
   3) Call ImGuiHelper::BeginFrame() with the instance you've created
   4) Use ImGui (ImGui::Begin, ImGui::Button, ...)
   5) Call ImGuiHelper::EndFrame()
   6) Call RenderWindow::Present()

## Example2
 - This example project shows the overview of this library\
   To be specific, it will be performing an offscreen rendering (two-pass)\
   First on a texture, then on the actual window
 - Things covered in this example:
   1) Creating window
   2) Creating input layout for shader
   3) Loading compiled vertex/pixel shaders
   4) Creating an indexed triangle mesh
   5) Creating transform matrices
   6) Creating constant buffers for shaders
   7) Creating an empty texture and texture sampler
   8) Synchronizing texture size with window by adding event handler for window resize event
   9) Setting pipeline (CV, RT, PS, VS, ...)
   10) Starting message loop
   11) Using keyboard input to update constant buffer
   12) Rendering to a texture
   13) Rendering texture to window (you can do post-processing with this)
   14) Exception handling (the outermost try-catch block and printing exception)

   * I used shader model 5.0 and specified whether it is a PS or VS\
     Visual studio will compile it for you
