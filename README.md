# ECTextEditor

This project is a basic text editor that can take in a file (or create one) and add/remove/edit text, and then save it back to the file. The text editor automatically wraps paragraphs if they get too long for one line, but doesn’t support multiple pages. With this text editor, one can add and remove basic text, but also add, remove, and merge paragraphs. There are a few bugs, but the code works fine for the most part (I struggled with deleting blank lines).

I made this project for a C++ class I took my sophomore year. I haven't worked with this code since I took the class, but I plan on refractoring it and fixing a few bugs. As it stands right now, the code could definitely be cleaner.

User Guide:  
1. Navigate to the project directory.  
2. Type ‘make’ in your terminal to compile the files.  
3. Type “./ECTextEditor filename” to run the text editor.  
  a. You can use an existing .txt file within the directory.  
  b. If the given filename does not exist, the editor will create a new file with that name within the directory.  

Functionalities:  
  Ctrl-q        - save and quit the program  
  Ctrl-s        - save  
  Arrow keys    - move the cursor around to navigate the text  
  Enter/return  - create a new paragraph on the next line  
  Backspace     - delete text (or merge with the the previous line)  
  Ctrl-z        - undo  
  Ctrl-y        - redo  
  Letter keys   - type in text  

Note: this code was developed in VSCode on macOS, and tested out in the default terminal application on macOS. There are a few bugs: when entering text on a blank line in some cases, the character gets added to the next line. Also, when backspacing a blank line below some text, the code breaks. Other than that, the code works fine.


Below is the design spec (UML) for the project. The project used a lot of design patterns, such as command, MVC, chain of responsbility, subject, and observer.

![Design Spec (UML Diagram)](https://user-images.githubusercontent.com/15129556/85901712-6b547880-b7d0-11ea-8eee-b2c4ef615f29.png)  
