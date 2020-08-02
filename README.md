# GVNEditor-Prototype
The GVNEditor is the visual editor for the GVNEngine. The GVNEditor is intended as a one-stop-shop for developing content for projects using the GVNEngine. This repo was used as a place to prototype an early iteration of the GVNEditor using C++ and Qt.

![ScreenShot](README_Files/GVNEditor.png?raw=true "GVNEditor")

## Feature List
### Editing Table
- Save or load a 'story' XML file. Loading will repopulate the editing table
- Add / remove rows
- Move rows up / down
- Text in every column wraps, allowing for short to long text entries

### Logger
- All editing classes can call a 'Log' function which outputs their message to the logger with a generated datestamp
  
