#!/bin/bash

# Dosya ve program tanımlamaları
INFILE="infile"
OUTFILE1="outfile1"
OUTFILE2="outfile2"
PIPEX="./pipex"

# Test sayacı
TEST_COUNT=0
FAILED_TESTS=0

# **Genel test fonksiyonu**
run_test() {
    local cmd1=$1
    local cmd2=$2
    local test_name=$3

    TEST_COUNT=$((TEST_COUNT + 1))

    # Normal bash komutu ile outfile1 oluştur
    < "$INFILE" eval "$cmd1" | eval "$cmd2" > "$OUTFILE1" 2>&1

    # pipex ile outfile2 oluştur
    "$PIPEX" "$INFILE" "$cmd1" "$cmd2" "$OUTFILE2" 2>&1

    # Dosyaları karşılaştır
    if diff -q "$OUTFILE1" "$OUTFILE2" > /dev/null; then
        echo "✅ Test $TEST_COUNT ($test_name) PASSED"
    else
        echo "❌ Test $TEST_COUNT ($test_name) FAILED"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# **Memory leak test fonksiyonu**
run_memory_leak_test() {
    local cmd1=$1
    local cmd2=$2
    local test_name=$3

    TEST_COUNT=$((TEST_COUNT + 1))

    echo "🧪 Running memory leak test: $test_name"
    valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 "$PIPEX" "$INFILE" "$cmd1" "$cmd2" "$OUTFILE2" > /dev/null 2>&1

    if [ $? -eq 0 ]; then
        echo "✅ Memory leak test $TEST_COUNT ($test_name) PASSED"
    else
        echo "❌ Memory leak test $TEST_COUNT ($test_name) FAILED"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# **Yanlış komut test fonksiyonu**
run_invalid_command_test() {
    local cmd1=$1
    local cmd2=$2
    local test_name=$3

    TEST_COUNT=$((TEST_COUNT + 1))

    echo "🔴 Testing invalid command: $test_name"

    # Bash hatalı komutu çalıştırıyor mu?
    bash_output=$( { bash -c "< '$INFILE' $cmd1 | $cmd2 > '$OUTFILE1'" ; } 2>&1 )
    bash_exit_status=$?

    # Pipex hatalı komutu çalıştırıyor mu?
    pipex_output=$( { "$PIPEX" "$INFILE" "$cmd1" "$cmd2" "$OUTFILE2"; } 2>&1 )
    pipex_exit_status=$?

    # Sonuçları karşılaştır
    if [[ "$bash_output" == "$pipex_output" && "$bash_exit_status" == "$pipex_exit_status" ]]; then
        echo "✅ Test $TEST_COUNT ($test_name) PASSED"
    else
        echo "❌ Test $TEST_COUNT ($test_name) FAILED"
        echo "   - Bash çıktı:  [$bash_output]"
        echo "   - Pipex çıktı: [$pipex_output]"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# **Hatalı komutlar için memory leak testi**
run_invalid_memory_leak_test() {
    local cmd1=$1
    local cmd2=$2
    local test_name=$3

    TEST_COUNT=$((TEST_COUNT + 1))

    echo "🛠 Running invalid memory leak test: $test_name"
    valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 "$PIPEX" "$INFILE" "$cmd1" "$cmd2" "$OUTFILE2" > /dev/null 2>&1

    if [ $? -eq 0 ]; then
        echo "✅ Invalid memory leak test $TEST_COUNT ($test_name) PASSED"
    else
        echo "❌ Invalid memory leak test $TEST_COUNT ($test_name) FAILED"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

# **Test dosyasını oluştur**
echo -e "1 apple\n2 orange\n3 banana\n4 grape\n5 pineapple" > "$INFILE"

# **Geçerli testler**
run_test "awk '{print \$2, \$1}'" "sort" "awk and sort"
run_test "awk '{print \$1 * 2}'" "grep -v '4'" "awk and grep"

# **Memory leak testleri**
run_memory_leak_test "awk '{print \$2, \$1}'" "sort" "memory leak test: awk and sort"

# **Yanlış komut testleri**
run_invalid_command_test "invalidcommand" "wc -l" "Invalid command 1"
run_invalid_command_test "awk '{print \$2}'" "notacommand" "Invalid command 2"
run_invalid_command_test "ls | invalidcommand" "wc -l" "Invalid command 3"

# **Yanlış komutlarda memory leak testi**
run_invalid_memory_leak_test "invalidcommand" "wc -l" "Invalid memory leak test 1"
run_invalid_memory_leak_test "awk '{print \$2}'" "notacommand" "Invalid memory leak test 2"
run_invalid_memory_leak_test "ls | invalidcommand" "wc -l" "Invalid memory leak test 3"

# **Sonuçları göster**
if [ "$FAILED_TESTS" -eq 0 ]; then
    echo -e "\n🎉 Tüm testler başarıyla geçti!"
else
    echo -e "\n❌ $FAILED_TESTS test başarısız oldu."
fi

# **Temizlik**
rm -f "$INFILE" "$OUTFILE1" "$OUTFILE2"

