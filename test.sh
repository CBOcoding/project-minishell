#!/bin/bash

# Minishell test script

# Section 1: External commands
echo "TEST: ls"
ls
echo "TEST: /bin/ls"
/bin/ls
echo "TEST: echo hello"
echo hello
echo "TEST: pwd"
pwd

# Section 2: Redirections
echo "TEST: echo hello > testfile.txt"
echo hello > testfile.txt
echo "TEST: cat testfile.txt"
cat testfile.txt
echo "TEST: echo world >> testfile.txt"
echo world >> testfile.txt
echo "TEST: cat testfile.txt"
cat testfile.txt
echo "TEST: echo input > in.txt"
echo input > in.txt
echo "TEST: cat < in.txt"
cat < in.txt

# Section 3: Pipes
echo "TEST: ls | wc -l"
ls | wc -l
echo "TEST: echo uno | cat | cat | wc -l"
echo uno | cat | cat | wc -l
echo "TEST: cat < in.txt | wc -c"
cat < in.txt | wc -c

# Section 4: Built-ins
echo "TEST: mkdir test_dir"
mkdir test_dir
echo "TEST: cd test_dir"
cd test_dir
echo "TEST: pwd"
pwd
echo "TEST: cd .."
cd ..
echo "TEST: rmdir test_dir"
rmdir test_dir
echo "TEST: echo hello world"
echo hello world
echo "TEST: echo -n no_newline"
echo -n no_newline
echo ""

# Section 5: export/unset/env
echo "TEST: export FOO=bar"
export FOO=bar
echo "TEST: echo $FOO"
echo $FOO
echo "TEST: env | grep FOO"
env | grep FOO
echo "TEST: unset FOO"
unset FOO
echo "TEST: echo $FOO"
echo $FOO

# Section 6: Heredoc
echo "TEST: cat << EOF"
cat << EOF
line1
line2
EOF
echo "TEST: wc -l << END"
wc -l << END
uno
due
END

# Section 7: Variable expansion
echo "TEST: export NAME=Minishell"
export NAME=Minishell
echo "TEST: echo $NAME"
echo $NAME

# Section 8: Error handling
echo "TEST: pippo"
pippo
echo "TEST: ls | pippo"
ls | pippo
echo "TEST: ls > /no/permission"
ls > /no/permission
echo "TEST: cat <<"
cat <<
