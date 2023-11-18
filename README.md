# clap
C++ library for analyzing program call arguments.

## dependencies:
### fmt library
<ol>
    <li>from https://github.com/fmtlib/fmt</li>
    <li>install on macOS: brew install fmt</li>
</ol>

## How to add to your own project (using CMake):<br>
<ol>
    <li>Go to the root directory of your project (I assume you have git initialized).</li>
    <li>Enter the command: <b><i>git submodule add https://github.com/piotrpsz/clap.git</i></b></li>
    <li>In your project's <b>CMakeLists.txt</b> file, add the following:</li>
    <ul>
        <li>add_subdirectory(clap)</li>
        <li>target_link_libraries(your_project_name PUBLIC clap)</li>
    </ul>
</ol>