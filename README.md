# Minishell Executor

**Languages**

[![My Skills](https://skillicons.dev/icons?i=c)](https://skillicons.dev)

**Append Redirect Command >>**

- This command will append/add "Hello World!" to greetings.txt
```
echo "Hello World!" >> greetings.txt
```

**Pipe Command |**

It is used to pipe, or transfer, the standard o/p from the command on its left into the standard i/p of the command on its right.
- First, echo "Hello World" will send Hello World to the standard output.
- Next, pipe | will transfer the standard output to the next command's standard input.
- Finally, wc -w will count the number of words from its standard input, which is 2.
```
echo "Hello World" | wc -w
```

**Redirecting Output >**

- redirect output by taking the output from the command on the left and passing as input to the file on the right.
```
echo "Hello" > hello.txt
```

**Heredoc <<**

- Heredoc uses 2 angle brackets (<<) followed by a delimiter token.
```
 cat << END
    > Hello there
    > This is the end
    > END
Hello there
This is the end
```

**Redirect <**

```
cat < hello.txt
```

**$$ Variable**
- Special variable that represents the process ID (PID) of the currently running shell or script

**export**

- 'export' command is used to make environment variables
```
export MY_VARIABLE="Hello, World!"
echo $MY_VARIABLE
```

**References**

**Pipe**
- https://www.youtube.com/watch?v=Mqb2dVRe0uo
