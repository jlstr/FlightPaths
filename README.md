
# FlighPaths

## 📦 Installation of Required Dependencies

> Note: This project was developed and tested on macOS. Installation steps might differ for other platforms such as Windows or Linux. CMake will typically find the macOS compiler (usually Clang, the default compiler on macOS) during its configuration process. All commands below are intended to be executed from the Terminal.

### 1. Install Homebrew

Homebrew is a package manager for macOS, which simplifies the installation of development tools and libraries.

To install Homebrew, run:

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
More information: https://brew.sh

### 2. Install CMake

CMake is a cross-platform build system that generates build files for C++ projects.

```
brew install cmake
```
More information: https://cmake.org

### 3. Install Google Test

Google Test is the testing framework used in this project. Installing it via Homebrew downloads the required headers and libraries locally.

```
brew install googletest
```
More information: https://google.github.io/googletest

## 🏗️ Building the Project

Once all dependencies are installed, navigate to the project's root directory (`cd FlightPaths`) and run the following:

### Step 1: Generate Build Files with CMake

```
cmake -S . -B build
```

This command tells CMake to:

- Use the current directory (.) as the source directory
- Generate build files in a subdirectory named build

You'll see some output that looks like this:

```
-- The C compiler identification is AppleClang 14.0.3.14030022
-- The CXX compiler identification is AppleClang 14.0.3.14030022
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (9.4s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/jose/Desktop/FlightPaths/build
```

### Step 2: Build the Project

```
cmake --build build
```

This compiles all the source files and links them into executables using the previously generated build configuration.

Sample output:

```
[  3%] Building CXX object CMakeFiles/FlightPaths.dir/src/flight_paths.cpp.o
[  7%] Building CXX object CMakeFiles/FlightPaths.dir/src/graph_builder.cpp.o
[ 10%] Building CXX object CMakeFiles/FlightPaths.dir/src/path_finder.cpp.o
[ 14%] Building CXX object CMakeFiles/FlightPaths.dir/src/data_loader.cpp.o
[ 17%] Building CXX object CMakeFiles/FlightPaths.dir/src/string_helper.cpp.o
[ 21%] Linking CXX executable FlightPaths
[ 21%] Built target FlightPaths
...
[ 89%] Linking CXX executable path_finder_test
[ 89%] Built target path_finder_test
[ 92%] Building CXX object CMakeFiles/string_helper_test.dir/src/tests/string_helper_test.cpp.o
[ 96%] Building CXX object CMakeFiles/string_helper_test.dir/src/string_helper.cpp.o
[100%] Linking CXX executable string_helper_test
[100%] Built target string_helper_test

```

## ✅ Running Tests

From the project root directory, run:

```
cd build && ctest && cd ..
```

This will:
- Navigate into the build directory
- Execute all unit tests via ctest
- Return to the root directory afterward

Sample Output:

```
Test project /Users/jose/Desktop/FlightPaths/build
      Start  1: GraphBuilderTest.AssemblesCorrectGraphWithFourCities
 1/36 Test  #1: GraphBuilderTest.AssemblesCorrectGraphWithFourCities .......   Passed    0.01 sec
      Start  2: GraphBuilderTest.EmptyInputProducesEmptyGraph
 2/36 Test  #2: GraphBuilderTest.EmptyInputProducesEmptyGraph ..............   Passed    0.00 sec
      Start  3: GraphBuilderTest.SingleCityProducesEmptyGraph
 3/36 Test  #3: GraphBuilderTest.SingleCityProducesEmptyGraph ..............   Passed    0.01 sec
      Start  4: GraphBuilderTest.NoEdgesWhenMatrixIsZeroExceptDiagonal
 4/36 Test  #4: GraphBuilderTest.NoEdgesWhenMatrixIsZeroExceptDiagonal .....   Passed    0.01 sec
      Start  5: GraphBuilderTest.ThrowsWhenMatrixRowsDoNotMatchCityCount
 5/36 Test  #5: GraphBuilderTest.ThrowsWhenMatrixRowsDoNotMatchCityCount ...   Passed    0.01 sec
...
31/36 Test #31: StringHelperTest.LeavesInternalSpacesUntouched .............   Passed    0.00 sec
      Start 32: StringHelperTest.HandlesStringWithOnlySpaces
32/36 Test #32: StringHelperTest.HandlesStringWithOnlySpaces ...............   Passed    0.01 sec
      Start 33: StringHelperTest.HandlesEmptyStringTrimming
33/36 Test #33: StringHelperTest.HandlesEmptyStringTrimming ................   Passed    0.01 sec
      Start 34: StringHelperTest.HandlesTabsAndNewlines
34/36 Test #34: StringHelperTest.HandlesTabsAndNewlines ....................   Passed    0.01 sec
      Start 35: StringHelperTest.TrimsSingleCharacterStringWithSpace
35/36 Test #35: StringHelperTest.TrimsSingleCharacterStringWithSpace .......   Passed    0.00 sec
      Start 36: StringHelperTest.TrimsSingleNonSpaceCharacter
36/36 Test #36: StringHelperTest.TrimsSingleNonSpaceCharacter ..............   Passed    0.00 sec

100% tests passed, 0 tests failed out of 36

Total Test time (real) =   0.22 sec
```

