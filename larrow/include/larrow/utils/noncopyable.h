namespace utils {
    class NonCopyabale {
    protected:
        NonCopyabale() = default;
        ~NonCopyabale() = default;
        NonCopyabale(const NonCopyabale&) = delete;
        NonCopyabale& operator=(const NonCopyabale&) = delete;
    };
}