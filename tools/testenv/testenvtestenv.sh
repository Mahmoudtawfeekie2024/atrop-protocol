#!/bin/bash
# ============================================
# 🧪 ATROP Dev Environment Boot Validation Script
# ============================================

echo "🔍 Starting ATROP dev container environment check..."

# 1. Python/Pip Check
echo -n "🔹 Python Version: "; python3 --version
echo -n "🔹 pip Version: "; pip --version

# 2. Python Package Check
echo "🔹 Verifying required Python packages..."
for pkg in pytest virtualenv mypy grpcio flake8 black; do
    pip show "$pkg" > /dev/null 2>&1 && echo "   ✅ $pkg installed" || echo "   ❌ $pkg missing!"
done

# 3. Build Toolchain Check
echo "🔹 Verifying C++ build tools..."
for tool in g++ cmake make; do
    which $tool > /dev/null 2>&1 && echo "   ✅ $tool found" || echo "   ❌ $tool not found!"
done

# 4. Directory Mount Check
echo "🔹 Checking mounted directories..."
for dir in daemon sdk test; do
    if [ -d "/app/$dir" ]; then
        echo "   ✅ /app/$dir exists"
    else
        echo "   ❌ /app/$dir missing"
    fi
done

# 5. Pytest Check (minimal test run)
if [ -d "/app/test/unit" ]; then
    echo "🔹 Running dry pytest check..."
    pytest --maxfail=1 --disable-warnings --tb=short /app/test/unit || echo "⚠️ pytest check failed"
else
    echo "⚠️ /app/test/unit not found, skipping pytest check"
fi

# 6. Optional: GTest Check (if built)
if [ -f "/app/build/tests/test_main" ]; then
    echo "🔹 Running GTest binary..."
    /app/build/tests/test_main || echo "⚠️ GTest failed or not properly built"
else
    echo "⚠️ GTest binary not found"
fi

echo "✅ ATROP environment check complete."
