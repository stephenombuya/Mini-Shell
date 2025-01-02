# Mini Shell

A lightweight shell program implemented in C that supports basic command execution. This project demonstrates fundamental concepts of process management, tokenization, and user interaction in a Linux environment.

## Features
- Command execution (e.g., `ls`, `pwd`, etc.).
- Input parsing and tokenization.
- Graceful handling of invalid commands.
- Exit command to terminate the shell.

## Usage

### Prerequisites
- A C compiler (e.g., GCC).
- A Linux or UNIX-based operating system.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/stephenombuya/Mini-Shell
   cd mini-shell
   ```
2. Compile the program:
   ```bash
   gcc -o mini-shell mini_shell.c
   ```

### Running the Shell
Start the shell by running:
```bash
./mini-shell
```
You will see a prompt `mini-shell>` where you can type commands.

### Example Usage
```bash
mini-shell> ls
mini-shell> pwd
mini-shell> exit
```

## Contributing
Contributions are welcome! Follow these steps:
1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Description of changes"
   ```
4. Push to the branch:
   ```bash
   git push origin feature-name
   ```
5. Open a pull request.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgements
- Inspired by the need for simple examples in operating systems and C programming.

---
