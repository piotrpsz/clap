# clap
C++ library for analyzing program call arguments.
<ul>
    <li>you can use single-letter (short) arguments in the call line, e.g. -i (ignore case) -r (recursive),</li>
    <li>you can use longer arguments, e.g.: --icase, --resursive,</li>
    <li>specifying the value of the argument: -d '/Users' or -d='/Users' or --dir '/Users' lub --dir='/Users',</li>
    <li>if you have several arguments without values (-i and -r) you can combine them: -ir</li>
</ul>

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

## Example of use:
First create a Clap object with the parameters you want:
```c++
auto clap = Clap("dirscanner v. 0.1",
                 Arg()
                    .marker("-i")
                    .promarker("--icase")
                    .ordef(false),
                 Arg()
                    .marker("-r")
                    .promarker("--recursive"),
                 Arg()
                    .marker("-d")
                    .promarker("--dir")
);
```
Then, after the program starts, call the <b>parse</b> function::
```c++
int main(int argn, char* argv[]) {
    clap.parse(argn, argv);
    ...
    ...
}
```
And finally to get the parsing result:
```c++
    if (auto directory = clap["--dir"]; directory)
        std::cout << *directory << '\n';

    if (auto icase = clap["-i"]; icase)
        std::cout << *icase << '\n';
```
When no value is given for the argument, it receives the logical value true (that it was in the call).
