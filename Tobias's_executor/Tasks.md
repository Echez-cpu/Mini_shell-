- Focus on command parsing, handling quotes, and variable expansion.
- Implement echo, pwd, export.
- Handle Input/Output redirections (<, >, <<, >>).
- Manage signal handling (ctrl-C, ctrl-D, ctrl-\\).

Problems:
- Save $? somehow
- Access export?

Mem-Save:
- " = 34, ' = 39
- Var-exp = $? -> 0 || $Hellauaa -> ''
- solve command parsing with linked list ???
- < [fd] : STD_IN == fd
- << [Str] : read until line == str
- > [fd] : STD_OUT == fd
- >> [fd] : STD_OUT == fd (append)

