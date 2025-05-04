#!/bin/zsh

# Сохраняем исходную директорию
ORIGINAL_DIR=$(pwd)

echo "\n===== Starting build process in $(pwd) ====="

# 1. Генерация проекта CMake
echo "Step 1: Running CMake..."
cmake -B .build || {
    echo "❌ CMake failed"
    cd "$ORIGINAL_DIR"
    exit 1
}

# 2. Сборка проекта
echo -e "\nStep 2: Building project..."
make -C .build || {
    echo "❌ Build failed"
    cd "$ORIGINAL_DIR"
    exit 1
}

# 3. Запуск программы
echo -e "\nStep 3: Running program..."
{
    cd .bin && \
    echo "Running in: $(pwd)\n\n====lab_5==================================================================\n" && \
    ./lab_5
} || {
    echo "❌ Execution failed"
    cd "$ORIGINAL_DIR"
    exit 1
}

# Возвращаемся в исходную директорию
cd "$ORIGINAL_DIR"
echo -e "\n===========================================================================\
\n\nScript 'run.sh': ✅ All done! Returned to: $(pwd)"