#!/bin/bash

# Colors for better output
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
RESET="\033[0m"

# Function to run a test case
run_test() {
  local test_num=$1
  local infile=$2
  local cmd1=$3
  local cmd2=$4
  local outfile=$5
  local description=$6

  echo -e "${YELLOW}Test Case $test_num: $description${RESET}"

  # Create outfile names
  local pipex_outfile="${outfile}"
  local bash_outfile="${outfile}_bash"

  # Run pipex
  echo "Running: ./pipex $infile \"$cmd1\" \"$cmd2\" $pipex_outfile"
  ./pipex "$infile" "$cmd1" "$cmd2" "$pipex_outfile" 2> "pipex_error_$test_num.txt"
  local pipex_exit=$?

  # Run bash equivalent
  echo "Running bash: < $infile $cmd1 | $cmd2 > $bash_outfile"
  eval "< $infile $cmd1 | $cmd2 > $bash_outfile" 2> "bash_error_$test_num.txt"
  local bash_exit=$?

  # Compare exit codes
  echo "Pipex exit code: $pipex_exit"
  echo "Bash exit code: $bash_exit"

  # Compare outputs if both commands succeeded
  if [ -f "$pipex_outfile" ] && [ -f "$bash_outfile" ]; then
    if diff "$pipex_outfile" "$bash_outfile" > /dev/null; then
      echo -e "${GREEN}Output files match!${RESET}"
    else
      echo -e "${RED}Output files differ!${RESET}"
      echo "Pipex output:"
      cat "$pipex_outfile"
      echo "Bash output:"
      cat "$bash_outfile"
    fi
  else
    echo -e "${RED}One or both output files not created${RESET}"
  fi

  echo "----------------------------------------"
}

# Clean up all test files - both at the beginning and end of tests
cleanup() {
  echo "Cleaning up test files..."
  # Remove all test input files
  rm -f infile*

  # Remove all test output files
  rm -f outfile*

  # Remove empty and permission test files
  rm -f empty_infile noperm_*

  # Remove bash comparison files
  rm -f *_bash

  # Remove error log files
  rm -f pipex_error_* bash_error_*

  # Remove any other temporary files that might be created
  rm -f temp_* *.tmp

  echo "Cleanup complete."
}

# Setup test environment
setup() {
  echo "Setting up test environment..."

  # Test Case 1
  echo -e "Hello World\nThis is a test file\nWith multiple lines\nFor testing pipes" > infile1

  # Test Case 2
  echo -e "Line 1\nLine 2\nLine 3\nLine 4\nLine 5" > infile2

  # Test Case 8
  echo -e "zebra\napple\nbanana\norange\nkiwi" > infile8

  # Test Case 9
  echo -e "Hello \"World\"\nThis is a 'test' file" > infile9

  # Test Case 10
  touch empty_infile

  # Permission Test Cases
  echo "This is a test" > noperm_infile
  chmod 000 noperm_infile

  touch noperm_outfile
  chmod 444 noperm_outfile
}

# Main test script
echo -e "${YELLOW}========== PIPEX TESTER ==========${RESET}"

# Clean up any existing test files first
cleanup

# Set up the test environment
setup

# Run all test cases
run_test 1 "infile1" "grep test" "wc -l" "outfile1" "Basic functionality"
run_test 2 "infile2" "grep Line" "sed 's/Line/Number/g'" "outfile2" "Command with multiple arguments"
run_test 3 "infile2" "/usr/bin/cat" "/usr/bin/grep Number" "outfile3" "Commands using absolute paths"
run_test 4 "nonexistentfile" "cat" "grep test" "outfile4" "Non-existent infile"
run_test 5 "infile1" "nonexistentcmd" "wc -l" "outfile5" "Non-existent command"
run_test 6 "noperm_infile" "cat" "wc -l" "outfile6" "Permission denied on infile"
run_test 7 "infile1" "cat" "wc -l" "noperm_outfile" "Permission denied on outfile"
run_test 8 "infile8" "grep -v kiwi" "sort" "outfile8" "Complex pipeline with sorting"
run_test 9 "infile9" "grep \"World\"" "wc -l" "outfile9" "Command with quotes"
run_test 10 "empty_infile" "cat" "wc -l" "outfile10" "Empty infile"

# Reset permissions before cleanup
chmod 644 noperm_infile 2>/dev/null
chmod 644 noperm_outfile 2>/dev/null

echo -e "${YELLOW}========== TESTING COMPLETE ==========${RESET}"

# Clean up all test files at the end
cleanup
