# SQF downsizer

## Build

Use make to build the executable

## Usage

### Parameters

```
downsize.exe file_to_read new_file
1 : file_to_read : file that will be read and processed
2 : new_file : file created upon process. Can be identical to file_to_read if you want to override it
```

### Options
None

### Exemple

```
downsize.exe ./tests/initPlayerLocal.sqf ./tests/new_initPlayerLocal.sqf
downsize.exe ./tests/initPlayerLocal.sqf test.sqf
downsize.exe ./tests/initPlayerLocal.sqf ./tests/initPlayerLocal.sqf
```

## Author

* **Lyeed** - [Lyeed](https://github.com/Lyeed)
