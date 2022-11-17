#ifndef CORELIB_UNITTEST_TESTUTILS_H
#define CORELIB_UNITTEST_TESTUTILS_H

#include <gtest/gtest.h>
#include <vector>
#include <string>

namespace testing {
    class CommandLineParser;
    static CommandLineParser *pCommandLineParser;

    class MemoryLeakDetector : public EmptyTestEventListener {
    public:
        virtual void OnTestStart(const TestInfo&) override;
        virtual void OnTestEnd(const TestInfo &test_info) override;

    private:
#ifdef _WIN32
    #if defined(_DEBUG) && !defined(IS_MOBILE_PLATFORM)
        _CrtMemState m_memState;
    #endif
#endif
    };

    class ResourceLeakDetector : public EmptyTestEventListener {
    public:
        virtual void OnTestStart(const TestInfo &) override;
        virtual void OnTestEnd(const TestInfo &test_info) override;

    private:
#ifdef _WIN32
    #if defined(_DEBUG) && !defined(IS_MOBILE_PLATFORM)
        int m_numberOfGuiResources;
        int m_numberOfUserResources;
    #endif
#endif
    };

    class HandleLeakDetector : public EmptyTestEventListener {
    public:
        virtual void OnTestStart(const TestInfo &) override;
        virtual void OnTestEnd(const TestInfo &test_info) override;

    private:
#ifdef _WIN32
    #if defined(_DEBUG) && !defined(IS_MOBILE_PLATFORM)
        unsigned long m_numberOfProcessHandles;
    #endif
#endif
    };

    class CommandLineParser {
    public:
        CommandLineParser(int argc, char *argv[]);
        int argumentCount() const;
        std::vector<std::string> arguments() const;

    private:
        int m_argumentCount;
        std::vector<std::string> m_arguments;
    };
}

#define CORELIB_TESTMAIN \
GTEST_API_ int main(int argc, char *argv[]) {\
    testing::InitGoogleTest(&argc, argv);\
    testing::UnitTest::GetInstance()->listeners().Append(new testing::ResourceLeakDetector());\
    testing::UnitTest::GetInstance()->listeners().Append(new testing::HandleLeakDetector());\
    testing::UnitTest::GetInstance()->listeners().Append(new testing::MemoryLeakDetector());\
\
    testing::pCommandLineParser = new testing::CommandLineParser(argc, argv);\
\
    return RUN_ALL_TESTS();\
}

#endif // CORELIB_UNITTEST_TESTUTILS_H
