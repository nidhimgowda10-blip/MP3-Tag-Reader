MP3 Tag Reader

📌 Description

MP3 Tag Reader is a command-line application developed in **C** to read and edit **ID3v2.3 metadata** stored in MP3 audio files.

The application allows users to view and modify commonly used MP3 tag information such as **Title, Artist, Album, Year, Genre, and Comment**.

🎯 Objectives

* Read ID3v2.3 metadata from MP3 files.
* Display existing tag information.
* Edit selected tag fields.
* Validate user inputs and command-line arguments.
* Handle MP3 files using binary file operations.

🛠️ Technologies Used

* **Language:** C
* **Standard:** C99
* **Concepts:** File Handling, Structures, Pointers, Strings, Binary File I/O
* **Compiler:** GCC
* **Debugging:** Valgrind
* **Build Tool:** Makefile

⚙️ Features

1. View MP3 Tags

Displays metadata stored in the MP3 file, including:

* Title
* Artist
* Album
* Year
* Genre
* Comment

2. Edit MP3 Tags

Allows the user to modify supported ID3v2.3 tag fields.

3. Command-Line Interface

The application accepts command-line arguments to perform view and edit operations.

4. Input Validation

Validates command-line arguments and ensures that the required MP3 file is provided.

5. Memory Management

The program was tested using **Valgrind** to identify memory leaks and memory-related errors.

🧠 ID3v2.3 Tag Structure

The MP3 metadata is stored in frames. Each frame contains information about a particular tag.

```text
ID3 Header
    ↓
┌─────────────┐
│ Frame ID    │
├─────────────┤
│ Frame Size  │
├─────────────┤
│ Flags       │
├─────────────┤
│ Frame Data  │
└─────────────┘
```

Examples of commonly used frames:

```text
TIT2 → Title
TPE1 → Artist
TALB → Album
TYER → Year
TCON → Genre
COMM → Comment
```

📂 Project Structure

```text
MP3_Tag_Reader/
│
├── main.c
├── utils.c
├── validate.c
├── view.c
├── edit.c
├── Header files
├── Makefile
└── README.md
```

▶️ Compilation

Compile the project using:

```bash
make
```

Run the application:

```bash
./mp3_tag_reader
```

🖥️ Operations

View Tags

```bash
./mp3_tag_reader -v sample.mp3
```

Edit Tags

```bash
./mp3_tag_reader -e -t "New Title" sample.mp3
```

🔍 Example Output

```text
----------------------------------------
        MP3 TAG READER
----------------------------------------

TITLE       : Sample Song
ARTIST      : Sample Artist
ALBUM       : Sample Album
YEAR        : 2025
GENRE       : Pop
COMMENT     : Sample Comment

----------------------------------------
```

📚 Concepts Learned

* ID3v2.3 MP3 Tag Format
* Binary File Handling
* File Pointers
* Structures
* Pointers
* String Manipulation
* Command-Line Arguments
* Modular Programming
* Input Validation
* Dynamic Memory Management
* Makefile
* Valgrind Debugging

👩‍💻 Author

**Nidhi M**
