# Create ld symlink to avoid linking error(s)
ln -s $(pwd)/prebuilts/clang/host/linux-x86/clang-r383902b/bin/lld \
    $(pwd)/prebuilts/clang/host/linux-x86/clang-r383902b/bin/ld &> /dev/null
