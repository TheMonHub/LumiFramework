# Contributing to LumiFramework

We're incredibly excited that you're interested in contributing to LumiFramework\! Your contributions, whether big or small, are vital to making Lumi the best C++ desktop framework it can be.

This guide outlines how you can contribute, ensuring a smooth and efficient process for everyone involved.

-----

## Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](CODE_OF_CONDUCT.md). By participating in this project, you agree to abide by its terms.

-----

## How to Contribute

### 1\. Find Something to Work On

* **Look for Issues:** Check the [Issues](https://github.com/TheMonHub/LumiFramework/issues) section on GitHub for existing bugs, feature requests, or tasks.
    * When reporting a bug, please include: steps to reproduce, expected behavior, actual behavior, and your environment (OS, compiler, LumiFramework version/commit).
* **Discuss New Ideas:** If you have a new idea for a feature or a significant change, please open an [issue](https://github.com/TheMonHub/LumiFramework/issues) first to discuss it with the maintainers. This helps avoid duplicate work and ensures your contribution aligns with the project's vision.
    * When suggesting a feature, clearly describe the problem it solves, how it might work, and why it's beneficial to LumiFramework.
### 2\. Fork the Repository

First, you'll need to fork the [LumiFramework repository](https://github.com/TheMonHub/LumiFramework) to your own GitHub account. This creates a personal copy where you can make your changes.

### 3\. Clone Your Fork

Clone your forked repository to your local machine:

```bash
git clone https://github.com/YourUsername/LumiFramework.git
cd LumiFramework
```

### 3.5. Development Environment Setup

To build and contribute to LumiFramework, you will need:

* **C++ Compiler:**
    * **Clang** (recommended): LLVM/Clang 16.0 and newer.
    * **GCC**: GCC 14 (for the in-development branch, after 2023-09-20) and newer.
    * **MSVC**: MSVC toolset 14.34 and newer (provided with Visual Studio 17.4 and newer).
* **CMake:** Version 3.28 or newer.
* **Git:** Latest stable version.
* **Clang-Format & Clang-Tidy:** Ensure these are installed and in your PATH for the formatting and static analysis scripts to work correctly, LLVM version 19 required.

LumiFramework aims to be cross-platform, supporting Windows, Linux, and macOS. Please ensure your development environment is set up according to these requirements.

### 4\. Gitflow Workflow

LumiFramework uses the **Gitflow Workflow**. This means we primarily work with feature branches.

1.  **Sync with `develop`:** Ensure your local `develop` branch is up to date with the upstream `develop` branch:
    ```bash
    git checkout develop
    git pull upstream develop # Assuming you've set up 'upstream' remote
    ```
    If you haven't set up the `upstream` remote yet, you can do so with:
    ```bash
    git remote add upstream https://github.com/TheMonHub/LumiFramework.git
    ```
2.  **Create a Feature Branch:** Based on `develop`, create a new feature branch for your changes. Use a descriptive name (e.g., `feature/add-new-widget`, `bugfix/fix-memory-leak`).
    ```bash
    git checkout -b feature/your-feature-name develop
    ```
3.  **Make Your Changes:** Implement your bug fix or feature.

### 5\. Build the Project

LumiFramework uses CMake for its build system. The primary build instructions are detailed directly within the [CMakeLists.txt](CMakeLists.txt) file at the root of the project.

In short, a typical build process involves:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Refer to the top of `CMakeLists.txt` for the most accurate and up-to-date build instructions, including any specific platform requirements or configuration options.

### 6\. Format Your Code (Crucial\!)

LumiFramework enforces strict code formatting using Clang-Format. **Before committing**, always run the formatting script to ensure your code adheres to our style guidelines:

```bash
./clang-format-fix.sh
```

This script will automatically reformat your code in place.

To only check the formatting without making changes, you can use:

```bash
./clang-format.sh
```

### 7\. Run Static Analysis (Important\!)

We use Clang-Tidy for static analysis to catch potential bugs and enforce coding standards. **Before committing**, run the Clang-Tidy script:

```bash
./clang-tidy.sh
```

**Note:** This script will build the project under the `build` directory as part of its execution. Review any warnings or errors reported by Clang-Tidy and address them before pushing.

To fix issues reported by Clang-Tidy automatically, you can use the `-fix` script:

```bash
./clang-tidy-fix.sh
```

### 8\. Test Your Changes

Ensure your changes don't break existing functionality and, if applicable, add new unit tests for your feature or bug fix. Run the tests using your build system (e.g., `cmake --build . --target test` from your `build` directory).

### 9\. Commit Your Changes

Once your changes are complete, formatted, analyzed, and tested, commit them to your feature branch. Write clear and concise commit messages.

Use a clear and concise message prefixed with a type:

* `feat`: For new features.
* `fix`: For bug fixes.
* `docs`: For documentation changes.
* `style`: For formatting or non-functional code changes.
* `refactor`: For code refactoring.
* `test`: For adding or modifying tests.
* `chore`: For maintenance tasks, build process changes, etc.
* `perf`: For performance improvements.

```bash
git add .

git commit -m "feat: Add new awesome widget"
```

### 10\. Push Your Feature Branch

Push your feature branch to your forked repository on GitHub:

```bash
git push origin feature/your-feature-name
```

### 11\. Create a Pull Request (PR)

Before submitting your PR, please ensure:
* Your code is formatted (`./clang-format-fix.sh`).
* Clang-Tidy reports no major warnings (`./clang-tidy.sh`).
* All existing tests pass, and new tests are added for new features/fixes.
* Your commit messages follow the Conventional Commits guidelines.
* You have read through your changes one last time, as if you were reviewing someone else's code.

1.  Go to your forked repository on GitHub.
2.  GitHub will usually show a banner prompting you to create a pull request from your recently pushed branch. If not, navigate to the "Pull requests" tab and click "New pull request."
3.  **Ensure the base branch is `develop` on the `TheMonHub/LumiFramework` repository, and the compare branch is your `feature/your-feature-name` on your fork.**
4.  Provide a clear and descriptive title and description for your pull request.
    * Explain what problem it solves or what feature it adds.
    * Reference any related issues (e.g., `Closes #123`, `Fixes #456`).
5.  Submit the pull request.

### 12\. Code Review

Maintainers will review your pull request. Be prepared to:

* Address any feedback or questions.
* Make further commits to your branch if necessary (these will automatically update the PR).
* Ensure all CI checks (build, format, static analysis, tests, etc.) pass on your PR.

Once your PR is approved and all checks pass, it will be merged into the `develop` branch.

## Need Help?

If you get stuck or have questions about contributing, feel free to:
* Open an [issue](https://github.com/TheMonHub/LumiFramework/issues) on GitHub.
* [Join our Discord server](https://discord.gg/2jJaC3yFEH)


-----

Thank you for contributing to LumiFramework\! We appreciate your efforts in making this project better.