# dump-it
A simple binary dump command-line program for Linux written in C

## Compile
```
$ make
```

## Usage
```
$ ./dumpit file1 file2...
```

##### Example:
```
$ ./dumpit ./lorem_ipsum.txt
```
If we dump a text file containing the first sentence of Lorem Ipsum we get this: 
```
./lorem_ipsum.txt
----------------------------------------------------------------
4c 6f 72 65 6d 20 69 70 73 75 6d 20 64 6f 6c 6f Lorem ipsum dolo
72 20 73 69 74 20 61 6d 65 74 2c 20 63 6f 6e 73 r sit amet, cons
65 63 74 65 74 75 72 20 61 64 69 70 69 73 63 69 ectetur adipisci
6e 67 20 65 6c 69 74 2c 20 73 65 64 20 64 6f 20 ng elit, sed do 
65 69 75 73 6d 6f 64 20 74 65 6d 70 6f 72 20 69 eiusmod tempor i
6e 63 69 64 69 64 75 6e 74 20 75 74 6c 61 62 6f ncididunt utlabo
72 65 20 65 74 20 64 6f 6c 6f 72 65 20 6d 61 67 re et dolore mag
6e 61 20 61 6c 69 71 75 61 0a 00 00 00 00 00 00 na aliqua.......
```
This also works for binaries (for example, you can see a dump of dumpit).
