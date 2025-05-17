# Lessons Learned

This project has been incredibly instructive. Given my current stage of development as a programmer, it was also quite challenging. It was my first time tackling a project of this complexity, especially as part of a team, and I had to learn a lot along the way.

The minishell project marked a significant step in my journey toward becoming a systems-level C programmer. It didn’t just teach me how to implement a shell: it taught me how to think like one.

Although I still have much to learn, here are some reflections on the process and the key lessons that emerged. I've also compiled more detailed notes in several additional files:

- Main challenges [CHALLENGES.md](CHALLENGES.md)
- Overall project's design: [DESIGN.md](DESIGN.md)
- Project's execution process: [EXECUTION.md](EXECUTION.md)
- Dynamic buffering: [BUFFER.md](BUFFER.md)
- Memory pooling: [MEMORY_POOLING.md](MEMORY_POOLING.md)
- Safe memory handling: [SAFE.md](SAFE.md)
- Use of the `extern` keyword: [EXTERN.md](EXTERN.md)
- Use of the `volatile` keyword: [VOLATILE.md](VOLATILE.md)
- Header file management: [HEADERS.md](HEADERS.md)
- Wrapper functions: [WRAPPERS.md](WRAPPERS.md)

### 1. Process management in UNIX
I gained solid practical knowledge of forking, piping, and inter-process communication. This experience has built a strong foundation for systems-level programming in C.

### 2. Subtlety of shell parsing
I developed a better understanding of the complexities involved in quote handling, variable expansion, and the syntactic rules that govern shell behavior.

### 3. Defensive coding and edge case awareness
I learned to anticipate errors caused by unusual user input or unexpected environments. I also built strategies to handle these situations gracefully.

### 4. Testing Culture
I adopted a consistent habit of testing edge cases, especially those highlighted in community threads. I also became aware of the importance of crafting a reliable test suite tailored to the project's needs, as poor test coverage can give misleading results.

### 5. Code Discipline
I practiced writing clean, modular, and maintainable code within the constraints of the Norm and strict memory management requirements.

### 6. Community Collaboration
I benefited significantly from community feedback, especially through Slack discussions, which helped me catch implementation issues and align the shell's behavior more closely with bash.

### 7. Git Management
With 153 files and 17,803 lines of code across 1,045 commits, the rule *branch early and branch often* proved invaluable. This strategy allowed us to develop different features in parallel and manage changes efficiently.

### 8. Refactoring and Function Complexity
Refactoring long, complex functions into smaller, Norm-compliant ones presented recurring challenges. We often encountered breakages after refactoring, which taught us to plan such tasks carefully.

### 9. Documentation
I learned to implement Doxygen for structured code documentation and used gitstats to monitor repository activity. For future projects, I plan to take a drafting approach to documentation from the beginning, as maintaining accurate docstrings proved difficult with many files still in progress.
I also learned how to use `gitstats`to create visualizations and statistics about the project's Git repository. Instructions on how to generate them can be found at [gitstats.md](gitstats.md).

---

This project was more than just a shell implementation. It was a practical course in systems programming, collaboration, and software engineering discipline.

