#!/bin/bash

INFILE="infile"
OUTFILE1="outfile1"
OUTFILE2="outfile2"
PIPEX="./pipex"

TEST_COUNT=0
FAILED_TESTS=0

run_test() {
    local cmd1=$1
    local cmd2=$2
    local test_name=$3

    TEST_COUNT=$((TEST_COUNT + 1))

    < "$INFILE" eval "$cmd1" | eval "$cmd2" > "$OUTFILE1"

    "$PIPEX" "$INFILE" "$cmd1" "$cmd2" "$OUTFILE2"

    if diff -q "$OUTFILE1" "$OUTFILE2" > /dev/null; then
        echo "✅ Test $TEST_COUNT ($test_name) PASSED"
    else
        echo "❌ Test $TEST_COUNT ($test_name) FAILED"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

echo -e "1 apple\n2 orange\n3 banana\n4 grape\n5 pineapple" > "$INFILE"

run_test "awk '{print \$2, \$1}'" "sort" "awk and sort"
run_test "awk '{print \$1 * 2}'" "grep -v '4'" "awk and grep"
run_test "awk '{print \$2}'" "tr 'a-z' 'A-Z'" "awk and tr"
run_test "cat" "wc -l" "cat and wc"
run_test "grep 'a'" "sort -r" "grep and sort"
run_test "cut -d ' ' -f 2" "uniq" "cut and uniq"
run_test "awk '{print \$1}'" "paste -sd+ | bc" "awk and paste"
run_test "sed 's/a/@/g'" "tr '@' 'a'" "sed and tr"
run_test "awk '{print \$2}'" "head -n 3" "awk and head"
run_test "awk '{print \$1}'" "tail -n 2" "awk and tail"

if [ "$FAILED_TESTS" -eq 0 ]; then
    echo -e "\n🎉 Tüm testler başarıyla geçti!"
else
    echo -e "\n❌ $FAILED_TESTS test başarısız oldu."
fi

rm -f "$INFILE" "$OUTFILE1" "$OUTFILE2"