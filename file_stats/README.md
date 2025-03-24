fstats Documentation
====================

Overview
--------

`fstats` scans a file and provides detailed statistics about the contents, including the number of words, lines, characters, special characters, and more. It also determines whether the file is a binary or text file and retrieves its file extension.

Features
--------

* Scans the file for basic statistics: file size, word count, line count, character count, etc.
* Identifies whether the file is a text or binary file.
* Extracts the file's extension.

File Types
----------

`fstats` classifies files as either **Text** or **Binary**. A file is classified as binary if more than 10% of its characters are non-text characters (those that are not printable or common control characters).

Usage
-----

```bash
fstats.exe <filepath>
```