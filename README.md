# tfsound


## Information
tfsound is tools for test frequency audio.
This simple tools and You must to code simple script.

## How To Using
The Program: Just like giving parameters to functions. the way is like giving a frequencyn in the first and second posts there is a delay (cs). 
So it looks this way. In the middle of it must be put a comma.

### Main:
```bash
Frequency, Delay
```

And if there is another line put a comma at the last delay it will be like this.

### Main:
```bash
Frequency, Delay,
Frequency, Delay
```

### Example:
```bash
440, 100,
440, 100,
440, 100,
330, 70,
330, 70
```

## Compile

You must have the dependencies.
### Dependencies
- Compiler (Mingw | GNU Compiler)
- SDL2 (Library)
- make (tools)

### Compile Command
You just run this command.
After you running the command.
The output file in folder bin.
```bash
$ make
```

## Flags TFSound
### Compile Code
If you wont to compile you must giving flags like this:
```bash
$ ./tfsound --compile <PATH/FILE>
```
### Play The File
After you compile the output file it's `<PATH/FILE>.tf`. The tools
Will be write new file with the name file you giving But in Compile.
The name of file it's giving format `.tf`.

If you wont play you must giving flags like this:
```bash
$ ./tfsound --play <PATH/FILE>.tf
```