## 🚀 Executing the Project

After successful build and testing, you can run the main executable from the root directory:

```
./build/FlightPaths "castle Black" "Riverrun"
```

Sample Output:

```
Castle Black -> Winterfell -> Riverrun: 55
Castle Black -> Riverrun: 80
```

## ⚠️ Assumptions

- Input is loaded from CSV files, not from the CLI.

  The program assumes that city and cost data are provided via two CSV files located in the test_data/ directory: `test_data/cities.csv`, `test_data/costs.csv`.
  This is a conscious design decision to improve usability and reduce user error. Entering a full cost matrix via the command line would be tedious, error-prone, and impractical for repeated testing. By using editable files, users can efficiently configure new datasets using a text editor or spreadsheet software.
  ➡️ To test different input, simply modify and save these two files before re-running the program.

- The input cost matrix represents a Directed Acyclic Graph (DAG).

  The matrix must follow an upper triangular format, indicating that flights are one-way and that only forward (i.e., later-indexed) destinations are reachable from a given city. This structure inherently prevents cycles and enables traversal using DFS.

- The DAG is conceptually modeled as an N-ary Tree.

  Given its acyclic, top-down layout, the DAG behaves like an N-ary tree rooted at the starting city. This model simplifies traversal and visualization, as each unique path from the root corresponds to a valid itinerary.

- Matrix size is limited to 8x8.

  As per functional requirements, the program explicitly rejects any matrix larger than 8x8. While the underlying logic supports arbitrary graph sizes, this upper bound ensures predictable performance and aligns with the problem's requirements.

- City names are unique and case-insensitive.

  Each city name in `cities.csv` must be unique (after case normalization). Duplicate names could introduce graph inconsistencies or hidden cycles and are explicitly rejected. All city name comparisons are case-insensitive, allowing for flexible input.

- Whitespace is sanitized.

  Leading and trailing whitespace in city names is automatically stripped during parsing. Internal whitespace (e.g., "Los Angeles") is preserved.

- Disconnected paths are valid.

  Zero entries off the main diagonal in the cost matrix represent the absence of a flight. The system fully supports disconnected graphs and will report “No paths were found” when a route between two cities does not exist.

## 📝 Notes
- Paths are computed using DFS traversal.

  The program uses a recursive Depth-First Search to discover all simple (non-cyclic) paths between two cities. The search visits each node only once per path, preserving correctness in the acyclic graph.

- Error reporting is explicit and robust.

  Invalid input (e.g., malformed files, mismatched dimensions, non-numeric costs, or missing city names) is caught early. Errors are accompanied by descriptive messages to help users correct their data.

- C++ Exit codes 

  The program uses standard C++ Exit codes (https://en.wikipedia.org/wiki/Exit_status#C_language) -> EXIT_SUCCESS and EXIT_FAILURE from the program's `main` function to satisfy this specific requirement

- City mapping retains original formatting.

  While internal comparisons are made with lowercase names, the original formatting (including case and spacing) is retained for display in output paths.

- Self-links are ignored.

  Diagonal entries in the cost matrix (e.g., flights from a city to itself) are excluded from graph construction and traversal.

- The graph is built defensively.

  Even though the matrix format guarantees a DAG, the program still verifies that city names are unique and maintains per-path visit histories to safeguard against accidental cycles or malformed data.